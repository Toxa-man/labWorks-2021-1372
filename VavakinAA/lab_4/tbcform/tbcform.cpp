#include "tbcform.h"
#include "ui_tbcform.h"
#include "character.h"
#include <QMessageBox>
#include <QRegularExpression>

TBCform::TBCform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TBCform)
{
    ui->setupUi(this);
}

TBCform::~TBCform()
{
    delete ui;
}

enum Action { Attack, Defend, Wait};
Character player;
Character enemy;
QRegularExpression sep("(\\s+)");

void TBCform::receive_character(QString character)
{
    QStringList info = character.split(sep);
    QStringList character_info = strlist_parse_character(info);
    player.set_character(character_info);
    int PlayerHP = player.get_hp();
    ui->PlayerHP->setMaximum(PlayerHP);
    ui->PlayerHP->setValue(PlayerHP);
    ui->PlayerEP->setMaximum(100);
    ui->PlayerEP->setValue(100);
}

void TBCform::receive_character_file(QString file_name)
{
    QFile character(file_name);
    QStringList character_info = parse_character(character);
    player.set_character(character_info);
    int PlayerHP = player.get_hp();
    ui->PlayerHP->setMaximum(PlayerHP);
    ui->PlayerHP->setValue(PlayerHP);
    ui->PlayerEP->setMaximum(100);
    ui->PlayerEP->setValue(100);
}

void TBCform::pick_opponent_msg(){
    QMessageBox msg;
    QString tmpStyleSheet=this->styleSheet();
    msg.setStyleSheet(tmpStyleSheet);
    msg.setText("Pick your opponent!");
    msg.setWindowTitle("Path of Hero");
    const QIcon icon(":/resources/img/icon.ico");
    msg.setWindowIcon(icon);
    msg.setIcon(QMessageBox::Warning);
    msg.exec();
}

void TBCform::no_energy_msg(){
    QMessageBox msg;
    QString tmpStyleSheet=this->styleSheet();
    msg.setStyleSheet(tmpStyleSheet);
    msg.setText("Not enough energy for this action!");
    msg.setWindowTitle("Path of Hero");
    const QIcon icon(":/resources/img/icon.ico");
    QPixmap energy_icon(":/resources/img/energy.ico");
    msg.setWindowIcon(icon);
    msg.setIconPixmap(energy_icon);
    msg.exec();
}

void TBCform::victory_msg(){
    QMessageBox msg;
    QString tmpStyleSheet=this->styleSheet();
    msg.setStyleSheet(tmpStyleSheet);
    msg.setText("Gratz! You defeated your enemy");
    msg.setWindowTitle("Path of Hero");
    const QIcon icon(":/resources/img/icon.ico");
    QPixmap victory_icon(":/resources/img/victory.ico");
    msg.setWindowIcon(icon);
    msg.setIconPixmap(victory_icon);
    msg.exec();
}

void TBCform::defeat_msg(){
    QMessageBox msg;
    QString tmpStyleSheet=this->styleSheet();
    msg.setStyleSheet(tmpStyleSheet);
    msg.setText("Oh no! You lost this fight");
    msg.setWindowTitle("Path of Hero");
    const QIcon icon(":/resources/img/icon.ico");
    QPixmap defeat_icon(":/resources/img/defeat.ico");
    msg.setWindowIcon(icon);
    msg.setIconPixmap(defeat_icon);
    msg.exec();
}

char TBCform::decision(){
    if(ui->radioButton_1->isChecked()){
        return '1';
    }
    else if (ui->radioButton_2->isChecked()){
        return '2';
    }
    else if (ui->radioButton_3->isChecked()){
        return '3';
    }
    return '0';
}

void TBCform::reset_combat()
{
    int PlayerHP = player.get_hp();
    enemy.reset_character();
    ui->EnemyHP->setMaximum(100);
    ui->EnemyHP->setValue(0);
    ui->EnemyEP->setValue(0);
    ui->PlayerHP->setMaximum(PlayerHP);
    ui->PlayerHP->setValue(PlayerHP);
    ui->PlayerEP->setValue(100);
}

void TBCform::check_endgame()
{
    if (ui->PlayerHP->value() == 0){
        defeat_msg();
        reset_combat();
    }
    else if (ui->EnemyHP->value() == 0){
        victory_msg();
        reset_combat();
    }
}

QStringList TBCform::parse_character(QFile& character_info){
    character_info.open(QIODevice::ReadOnly);
    QByteArray info = character_info.readAll();
    QStringList info_list = QString(info).split(sep);
    QStringList sorted_info;
    for (int i = 0;i < info_list.size(); i++){
        if (i % 2 == 1){
            sorted_info.append(info_list[i]);
        }
    }
    return sorted_info;
}

QStringList TBCform::strlist_parse_character(QStringList& character_info){
    QStringList sorted_info;
    for (int i = 0;i < character_info.size(); i++){
        if (i % 2 == 1){
            sorted_info.append(character_info[i]);
        }
    }
    return sorted_info;
}

void TBCform::enemy_attack(){
    int change_seed = (-100000 + rand() % 200000);
    srand(time(NULL) + change_seed);
    int random_damage = (((rand() % player.get_max_stat())) / 50);
    int base_damage = 30;
    int damage = base_damage + random_damage;
    int energy_consumption = 20;

    if (player.is_damage_reduction_active){
        damage = damage * (1 - enemy.incoming_damage_reduction);
        player.is_damage_reduction_active = false;
    }

    if(damage >  ui->PlayerHP->value()){
        ui->PlayerHP->setValue(0);
    }
    else{
       ui->PlayerHP->setValue(ui->PlayerHP->value() - damage);
    }

    ui->EnemyEP->setValue(ui->EnemyEP->value() - energy_consumption);

    ui->Console->append("[Enemy] Dealt " + QString::number(damage) + " damage to opponent");
}

