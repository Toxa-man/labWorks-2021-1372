#include "minesweeper.h"
#include "ui_minesweeper.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QRandomGenerator>
#include <QString>
#include <QDateTime>
#include <QMessageBox>

QRandomGenerator generator;
bool isStart(true);

Minesweeper::Minesweeper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Minesweeper)
{
    ui->setupUi(this);
    myMapper = new QSignalMapper(this);

    for (int i=0;i<81;i++)
        isBomb[i]=false;

    QGridLayout *myGrid = new QGridLayout(this);
    myGrid->setSpacing(2);

    int num = 0;

    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            btn[num] = new QPushButton("", this);
            btn[num]->setFixedSize(70,70);
            btn[num]->setStyleSheet("font: bold;font-size: 36px");
            connect(btn[num], SIGNAL(clicked()), myMapper, SLOT(map()));
            myMapper->setMapping(btn[num], num);
            myGrid->addWidget(btn[num], i, k);
            num++;
        }
    }
    connect(myMapper, SIGNAL(mapped(int)), this, SLOT(onclicked(int)));

       QWidget *myWidget = new QWidget;
       myWidget->setLayout(myGrid);
       setCentralWidget(myWidget);
}

Minesweeper::~Minesweeper()
{
    delete ui;
}

void Minesweeper::restartGame(){
    for (int k=0;k<81;k++){
    btn[k]->setStyleSheet("font: bold;font-size: 36px");
    btn[k]->setEnabled(true);
    btn[k]->setFlat(false);
    btn[k]->setText("");
    isBomb[k]=false;
    }
}

void Minesweeper::setBombs(int num){
    int newbombs[10];
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    for (int i=0;i<10;i++){
        newbombs[i]=generator.bounded(81);
        while (newbombs[i]==num){
            newbombs[i]=generator.bounded(81);
        }
        int k=0;
        while(k<i){
            if (newbombs[i]==newbombs[k]){
                newbombs[i]=generator.bounded(81);
                k=-1;
            }
            k++;
        }
        isBomb[newbombs[i]]=true;
    }

}


int Minesweeper::getBombs(int num){
int y = num/9;
int x = num-y*9;
int numBombs=0;
if (y>0)numBombs+=isBomb[(y-1)*9+x];
if (y<8)numBombs+=isBomb[(y+1)*9+x];
if (x>0)numBombs+=isBomb[y*9+x-1];
if (x<8)numBombs+=isBomb[y*9+x+1];
if (y>0 && x>0)numBombs+=isBomb[(y-1)*9+x-1];
if (y>0 && x<8)numBombs+=isBomb[(y-1)*9+x+1];
if (y<8 && x>0)numBombs+=isBomb[(y+1)*9+x-1];
if (y<8 && x<8)numBombs+=isBomb[(y+1)*9+x+1];

if (numBombs==0 &&isBomb[num]==0){
    if (y>0 &&isBomb[(y-1)*9+x]==0 && btn[(y-1)*9+x]->isEnabled())
        onclicked((y-1)*9+x);
    if (y<8 &&isBomb[(y+1)*9+x]==0 && btn[(y+1)*9+x]->isEnabled())
        onclicked((y+1)*9+x);
    if (x>0 &&isBomb[y*9+x-1]==0 && btn[y*9+x-1]->isEnabled())
        onclicked(y*9+x-1);
    if (x<8 &&isBomb[y*9+x+1]==0 && btn[y*9+x+1]->isEnabled())
        onclicked(y*9+x+1);
    if (y>0 && x>0 &&isBomb[(y-1)*9+x-1]==0 && btn[(y-1)*9+x-1]->isEnabled())
        onclicked((y-1)*9+x-1);
    if (y>0 && x<8 &&isBomb[(y-1)*9+x+1]==0 && btn[(y-1)*9+x+1]->isEnabled())
        onclicked((y-1)*9+x+1);
    if (y<8 && x>0 &&isBomb[(y+1)*9+x-1]==0 && btn[(y+1)*9+x-1]->isEnabled())
        onclicked((y+1)*9+x-1);
    if (y<8 && x<8 &&isBomb[(y+1)*9+x+1]==0 && btn[(y+1)*9+x+1]->isEnabled())
        onclicked((y+1)*9+x+1);
}

return numBombs;
}

void Minesweeper::onclicked(int num){
    if (isStart){
        setBombs(num);
        isStart=false;
    }
    btn[num]->setFlat(true);
    btn[num]->setEnabled(false);

    int count=0;
    bool isWin=true;
    while (count<81){
        if (btn[count]->isEnabled() && !isBomb[count]){
            count=80;
            isWin=false;
        }
        count++;
    }

    int countBombs = getBombs(num);
    if (countBombs !=0 && !isBomb[num])
    {
        if (countBombs==1)
            btn[num]->setStyleSheet("font: bold;font-size: 36px;color:blue");
        if (countBombs==2)
            btn[num]->setStyleSheet("font: bold;font-size: 36px;color:green");
        if (countBombs==3)
            btn[num]->setStyleSheet("font: bold;font-size: 36px;color:red");
        if (countBombs>=4)
            btn[num]->setStyleSheet("font: bold;font-size: 36px;color:black");
        btn[num]->setText(QString::number(countBombs));
    }

    QMessageBox::StandardButton reply;
    if (isBomb[num]){
        for (int k=0;k<81;k++){
        if (isBomb[k]) btn[k]->setText("B");
        btn[k]->setEnabled(false);
        }
        reply = QMessageBox::question(this, "Поражение","Вы проиграли! Хотите начать заново?",QMessageBox::Yes | QMessageBox::No);
    }

    if (isWin) {
        for (int k=0;k<81;k++){
            btn[k]->setEnabled(false);
        }
        reply = QMessageBox::question(this, "Победа","Вы выиграли! Хотите начать заново?",QMessageBox::Yes | QMessageBox::No);
    }

    if (reply == QMessageBox::Yes){
        isStart=true;
        restartGame();
    }

}




