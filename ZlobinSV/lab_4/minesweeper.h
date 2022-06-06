#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QList>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class Minesweeper; }
QT_END_NAMESPACE

class Minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr);
    ~Minesweeper();

private:
    Ui::Minesweeper *ui;
    QSignalMapper* myMapper;
    QPushButton *btn[81];
    bool isBomb[81];

private slots:
    void onclicked(int num);
    void setBombs(int num);
    void restartGame();
    int getBombs(int num);
};
#endif // MINESWEEPER_H
