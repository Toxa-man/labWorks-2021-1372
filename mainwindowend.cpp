#include "mainwindowend.h"
#include "ui_mainwindowend.h"
#include <QTimer>

MainWindowEnd::MainWindowEnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowEnd)
{
    ui->setupUi(this);
    QObject::connect(ui->button_play,&QPushButton::clicked,[this](){click_play();});
    QObject::connect(ui->button_complete,&QPushButton::clicked,[this](){click_complete();});
}

MainWindowEnd::~MainWindowEnd()
{
    delete ui;
}

void MainWindowEnd::it_is_not_win()
{
    ui->pushButtonEnd->setText("YOU LOST! TRY AGAIN");
}

void MainWindowEnd::it_is_win()
{
    ui->pushButtonEnd->setText("YOU ARE WINNER!");
}

void MainWindowEnd::click_play()
{
    this->close();
    emit show_game();
}

void MainWindowEnd::click_complete()
{
    this->close();
}
