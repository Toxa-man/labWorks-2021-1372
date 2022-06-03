#ifndef TBCFORM_H
#define TBCFORM_H

#include <QWidget>
#include <QFile>

namespace Ui {
class TBCform;
}

class TBCform : public QWidget
{
    Q_OBJECT

public:
    explicit TBCform(QWidget *parent = nullptr);
    ~TBCform();

public slots:
    void receive_character(QString character);
    void receive_character_file(QString file_name);

private slots:
    char decision();
    QStringList parse_character(QFile& character_info);
    QStringList strlist_parse_character(QStringList& character_info);
    void pick_opponent_msg();
    void victory_msg();
    void defeat_msg();
    void no_energy_msg();

    void reset_combat();
    void check_endgame();

    void player_attack();
    void player_defend();
    void player_wait();
    void enemy_turn();
    void enemy_attack();
    void enemy_defend();
    void enemy_wait();

    void on_AttackButton_clicked();
    void on_DefendButton_clicked();
    void on_WaitButton_clicked();
    void on_PickOpponentButton_clicked();
    void on_QuitButton_clicked();
    void on_MenuButton_clicked();

private:
    Ui::TBCform *ui;

signals:
    void tbcform_close();
};

#endif // TBCFORM_H
