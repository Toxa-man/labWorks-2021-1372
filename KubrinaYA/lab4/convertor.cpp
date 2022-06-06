#include "convertor.h"
#include "ui_convertor.h"

Convertor::Convertor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Convertor)
{
    ui->setupUi(this);
    _manager =new QNetworkAccessManager();
    connect(_manager , &QNetworkAccessManager::finished, this, &Convertor::onResult);
    _manager->get(QNetworkRequest(QUrl("http://cdn.cur.su/api/cbr.json")));

    //ui->label_res->setText(QTime::currentTime().toString("hh:mm:ss"));


    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
    timer->start(30000);

}

void Convertor::onResult(QNetworkReply *reply){
    if(!reply->error()){
           QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
           QJsonObject root = doc.object();
           QJsonObject rates = root["rates"].toObject();
           Convertor::val = rates.toVariantMap();
           //ui->label_res->setText(val.find("AZN")->toString());

        }
        reply->deleteLater();
}

Convertor::~Convertor()
{
    delete ui;
    delete _manager;
    delete timer;
}

void Convertor::slotTimer()
{

   // ui->label_res->setText(QTime::currentTime().toString("hh:mm:ss"));
    _manager =new QNetworkAccessManager();
    connect(_manager , &QNetworkAccessManager::finished, this, &Convertor::onResult);
    _manager->get(QNetworkRequest(QUrl("http://cdn.cur.su/api/cbr.json")));
    //ui->textEdit->setText(Convertor::root.value(Convertor::root.keys().at(2)).toString());
}

void Convertor::on_pushButton_conv_clicked()
{
    if(!(ui->lineEdit_val->text()=="")){
            if(ui->comboBox_from->currentText()=="USD"&&ui->comboBox_in->currentText()=="USD"){
                ui->label_res->setText(ui->lineEdit_val->text());
            }
            else if(ui->comboBox_from->currentText()=="USD"){
                ui->label_res->setText(QString::number(Convertor::val.find(ui->comboBox_in->currentText())->toDouble()
                                                       * ui->lineEdit_val->text().toDouble()));

            }
            else if(ui->comboBox_in->currentText()=="USD"){
                ui->label_res->setText(QString::number(ui->lineEdit_val->text().toDouble()
                                       / Convertor::val.find(ui->comboBox_from->currentText())->toDouble()));
            }
            else{
                double val_from = (ui->lineEdit_val->text().toDouble()
                        / Convertor::val.find(ui->comboBox_from->currentText())->toDouble());
                double val_in = val_from *Convertor::val.find(ui->comboBox_in->currentText())->toDouble();
                ui->label_res->setText(QString::number(val_in));
            }
        }
        else{
            ui->label_res->setText("0");
        }
}

