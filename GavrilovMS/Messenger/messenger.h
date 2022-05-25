#ifndef MESSENGER_H
#define MESSENGER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QString>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class Messenger; }
QT_END_NAMESPACE

class Messenger : public QMainWindow
{
    Q_OBJECT

public:
    Messenger(QWidget *parent = nullptr);
    ~Messenger();

private:
    Ui::Messenger *ui;
    QTcpSocket *socket;
    QByteArray data;
    quint16 nextBlockSize, room;
    QString name;


public slots:
    void slotReadyRead();
    void SendToServer(QString str);
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_2_clicked();

    void on_pushButton_3_pressed();
    void on_lineEdit_3_returnPressed();
    void on_lineEdit_2_returnPressed();
};
#endif // MESSENGER_H
