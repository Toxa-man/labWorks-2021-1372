#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "mainwindowend.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend MainWindowEnd;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void redrawing(); //перерисовываем поле
    bool is_win(); //проверяем поле на правильность собранных пятнашек

signals:
    void game_over();

private:
    Ui::MainWindow *ui;
    MainWindowEnd *w_end;
    void mix_cell(); //миксуем пятнашки в начале игры
    void set_name_cell(vector <size_t> name_cell); //присваиваем клеточкам их номера
    vector <size_t> name_cell; //числовой массив с номерами
    QString *name_cell_str; //строковый массив с номерами
    const size_t size=4; // "высота" доски
    const size_t count_cell=size*size; //количество клеток на доске

private slots:
    //слоты для каждой из кнопок
    void changed_1();
    void changed_2();
    void changed_3();
    void changed_4();
    void changed_5();
    void changed_6();
    void changed_7();
    void changed_8();
    void changed_9();
    void changed_10();
    void changed_11();
    void changed_12();
    void changed_13();
    void changed_14();
    void changed_15();
    void changed_16();
    void changed_complete(); //слот, позволяющий выйти из игры
    void other_game(); //слот, перерисовывающий поле для новой игры
    void game_over_with_win(); //слот, завершающий игру, если доска собрана правильно
};
#endif // MAINWINDOW_H
