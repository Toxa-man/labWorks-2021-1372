#ifndef EXPERTSYSTEM_H
#define EXPERTSYSTEM_H

#include <QWidget>


namespace Ui {
class ExpertSystem;
}

class ExpertSystem : public QWidget
{
    Q_OBJECT

public:
    explicit ExpertSystem(QWidget *parent = nullptr);
    ~ExpertSystem();


private slots:
    char decision();
    void set_choice(size_t);
    void waitSubmitButton();
    void save_hero();

    void begining_1();
    void begining_2();
    void begining_3();
    void begining_4();
    void gender_choice();
    void origin();
    void peasant_way();
    void find_someone();
    void keep_waiting();
    void examine_bug();
    void noble_way();
    void studying();
    void kaleidoscope();
    void rest();
    void orphan_way();
    void steal_food();
    void work_for_food();
    void begging();
    void go_plains();
    void go_mountain();
    void go_house();
    void smash_bug();
    void collect_bug();
    void release_bug();
    void continue_studying();
    void give_up_studying();
    void recall_kaleidoscope();
    void studying_after_kaleidoscope();
    void disassemble_kaleidoscope();
    void rest_after_kaleidoscope();
    void back_to_sleep();
    void studying_after_rest();
    void run_away();
    void come_what_may();
    void making_excuses();
    void help_herbalist();
    void help_tanner();
    void help_miner();
    void accept_offer();
    void reject_offer();
    void say_nothing();
    void fin();

    void on_SubmitButton_clicked();
    void on_ResetButton_clicked();

private:
    Ui::ExpertSystem *ui;

signals:
    void send_character(QString);
};

#endif // EXPERTSYSTEM_Hs
