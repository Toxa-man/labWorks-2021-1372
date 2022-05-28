#ifndef MAINWINDOWEND_H
#define MAINWINDOWEND_H

#include <QMainWindow>

namespace Ui {
class MainWindowEnd;
}

class MainWindowEnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowEnd(QWidget *parent = nullptr);
    ~MainWindowEnd();
    //функции, которые будут писать текст, в зависимости от того, выиграл игрок или просто вышел из игры
    void it_is_not_win();
    void it_is_win();
signals:
    //сигнал, который мы посылаем, если человек хочет начать новую игру
    void show_game();

private:
    Ui::MainWindowEnd *ui;
private slots:
    void click_play();
    void click_complete();
};

#endif // MAINWINDOWEND_H
