#include "server.h"

MyServer::MyServer(){

    if (this->listen(QHostAddress::Any,1000)){
        qDebug() << "start success";

    } else {
        qDebug() << "start error";
    }
    nextBlockSize = 0;
}

void MyServer::incomingConnection(qintptr socketDescriptor){

    socket = new QTcpSocket;
    socket ->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead, this, &MyServer::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected, socket, &MyServer::deleteLater);
    sockets[0].push_back(socket);

    qDebug() << "client connected: " << socketDescriptor;
}

void MyServer::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok){

        qDebug() << "reading..";
        for(;;){
            if (nextBlockSize == 0){
                if (socket->bytesAvailable() < 2){
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize){
                break;
            }

            QString str;
            quint16 room;
            in >> room;
            in >> str;


            qDebug() << room;

            size_t cur_r = 0;
            size_t cur_s = 0;
            for (size_t i = 0; i < 1000; i++){
                for (size_t j = 0; j < sockets[i].size(); j++){
                    if (socket->socketDescriptor() == sockets[i][j]->socketDescriptor()){
                        cur_r = i;
                        cur_s = j;
                        break;
                    }
                }
            }
            if (cur_r != room){
                sockets[room].push_back(socket);
                sockets[cur_r].remove(cur_s);
            }
            nextBlockSize = 0;
            SendToClient(str, room);
            break;
        }
    } else {
        qDebug() << "reading error";
    }
}

void MyServer::SendToClient(QString str, quint16 room){
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly );
    out.setVersion(QDataStream::Qt_5_15);


    out << quint16(0) << str;
    out . device() ->seek(0);
    out << quint16(data.size()-sizeof(quint16));
    for (size_t i = 0; i < sockets[room].size(); i++){
        sockets[room][i]->write(data);
    }
}
