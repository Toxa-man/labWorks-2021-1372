#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "expertsystem.h"
#include "tbcform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void show_menu();
    void receive_character(QString character);

private slots:
    void on_QuitButton_clicked();
    void on_NewCharacterButton_clicked();
    void on_LoadCharacterButton_clicked();

private:
    Ui::MainWindow *ui;
    ExpertSystem *system;
    TBCform *tbcform;

signals:
    void send_character_file(QString);
    void send_character(QString);
};
#endif // MAINMENU_H
