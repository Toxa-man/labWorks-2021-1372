#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QStyle>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    w_end = new MainWindowEnd;
    ui->setupUi(this);
    //создаем числовой массив с номерами пятнашек
    for (int i=0;i<count_cell;i++)
    {
        name_cell.push_back(i+1);
    }
    //миксуем номера в разном порядке с условием, чтоб игра была решаема
    mix_cell();
    //создаем массив, в котором будут храниться номера в строковом виде (т.е. текст, отображаемый на ячейках)
    name_cell_str = new QString[count_cell];
    //присваиваем номера нашим клеточкам
    set_name_cell(name_cell);
    //ui->pushButton1_16->setText(ui->pushButton1_15->text()); //эти две строчки я использовала для удобства проверки работы игры
    //ui->pushButton1_15->setText(""); //я убирала микс клеток и оставляла перемешанными только две последние клетки, чтоб не собирать всю игровую доску
    //перерисовка поля в зависимости от нажатой кнопки
    redrawing();
    //здесь мы запускаем окно для последующих игр, если игрок захочет поиграть еще
    QObject::connect(w_end,&MainWindowEnd::show_game,this,&MainWindow::other_game);
    //здесь мы завершаем игру, если клетки на доске собраны правильно
    QObject::connect(this,&MainWindow::game_over,this,&MainWindow::game_over_with_win);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []name_cell_str;
}

void MainWindow::mix_cell()
{

    //функция перемешивает элементы вектора
    random_shuffle(name_cell.begin(),name_cell.end()-1,[](int n){return rand() % n ;});
    //игра решаема, если количество перестановок четное
    //одна перестановка - это когда в паре элементов элемент с меньшим индексом больше, чем элемент с бОльшим индексом
    int perestanovki=0;
    for (size_t i=name_cell.size()-2;i>0;i--)
    {
        for (size_t j=0;j<i;j++)
        {
            if (name_cell[i]<name_cell[j] )
            {
                ++perestanovki;
            }
        }

    }
    if (perestanovki%2!=0)
    {
        //если количество перестановок нечетное, мы просто меняем 2 последних элемента друг с другом
        name_cell[name_cell.size()-1]=name_cell[name_cell.size()-2];
        name_cell[name_cell.size()-2]=name_cell[name_cell.size()-3];
        name_cell[name_cell.size()-3]=name_cell[name_cell.size()-1];
        name_cell[name_cell.size()-1]=size*size;
    }
}

 void MainWindow::set_name_cell(vector <size_t> name_cell)
 {
     for (int i=0;i<count_cell;i++)
     {
         if (name_cell[i]>=10) //в аски таблице нет двузначных чисел, поэтому мы создаем их искусственно
         {
             char second=name_cell[i]%10+'0';
             name_cell_str[i]="1";
             name_cell_str[i].append(second);
         }
         else {name_cell_str[i]=name_cell[i]+'0';} //цифры 0-9 в аски таблице есть
     }

     ui->pushButton1_1->setText(name_cell_str[0]);
     ui->pushButton1_2->setText(name_cell_str[1]);
     ui->pushButton1_3->setText(name_cell_str[2]);
     ui->pushButton1_4->setText(name_cell_str[3]);
     ui->pushButton1_5->setText(name_cell_str[4]);
     ui->pushButton1_6->setText(name_cell_str[5]);
     ui->pushButton1_7->setText(name_cell_str[6]);
     ui->pushButton1_8->setText(name_cell_str[7]);
     ui->pushButton1_9->setText(name_cell_str[8]);
     ui->pushButton1_10->setText(name_cell_str[9]);
     ui->pushButton1_11->setText(name_cell_str[10]);
     ui->pushButton1_12->setText(name_cell_str[11]);
     ui->pushButton1_13->setText(name_cell_str[12]);
     ui->pushButton1_14->setText(name_cell_str[13]);
     ui->pushButton1_15->setText(name_cell_str[14]);
     ui->pushButton1_16->setText("");
 }

