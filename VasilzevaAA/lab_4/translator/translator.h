#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTextStream>
#include <QFile>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Translator; }
QT_END_NAMESPACE

class Translator : public QMainWindow
{
    Q_OBJECT

public:
    Translator(QWidget *parent = nullptr);
    ~Translator();

public slots:
    void replyFinished(QNetworkReply* reply) {

        QNetworkReply::NetworkError err = reply->error();

        if(err != QNetworkReply::NoError) {
            qDebug() << "Failed: " << reply->errorString();
        }
        else {

            QFile NET_WORD ("C:\\qt_projs\\translator\\wooordhunt.txt");

            NET_WORD.open(QIODevice::WriteOnly);
            QTextStream in(&NET_WORD);

            in << reply->readAll();

            NET_WORD.close();
        }
    }

    void addWord(QString a_word);

private:
    Ui::Translator *ui;
};
#endif // TRANSLATOR_H