void TBCform::enemy_defend(){
    int energy_recover = 10;

    enemy.is_damage_reduction_active = true;
    ui->EnemyEP->setValue(ui->EnemyEP->value() + energy_recover);
    ui->Console->append("[Enemy] Incoming damage reduced");
}

void TBCform::enemy_wait(){
    int energy_recover = 30;
    if ((ui->EnemyEP->value() + energy_recover) > ui->EnemyEP->maximum()){
        ui->EnemyEP->setValue(ui->EnemyEP->maximum());
    }
    else{
        ui->EnemyEP->setValue(ui->EnemyEP->value() + energy_recover);
    }

    ui->Console->append("[Enemy] Recovered " + QString::number(energy_recover) + " energy");
}

void TBCform::enemy_turn(){
    int action;// Attack = 0, Defend = 1, Wait = 2;
    int min_energy = 20;
    int energy_to_defend = 30;

    if(ui->EnemyEP->value() < min_energy){
        action = Wait;
    }

    else if(ui->EnemyHP->value() < ui->EnemyHP->maximum() * 0.3 && ui->EnemyEP->value() <= energy_to_defend){
        int choose_action = rand() % 2;
        switch (choose_action)
        {
        case Attack: action = Attack;
            break;
        case Defend: action = Defend;
            break;
        }
    }

    else{
        action = Attack;
    }

    switch (action)
    {
    case Attack: enemy_attack();
        break;
    case Defend: enemy_defend();
        break;
    case Wait: enemy_wait();
        break;
    }
}

void TBCform::player_attack(){
    int change_seed = (-100000 + rand() % 200000);
    srand(time(NULL) + change_seed);
    int random_damage = (((rand() % player.get_max_stat())) / 50);
    int base_damage = 30;
    int damage = base_damage + random_damage;
    int energy_consumption = 20;

    if (energy_consumption > ui->PlayerEP->value()){
        no_energy_msg();
        return;
    }

    if (enemy.is_damage_reduction_active){
        damage = damage * (1 - enemy.incoming_damage_reduction);
        enemy.is_damage_reduction_active = false;
    }

    if(damage >  ui->EnemyHP->value()){
        ui->EnemyHP->setValue(0);
    }
    else{
       ui->EnemyHP->setValue(ui->EnemyHP->value() - damage);
    }

    ui->PlayerEP->setValue(ui->PlayerEP->value() - energy_consumption);

    ui->Console->append("[You] Dealt " + QString::number(damage) + " damage to opponent");

    if(ui->EnemyHP->value() == 0){
        return;
    }

    enemy_turn();
}

void TBCform::player_defend(){
    int energy_recover = 10;

    player.is_damage_reduction_active = true;
    ui->PlayerEP->setValue(ui->PlayerEP->value() + energy_recover);

    ui->Console->append("[You] Incoming damage reduced");

    enemy_turn();
}

void TBCform::player_wait(){
    int energy_recover = 30;
    if ((ui->PlayerEP->value() + energy_recover) > ui->PlayerEP->maximum()){
        ui->PlayerEP->setValue(ui->PlayerEP->maximum());
    }
    else{
        ui->PlayerEP->setValue(ui->PlayerEP->value() + energy_recover);
    }

    ui->Console->append("[You] Recovered " + QString::number(energy_recover) + " energy");

    enemy_turn();
}

void TBCform::on_AttackButton_clicked()
{
    if ((ui->EnemyHP->value() == 0) && (ui->EnemyEP->value() == 0)){
        pick_opponent_msg();
        return;
    }

    player_attack();

    check_endgame();
}

void TBCform::on_DefendButton_clicked()
{
    if ((ui->EnemyHP->value() == 0) && (ui->EnemyEP->value() == 0)){
        pick_opponent_msg();
        return;
    }

    player_defend();

    check_endgame();
}

void TBCform::on_WaitButton_clicked()
{
    if ((ui->EnemyHP->value() == 0) && (ui->EnemyEP->value() == 0)){
        pick_opponent_msg();
        return;
    }

    player_wait();

    check_endgame();
}


void TBCform::on_PickOpponentButton_clicked()
{
    char EnemyID = decision();
    QFile Alexandro(":/resources/txt/Alexandro.txt");
    QFile Christina(":/resources/txt/Christina.txt");
    QFile Karen(":/resources/txt/Karen.txt");
    QStringList character_info;
    switch(EnemyID)
    {
    case '1':character_info = parse_character(Alexandro);
        enemy.set_character(character_info);
        break;
    case '2':character_info = parse_character(Christina);
        enemy.set_character(character_info);
        break;
    case '3':character_info = parse_character(Karen);
        enemy.set_character(character_info);
        break;
    }
    int EnemyHP = enemy.get_hp();
    int PlayerHP = player.get_hp();

    ui->EnemyHP->setMaximum(EnemyHP);
    ui->EnemyHP->setValue(EnemyHP);
    ui->EnemyEP->setMaximum(100);
    ui->EnemyEP->setValue(100);

    ui->PlayerHP->setMaximum(PlayerHP);
    ui->PlayerHP->setValue(PlayerHP);
    ui->PlayerEP->setMaximum(100);
    ui->PlayerEP->setValue(100);

    ui->Console->clear();
}

void TBCform::on_MenuButton_clicked()
{
    emit tbcform_close();
    ui->Console->clear();
    this->close();
}

void TBCform::on_QuitButton_clicked()
{
    QApplication::quit();
}