bool MainWindow::is_win()
{
    if(ui->pushButton1_1->text()=="1"&&
    ui->pushButton1_2->text()=="2"&&
    ui->pushButton1_3->text()=="3"&&
    ui->pushButton1_4->text()=="4"&&
    ui->pushButton1_5->text()=="5"&&
    ui->pushButton1_6->text()=="6"&&
    ui->pushButton1_7->text()=="7"&&
    ui->pushButton1_8->text()=="8"&&
    ui->pushButton1_9->text()=="9"&&
    ui->pushButton1_10->text()=="10"&&
    ui->pushButton1_11->text()=="11"&&
    ui->pushButton1_12->text()=="12"&&
    ui->pushButton1_13->text()=="13"&&
    ui->pushButton1_14->text()=="14"&&
    ui->pushButton1_15->text()=="15"&&
    ui->pushButton1_16->text()=="") {
        return true;
    }
    return false;
}

void MainWindow::redrawing()
{
    QObject::connect(ui->pushButton1_1,&QPushButton::clicked,[this](){changed_1();});
    QObject::connect(ui->pushButton1_2,&QPushButton::clicked,[this](){changed_2();});
    QObject::connect(ui->pushButton1_3,&QPushButton::clicked,[this](){changed_3();});
    QObject::connect(ui->pushButton1_4,&QPushButton::clicked,[this](){changed_4();});
    QObject::connect(ui->pushButton1_5,&QPushButton::clicked,[this](){changed_5();});
    QObject::connect(ui->pushButton1_6,&QPushButton::clicked,[this](){changed_6();});
    QObject::connect(ui->pushButton1_7,&QPushButton::clicked,[this](){changed_7();});
    QObject::connect(ui->pushButton1_8,&QPushButton::clicked,[this](){changed_8();});
    QObject::connect(ui->pushButton1_9,&QPushButton::clicked,[this](){changed_9();});
    QObject::connect(ui->pushButton1_10,&QPushButton::clicked,[this](){changed_10();});
    QObject::connect(ui->pushButton1_11,&QPushButton::clicked,[this](){changed_11();});
    QObject::connect(ui->pushButton1_12,&QPushButton::clicked,[this](){changed_12();});
    QObject::connect(ui->pushButton1_13,&QPushButton::clicked,[this](){changed_13();});
    QObject::connect(ui->pushButton1_14,&QPushButton::clicked,[this](){changed_14();});
    QObject::connect(ui->pushButton1_15,&QPushButton::clicked,[this](){changed_15();});
    QObject::connect(ui->pushButton1_16,&QPushButton::clicked,[this](){changed_16();});
    QObject::connect(ui->pushButton,&QPushButton::clicked,[this](){changed_complete();});

}

void MainWindow::changed_complete() //если игрок устал и не хочет больше играть, он может сам завершить игру
{
   w_end->it_is_not_win();
   w_end->show();
   this->close();
}

void MainWindow::other_game()
{
    mix_cell();
    set_name_cell(name_cell);
    this->show();
}

void MainWindow::game_over_with_win()
{
    //здесь таймер, чтоб игровое окно не закрывалось слишком быстро и игрок вообще успел понять, что он выиграл
    QTimer::singleShot(1000,[this](){
        w_end->it_is_win();
        w_end->show();
        this->close();});
}


