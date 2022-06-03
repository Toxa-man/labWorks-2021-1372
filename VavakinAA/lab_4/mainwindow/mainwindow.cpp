#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QFontDatabase>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tbcform = new TBCform;
    system = new ExpertSystem;

    connect(this, &MainWindow::send_character_file, tbcform, &TBCform::receive_character_file);
    connect(system, &ExpertSystem::send_character, this, &MainWindow::receive_character);
    connect(this, &MainWindow::send_character, tbcform, &TBCform::receive_character);
    connect(tbcform, &TBCform::tbcform_close, this, &MainWindow::show_menu);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tbcform;
    delete system;
}

void MainWindow::show_menu(){
    show();
}

void MainWindow::receive_character(QString character)
{
    emit send_character(character);
    tbcform->show();
}

void MainWindow::on_NewCharacterButton_clicked()
{
    hide();
    system->show();
}

void MainWindow::on_QuitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_LoadCharacterButton_clicked()
{
    QString character_file = QFileDialog::getOpenFileName(this, tr("Load Character"), "", tr("txt files (*.txt)"));
    if (character_file == ""){
        return;
    }
    tbcform->show();
    emit send_character_file(character_file);
    hide();
}
