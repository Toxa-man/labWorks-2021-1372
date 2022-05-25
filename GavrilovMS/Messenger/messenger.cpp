#include "messenger.h"
#include "ui_messenger.h"

Messenger::Messenger(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Messenger)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::readyRead, this, &Messenger::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected, socket, &Messenger::deleteLater);
    socket->connectToHost("172.18.10.61",1000);
    name = "unknown";

    ui->lineEdit_3->setValidator( new QIntValidator(0, 999, this) );

    room = 0;
    nextBlockSize = 0;

}

Messenger::~Messenger()
{
    delete ui;
}

void Messenger::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok){
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
            in >> str;
            nextBlockSize = 0;
            ui->textBrowser->append(str);
        }

    } else {
        ui->textBrowser->append("reading error");
    }
}

void Messenger::SendToServer(QString str){
    data.clear();
    QString mess;
    mess = name + ": " + str;
    QDataStream out(&data, QIODevice::WriteOnly );

    out.setVersion(QDataStream::Qt_5_15);

    out << quint16(0) << room << mess;
    out . device() ->seek(0);
    out << quint16(data.size()-sizeof(quint16));

    socket -> write(data);
    ui -> lineEdit -> clear();

}


void Messenger::on_pushButton_clicked()
{
    SendToServer(ui->lineEdit->text());
}


void Messenger::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}


void Messenger::on_pushButton_2_clicked()
{
    if (ui->lineEdit_2->text() != ""){
       name = ui->lineEdit_2->text();
    }
}

void Messenger::on_lineEdit_2_returnPressed()
{
    if (ui->lineEdit_2->text() != ""){
       name = ui->lineEdit_2->text();
    }
}


void Messenger::on_pushButton_3_pressed()
{
    room = ui->lineEdit_3->text().toInt();
    ui->textBrowser->clear();

    QString str = "connected to room.";
    SendToServer(str);
}


void Messenger::on_lineEdit_3_returnPressed()
{

    room = ui->lineEdit_3->text().toInt();

    ui->textBrowser->clear();
    QString str = "connected to room.";
    SendToServer(str);
}