void MainWindow::changed_1()
{
  if (ui->pushButton1_2->text()=="")
  {
      ui->pushButton1_2->setText(ui->pushButton1_1->text());
      ui->pushButton1_1->setText("");
  }
  if (ui->pushButton1_5->text()=="")
  {
      ui->pushButton1_5->setText(ui->pushButton1_1->text());
      ui->pushButton1_1->setText("");
  }
  if(is_win()){ emit game_over();}
}
void MainWindow::changed_2()
{
  if (ui->pushButton1_1->text()=="")
  {
      ui->pushButton1_1->setText(ui->pushButton1_2->text());
      ui->pushButton1_2->setText("");
  }
  if (ui->pushButton1_3->text()=="")
  {
      ui->pushButton1_3->setText(ui->pushButton1_2->text());
      ui->pushButton1_2->setText("");
  }
  if (ui->pushButton1_6->text()=="")
  {
      ui->pushButton1_6->setText(ui->pushButton1_2->text());
      ui->pushButton1_2->setText("");
  }
  if(is_win()){ emit game_over();}
}
void MainWindow::changed_3()
{
  if (ui->pushButton1_2->text()=="")
  {
      ui->pushButton1_2->setText(ui->pushButton1_3->text());
      ui->pushButton1_3->setText("");
  }
  if (ui->pushButton1_4->text()=="")
  {
      ui->pushButton1_4->setText(ui->pushButton1_3->text());
      ui->pushButton1_3->setText("");
  }
  if (ui->pushButton1_7->text()=="")
  {
      ui->pushButton1_7->setText(ui->pushButton1_3->text());
      ui->pushButton1_3->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_4()
{
  if (ui->pushButton1_3->text()=="")
  {
      ui->pushButton1_3->setText(ui->pushButton1_4->text());
      ui->pushButton1_4->setText("");
  }
  if (ui->pushButton1_8->text()=="")
  {
      ui->pushButton1_8->setText(ui->pushButton1_4->text());
      ui->pushButton1_4->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_5()
{
  if (ui->pushButton1_1->text()=="")
  {
      ui->pushButton1_1->setText(ui->pushButton1_5->text());
      ui->pushButton1_5->setText("");
  }
  if (ui->pushButton1_6->text()=="")
  {
      ui->pushButton1_6->setText(ui->pushButton1_5->text());
      ui->pushButton1_5->setText("");
  }
  if (ui->pushButton1_9->text()=="")
  {
      ui->pushButton1_9->setText(ui->pushButton1_5->text());
      ui->pushButton1_5->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_6()
{
  if (ui->pushButton1_2->text()=="")
  {
      ui->pushButton1_2->setText(ui->pushButton1_6->text());
      ui->pushButton1_6->setText("");
  }
  if (ui->pushButton1_5->text()=="")
  {
      ui->pushButton1_5->setText(ui->pushButton1_6->text());
      ui->pushButton1_6->setText("");
  }
  if (ui->pushButton1_7->text()=="")
  {
      ui->pushButton1_7->setText(ui->pushButton1_6->text());
      ui->pushButton1_6->setText("");
  }
  if (ui->pushButton1_10->text()=="")
  {
      ui->pushButton1_10->setText(ui->pushButton1_6->text());
      ui->pushButton1_6->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_7()
{
  if (ui->pushButton1_3->text()=="")
  {
      ui->pushButton1_3->setText(ui->pushButton1_7->text());
      ui->pushButton1_7->setText("");
  }
  if (ui->pushButton1_6->text()=="")
  {
      ui->pushButton1_6->setText(ui->pushButton1_7->text());
      ui->pushButton1_7->setText("");
  }
  if (ui->pushButton1_8->text()=="")
  {
      ui->pushButton1_8->setText(ui->pushButton1_7->text());
      ui->pushButton1_7->setText("");
  }
  if (ui->pushButton1_11->text()=="")
  {
      ui->pushButton1_11->setText(ui->pushButton1_7->text());
      ui->pushButton1_7->setText("");
  }
  if(is_win()){ emit game_over();}
}


void MainWindow::changed_8()
{
  if (ui->pushButton1_4->text()=="")
  {
      ui->pushButton1_4->setText(ui->pushButton1_8->text());
      ui->pushButton1_8->setText("");
  }
  if (ui->pushButton1_7->text()=="")
  {
      ui->pushButton1_7->setText(ui->pushButton1_8->text());
      ui->pushButton1_8->setText("");
  }
  if (ui->pushButton1_12->text()=="")
  {
      ui->pushButton1_12->setText(ui->pushButton1_8->text());
      ui->pushButton1_8->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_9()
{
  if (ui->pushButton1_5->text()=="")
  {
      ui->pushButton1_5->setText(ui->pushButton1_9->text());
      ui->pushButton1_9->setText("");
  }
  if (ui->pushButton1_10->text()=="")
  {
      ui->pushButton1_10->setText(ui->pushButton1_9->text());
      ui->pushButton1_9->setText("");
  }
  if (ui->pushButton1_13->text()=="")
  {
      ui->pushButton1_13->setText(ui->pushButton1_9->text());
      ui->pushButton1_9->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_10()
{
  if (ui->pushButton1_6->text()=="")
  {
      ui->pushButton1_6->setText(ui->pushButton1_10->text());
      ui->pushButton1_10->setText("");
  }
  if (ui->pushButton1_9->text()=="")
  {
      ui->pushButton1_9->setText(ui->pushButton1_10->text());
      ui->pushButton1_10->setText("");
  }
  if (ui->pushButton1_11->text()=="")
  {
      ui->pushButton1_11->setText(ui->pushButton1_10->text());
      ui->pushButton1_10->setText("");
  }
  if (ui->pushButton1_14->text()=="")
  {
      ui->pushButton1_14->setText(ui->pushButton1_10->text());
      ui->pushButton1_10->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_11()
{
  if (ui->pushButton1_7->text()=="")
  {
      ui->pushButton1_7->setText(ui->pushButton1_11->text());
      ui->pushButton1_11->setText("");
  }
  if (ui->pushButton1_10->text()=="")
  {
      ui->pushButton1_10->setText(ui->pushButton1_11->text());
      ui->pushButton1_11->setText("");
  }
  if (ui->pushButton1_12->text()=="")
  {
      ui->pushButton1_12->setText(ui->pushButton1_11->text());
      ui->pushButton1_11->setText("");
  }
  if (ui->pushButton1_15->text()=="")
  {
      ui->pushButton1_15->setText(ui->pushButton1_11->text());
      ui->pushButton1_11->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_12()
{
  if (ui->pushButton1_8->text()=="")
  {
      ui->pushButton1_8->setText(ui->pushButton1_12->text());
      ui->pushButton1_12->setText("");
  }
  if (ui->pushButton1_11->text()=="")
  {
      ui->pushButton1_11->setText(ui->pushButton1_12->text());
      ui->pushButton1_12->setText("");
  }
  if (ui->pushButton1_16->text()=="")
  {
      ui->pushButton1_16->setText(ui->pushButton1_12->text());
      ui->pushButton1_12->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_13()
{
  if (ui->pushButton1_9->text()=="")
  {
      ui->pushButton1_9->setText(ui->pushButton1_13->text());
      ui->pushButton1_13->setText("");
  }
  if (ui->pushButton1_14->text()=="")
  {
      ui->pushButton1_14->setText(ui->pushButton1_13->text());
      ui->pushButton1_13->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_14()
{
  if (ui->pushButton1_10->text()=="")
  {
      ui->pushButton1_10->setText(ui->pushButton1_14->text());
      ui->pushButton1_14->setText("");
  }
  if (ui->pushButton1_13->text()=="")
  {
      ui->pushButton1_13->setText(ui->pushButton1_14->text());
      ui->pushButton1_14->setText("");
  }
  if (ui->pushButton1_15->text()=="")
  {
      ui->pushButton1_15->setText(ui->pushButton1_14->text());
      ui->pushButton1_14->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_15()
{
  if (ui->pushButton1_11->text()=="")
  {
      ui->pushButton1_11->setText(ui->pushButton1_15->text());
      ui->pushButton1_15->setText("");
  }
  if (ui->pushButton1_14->text()=="")
  {
      ui->pushButton1_14->setText(ui->pushButton1_15->text());
      ui->pushButton1_15->setText("");

  }
  if (ui->pushButton1_16->text()=="")
  {
      ui->pushButton1_16->setText(ui->pushButton1_15->text());
      ui->pushButton1_15->setText("");
  }
  if(is_win()){ emit game_over();}
}

void MainWindow::changed_16()
{
    if (ui->pushButton1_12->text()=="")
    {
        ui->pushButton1_12->setText(ui->pushButton1_16->text());
        ui->pushButton1_16->setText("");
    }
    if (ui->pushButton1_15->text()=="")
    {
        ui->pushButton1_15->setText(ui->pushButton1_16->text());
        ui->pushButton1_16->setText("");
    }
    if(is_win()){ emit game_over();}
}
