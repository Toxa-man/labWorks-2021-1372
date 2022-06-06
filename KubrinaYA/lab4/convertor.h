#ifndef CONVERTOR_H
#define CONVERTOR_H


#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QTimer>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class Convertor; }
QT_END_NAMESPACE

class Convertor : public QMainWindow
{
    Q_OBJECT

public:
    Convertor(QWidget *parent = nullptr);
    ~Convertor();

private slots:
    void on_pushButton_conv_clicked();
    void onResult(QNetworkReply *reply);
    void slotTimer();
private:
    Ui::Convertor *ui;
    QNetworkAccessManager *_manager;
    QVariantMap val;
    QTimer *timer;
};
#endif // CONVERTOR_H
