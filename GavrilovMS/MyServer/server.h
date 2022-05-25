#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QString>
#include <QMap>

class MyServer : public QTcpServer{

    Q_OBJECT

public:
    MyServer();
    QTcpSocket* socket;
private:

    QVector<QTcpSocket*> sockets[1000];
    QByteArray data;
    void SendToClient(QString str, quint16 room);
    quint16 nextBlockSize;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};

#endif // SERVER_H
