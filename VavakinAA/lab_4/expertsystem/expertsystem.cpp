#include "expertsystem.h"
#include "character.h"
#include "./ui_expertsystem.h"
#include <QFile>
#include <QTime>
#include <QDir>
#include <QTextStream>

ExpertSystem::ExpertSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpertSystem)
{
    ui->setupUi(this);
}

ExpertSystem::~ExpertSystem()
{
    delete ui;
}

Character hero;

char ExpertSystem::decision() {
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

void ExpertSystem::set_choice(size_t num){
    ui->radioButton_1->setChecked(true);
    switch(num)
    {
    case 0:
        ui->radioButton_1->hide();
        ui->radioButton_2->hide();
        ui->radioButton_3->hide();
        break;
    case 1:
        ui->radioButton_1->show();
        ui->radioButton_2->hide();
        ui->radioButton_3->hide();
        break;
    case 2:
        ui->radioButton_1->show();
        ui->radioButton_2->show();
        ui->radioButton_3->hide();
        break;
    case 3:
        ui->radioButton_1->show();
        ui->radioButton_2->show();
        ui->radioButton_3->show();
        break;
    }
}


void ExpertSystem::save_hero() {
    QString path("saves\\");
    QDir dir;

    if (!dir.exists(path)){
        dir.mkpath(path);
    }

    QFile outf(path + (QDateTime::currentDateTime()).toString().replace(':','-') + ".txt");
    hero.save_to_file(outf);
    outf.close();
}

void ExpertSystem::waitSubmitButton(){
    QEventLoop loop;
    QObject::connect(ui->SubmitButton, SIGNAL(pressed()), &loop, SLOT(quit()));
    QObject::connect(ui->ResetButton, SIGNAL(pressed()), &loop, SLOT(quit()));
    loop.exec();
}

void ExpertSystem::begining_1() {
    ui->SubmitButton->setText("Submit");
    set_choice(2);
    ui->NextEventLabel->setText("begining_2");
    ui->TextLabel->setText("Have you ever played MMORPG?");
    ui->radioButton_1->setText("Yes");
    ui->radioButton_2->setText("No");

    waitSubmitButton();

    switch (decision())
    {
    case '1':
        break;
    case '2': hero.modify_stats_multiplier(Agility, -0.1);
        break;
    }
    ui->radioButton_1->setChecked(true);
}

void ExpertSystem::begining_2() {
    set_choice(2);
    ui->NextEventLabel->setText("begining_3");
    ui->TextLabel->setText("Do you prefer to attack in melee or at long range?");
    ui->radioButton_1->setText("Melee");
    ui->radioButton_2->setText("Long range");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats_multiplier(Strength, 0.1);
        hero.modify_stats_multiplier(Agility, 0.05);
        hero.modify_stats_multiplier(Intelligence, -0.1);
        break;
    case '2': hero.modify_stats_multiplier(Strength, -0.1);
        hero.modify_stats_multiplier(Intelligence, 0.1);
        break;
    }
}

void ExpertSystem::begining_3() {
    set_choice(3);
    ui->NextEventLabel->setText("begining_4");
    ui->TextLabel->setText("Are you more attracted to mysterious magic or the sound of steel?");
    ui->radioButton_1->setText("Mysterious magic");
    ui->radioButton_2->setText("Sound of steel");
    ui->radioButton_3->setText("I don't like anything");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats_multiplier(Intelligence, 0.1);
        break;
    case '2': hero.modify_stats_multiplier(Strength, 0.1);
        break;
    case '3': hero.modify_stats_multiplier(Agility, 0.1);
        break;
    }
}

void ExpertSystem::begining_4() {
    set_choice(3);
    ui->NextEventLabel->setText("gender_choice");
    ui->TextLabel->setText("What you can associate yourself with: a motionless rock, a rebel wind or light in the dark?");
    ui->radioButton_1->setText("Rock");
    ui->radioButton_2->setText("Wind");
    ui->radioButton_3->setText("Light");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats_multiplier(Agility, -0.15);
        hero.modify_stats_multiplier(Strength, 0.1);
        break;
    case '2': hero.modify_stats_multiplier(Agility, 0.15);
        hero.modify_stats_multiplier(Strength, -0.1);
        break;
    case '3': hero.modify_stats_multiplier(Intelligence, 0.1);
        hero.modify_stats_multiplier(Strength, -0.15);
        hero.modify_stats_multiplier(Agility, 0.05);
        break;
    }
}

void ExpertSystem::gender_choice() {
    set_choice(2);
    ui->NextEventLabel->setText("origin");
    ui->TextLabel->setText("What gender is your character?");
    ui->radioButton_1->setText("Male");
    ui->radioButton_2->setText("Female");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.set_gender("Male");
        break;
    case '2': hero.set_gender("Female");
        break;
    }
}

void ExpertSystem::origin() {
    set_choice(3);
    ui->TextLabel->setText("What is your origin?");
    ui->radioButton_1->setText("Peasant");
    ui->radioButton_2->setText("Noble");
    ui->radioButton_3->setText("Orphan");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Strength, 2);
        ui->NextEventLabel->setText("peasant_way");
        break;
    case '2': hero.modify_stats(Intelligence, 2);
        ui->NextEventLabel->setText("noble_way");
        break;
    case '3': hero.modify_stats(Agility, 2);
        ui->NextEventLabel->setText("orphan_way");
        break;
    }
}

void ExpertSystem::peasant_way() {
    set_choice(3);
    ui->TextLabel->setText("You play hide-and-seek with the other kids in the neighbourhood, but they don't find you for a long time. A small bug crawls past you. What will you do?");
    ui->radioButton_1->setText("Try to find someone you know");
    ui->radioButton_2->setText("Keep waiting");
    ui->radioButton_3->setText("Examine a bug");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Agility, 2);
        hero.modify_race_points(Human, 2);
        hero.modify_race_points(Orc, 1);
        ui->NextEventLabel->setText("find_someone");
        break;
    case '2': hero.modify_stats(Agility, -1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("keep_waiting");
        break;
    case '3': hero.modify_stats(Intelligence, 2);
        hero.modify_race_points(Elf, 2);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("examine_bug");
        break;
    }
}

void ExpertSystem::find_someone() {
    set_choice(3);
    ui->TextLabel->setText("You find your buddies. They really forgot about you, so it was the right decision. Now it's your turn to seek. Where will you start your search?");
    ui->radioButton_1->setText("Plains");
    ui->radioButton_2->setText("Huge mountain");
    ui->radioButton_3->setText("Nearest house");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_profession_points(Herbalist, 1);
        hero.modify_race_points(Elf, 1);
        hero.modify_race_points(Human, 1);
        hero.modify_stats(Intelligence, -1);
        ui->NextEventLabel->setText("go_plains");
        break;
    case '2': hero.modify_stats(Agility, 1);
        hero.modify_profession_points(Miner, 1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_race_points(Human, 1);
        hero.modify_race_points(Orc, 1);
        ui->NextEventLabel->setText("go_mountain");
        break;
    case '3': hero.modify_stats(Strength, 1);
        hero.modify_profession_points(Tanner, 1);
        hero.modify_race_points(Dwarf, 1);
        hero.modify_race_points(Elf, 1);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("go_house");
        break;
    }
}

void ExpertSystem::keep_waiting() {
    set_choice(3);
    ui->TextLabel->setText("No one found you, so you just wasted your time. Now it's your turn to seek. Where will you start your search?");
    ui->radioButton_1->setText("Plains");
    ui->radioButton_2->setText("Huge mountain");
    ui->radioButton_3->setText("Nearest house");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_profession_points(Herbalist, 1);
        hero.modify_race_points(Elf, 1);
        hero.modify_race_points(Human, 1);
        hero.modify_stats(Intelligence, -1);
        ui->NextEventLabel->setText("go_plains");
        break;
    case '2': hero.modify_stats(Agility, 1);
        hero.modify_profession_points(Miner, 1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_race_points(Human, 1);
        hero.modify_race_points(Orc, 1);
        ui->NextEventLabel->setText("go_mountain");
        break;
    case '3': hero.modify_stats(Strength, 1);
        hero.modify_profession_points(Tanner, 1);
        hero.modify_race_points(Dwarf, 1);
        hero.modify_race_points(Elf, 1);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("go_house");
        break;
    }
}

void ExpertSystem::examine_bug() {
    set_choice(3);
    ui->TextLabel->setText("The bug turned out to be quite ordinary and unremarkable. Common. Useless. Bug. His fate is in your hands!");
    ui->radioButton_1->setText("Smash");
    ui->radioButton_2->setText("Collect in a jar");
    ui->radioButton_3->setText("Release");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Strength, 2);
        hero.modify_race_points(Orc, 2);
        hero.modify_race_points(Dwarf, 1);
        hero.modify_race_points(Elf, -1);
        ui->NextEventLabel->setText("smash_bug");
        break;
    case '2': hero.modify_stats(Agility, 1);
        hero.modify_profession_points(Miner, 1);
        hero.modify_race_points(Elf, 2);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("collect_bug");
        break;
    case '3': hero.modify_stats(Agility, 1);
        hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Human, 2);
        hero.modify_race_points(Dwarf, 1);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("release_bug");
        break;
    }
}

void ExpertSystem::noble_way() {
    set_choice(3);
    ui->TextLabel->setText("The life of a young nobleman is complicated. Today you have to study mathematical sciences. Suddenly your eyes are interested in an unusual toy - a kaleidoscope. What will be your priority?");
    ui->radioButton_1->setText("Studying");
    ui->radioButton_2->setText("Kaleidoscope");
    ui->radioButton_3->setText("Rest");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_race_points(Elf, 2);
        hero.modify_race_points(Human, 1);
        hero.modify_stats(Intelligence, 2);
        ui->NextEventLabel->setText("studying");
        break;
    case '2': hero.modify_stats(Intelligence, 1);
        hero.modify_stats(Strength, -1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_race_points(Human, 1);
        hero.modify_race_points(Elf, 1);
        ui->NextEventLabel->setText("kaleidoscope");
        break;
    case '3': hero.modify_stats(Strength, 1);
        hero.modify_hp(1);
        hero.modify_race_points(Orc, 2);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("rest");
        break;
    }
}

void ExpertSystem::studying() {
    set_choice(3);
    ui->TextLabel->setText("You feel very tired. Will you give up the case halfway through or will you continue?");
    ui->radioButton_1->setText("Continue");
    ui->radioButton_2->setText("Give up");
    ui->radioButton_3->setText("Recall a kaleidoscope");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_profession_points(Herbalist, 1);
        hero.modify_race_points(Elf, 1);
        hero.modify_stats(Intelligence, 1);
        ui->NextEventLabel->setText("continue_studying");
        break;
    case '2': hero.modify_stats(Intelligence, -1);
        hero.modify_stats(Agility, 2);
        hero.modify_race_points(Human, 1);
        hero.modify_race_points(Orc, 2);
        ui->NextEventLabel->setText("give_up_studying");
        break;
    case '3': hero.modify_stats(Agility, 1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_race_points(Elf, 1);
        ui->NextEventLabel->setText("recall_kaleidoscope");
        break;
    }
}

void ExpertSystem::kaleidoscope() {
    set_choice(3);
    ui->TextLabel->setText("An amazing world of colorful glasses opens up in front of you. Time passes unnoticed, it's already evening. How will you spend the rest of the day?");
    ui->radioButton_1->setText("Back to studying");
    ui->radioButton_2->setText("Disassemble a kaleidoscope");
    ui->radioButton_3->setText("Rest");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Elf, 2);
        ui->NextEventLabel->setText("studying_after_kaleidoscope");
        break;
    case '2': hero.modify_stats(Agility, 1);
        hero.modify_race_points(Dwarf, 1);
        ui->NextEventLabel->setText("disassemble_kaleidoscope");
        break;
    case '3': hero.modify_stats(Strength, 1);
        hero.modify_race_points(Human, 1);
        hero.modify_race_points(Orc, 1);
        hero.modify_race_points(Dwarf, -1);
        ui->NextEventLabel->setText("rest_after_kaleidoscope");
        break;
    }
}

void ExpertSystem::rest() {
    set_choice(3);
    ui->TextLabel->setText("You decided to lie down on the bed and instantly fall asleep.Time passes unnoticed, it's already evening. How will you spend the rest of the day?");
    ui->radioButton_1->setText("Back to sleep");
    ui->radioButton_2->setText("Recall a kaleidoscope");
    ui->radioButton_3->setText("Back to studying");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_hp(1);
        hero.modify_race_points(Orc, 1);
        hero.modify_race_points(Dwarf, 1);
        ui->NextEventLabel->setText("back_to_sleep");
        break;
    case '2': hero.modify_stats(Agility, 1);
        hero.modify_race_points(Dwarf, 1);
        ui->NextEventLabel->setText("recall_kaleidoscope");
        break;
    case '3': hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Elf, 1);
        ui->NextEventLabel->setText("studying_after_rest");
        break;
    }
}

void ExpertSystem::orphan_way() {
    set_choice(3);
    ui->TextLabel->setText("From an early age, you had to feed yourself. It's not so easy to find food while you living on the streets. You haven't eaten for 3 days. What are you going to do?");
    ui->radioButton_1->setText("Steal something from the nearest store");
    ui->radioButton_2->setText("Work for food");
    ui->radioButton_3->setText("Begging from someone passing by");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Agility, 2);
        hero.modify_race_points(Orc, 2);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("steal_food");
        break;
    case '2': hero.modify_stats(Strength, 1);
        hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Dwarf, 2);
        hero.modify_race_points(Elf, 1);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("work_for_food");
        break;
    case '3': hero.modify_stats(Agility, 1);
        hero.modify_stats(Strength, -1);
        hero.modify_race_points(Human, 1);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("begging");
        break;
    }
}

void ExpertSystem::steal_food() {
    set_choice(3);
    ui->TextLabel->setText("The seller grabs your hand when you tried to steal apples. What are you going to do?");
    ui->radioButton_1->setText("Run away");
    ui->radioButton_2->setText("Come what may");
    ui->radioButton_3->setText("Making excuses");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Agility, 1);
        hero.modify_race_points(Human, 2);
        hero.modify_race_points(Elf, 1);
        ui->NextEventLabel->setText("run_away");
        break;
    case '2': hero.modify_stats(Strength, 1);
        hero.modify_hp(1);
        hero.modify_race_points(Orc, 1);
        hero.modify_race_points(Dwarf, 1);
        ui->NextEventLabel->setText("come_what_may");
        break;
    case '3': hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Orc, -1);
        hero.modify_race_points(Elf, 2);
        hero.modify_hp(1);
        ui->NextEventLabel->setText("making_excuses");
        break;
    }
}

void ExpertSystem::work_for_food() {
    set_choice(3);
    ui->TextLabel->setText("You have a choice of whom to ask for a job.");
    ui->radioButton_1->setText("Herbalist");
    ui->radioButton_2->setText("Tanner");
    ui->radioButton_3->setText("Miner");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Intelligence, 1);
        hero.modify_race_points(Human, 2);
        hero.modify_hp(1);
        hero.modify_profession_points(Herbalist, 1);
        ui->NextEventLabel->setText("help_herbalist");
        break;
    case '2': hero.modify_stats(Agility, 2);
        hero.modify_hp(1);
        hero.modify_profession_points(Tanner, 1);
        hero.modify_race_points(Orc, 2);
        hero.modify_race_points(Dwarf, -1);
        ui->NextEventLabel->setText("help_tanner");
        break;
    case '3': hero.modify_stats(Strength, 2);
        hero.modify_hp(1);
        hero.modify_race_points(Dwarf, 1);
        hero.modify_profession_points(Miner, 1);
        ui->NextEventLabel->setText("help_miner");
    }
}

void ExpertSystem::begging() {
    set_choice(3);
    ui->TextLabel->setText("One of the wanderers notices you. Slowly approaches and offers to go with him? What do you say to the offer?");
    ui->radioButton_1->setText("Accept");
    ui->radioButton_2->setText("Reject");
    ui->radioButton_3->setText("Say nothing");

    waitSubmitButton();

    switch (decision())
    {
    case '1': hero.modify_stats(Intelligence, 1);
        hero.modify_stats(Agility, 1);
        hero.modify_race_points(Human, 1);
        ui->NextEventLabel->setText("accept_offer");
        break;
    case '2': hero.modify_stats(Strength, 1);
        hero.modify_race_points(Elf, 2);
        ui->NextEventLabel->setText("reject_offer");
        break;
    case '3': hero.modify_hp(-1);
        hero.modify_race_points(Orc, 2);
        hero.modify_race_points(Dwarf, 1);
        ui->NextEventLabel->setText("say_nothing");
        break;
    }
}

void ExpertSystem::continue_studying() {
    set_choice(0);
    ui->TextLabel->setText("You overcome yourself and after a few hours of studying botany go to rest.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::give_up_studying() {
    set_choice(0);
    ui->TextLabel->setText("You don't overcome yourself and go to the yard. Climbing a tree and hanging upside down is your new occupation.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::recall_kaleidoscope() {
    set_choice(0);
    ui->TextLabel->setText("You spend the rest of the day looking at colorful pictures made up of multicolored glass");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::studying_after_kaleidoscope() {
    set_choice(0);
    ui->TextLabel->setText("You spend the rest of the day reading a mathematical book.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::disassemble_kaleidoscope() {
    set_choice(0);
    ui->TextLabel->setText("You were wondering how this unusual toy works. Having disassembled it, you see how simple it is, but still amazing.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::rest_after_kaleidoscope() {
    set_choice(0);
    ui->TextLabel->setText("In the form of rest, you decide to give your body a physical activity.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::back_to_sleep() {
    set_choice(0);
    ui->TextLabel->setText("You wake up in the morning and realize that you didn't do anything useful last day...");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::studying_after_rest() {
    set_choice(0);
    ui->TextLabel->setText("You spend the rest of the day reading a mathematical book.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::run_away() {
    set_choice(0);
    ui->TextLabel->setText("You free your hand, grab a couple of apples and run away from the angry seller with all your might.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::come_what_may() {
    set_choice(0);
    ui->TextLabel->setText("The seller's anger changes to mercy. Now you don't live on the streets, you're a sales assistant.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::making_excuses() {
    set_choice(0);
    ui->TextLabel->setText("The seller decides to give you some fruit and a piece of bread. Now you're not hungry.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::help_herbalist() {
    set_choice(0);
    ui->TextLabel->setText("You help the herbalist and get a few coins. The skills you have gained will be needed in the future.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::help_tanner() {
    set_choice(0);
    ui->TextLabel->setText("You help the tanner and get a few coins. The skills you have gained will be needed in the future.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::help_miner() {
    set_choice(0);
    ui->TextLabel->setText("You help the miner and get a few coins. The skills you have gained will be needed in the future.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::accept_offer() {
    set_choice(0);
    ui->TextLabel->setText("You find out the name of the wanderer - Henry. And now he's your traveling partner.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::reject_offer() {
    set_choice(0);
    ui->TextLabel->setText("You reject the wanderer's offer. He's obviously upset, but he gives you a couple of coins for food.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::say_nothing() {
    set_choice(0);
    ui->TextLabel->setText("The wanderer giggles strangely and walks away in an uncertain direction. No one else comes up to you, you just stay hungry.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::go_plains() {
    set_choice(0);
    ui->TextLabel->setText("If someone decided to hide in an open field, it would be strange... You're already here, but there's nothing here, nothing but rocks, flowers and grass.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::go_mountain() {
    set_choice(0);
    ui->TextLabel->setText("You have successfully found several people. Your gaze was attracted by one unusual stone, you don't know what it is, but you take it to your pocket.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::go_house() {
    set_choice(0);
    ui->TextLabel->setText("You didn't find anyone, but a kind woman offered you a job - leather processing, in exchange for food. You did it and got your pie.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::smash_bug() {
    set_choice(0);
    ui->TextLabel->setText("Poor poor bug. It made an unpleasant sound and smeared on your fingers.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::collect_bug() {
    set_choice(0);
    ui->TextLabel->setText("It doesn't matter if it's an ordinary bug or an unusual one. It will be in your collection.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::release_bug() {
    set_choice(0);
    ui->TextLabel->setText("The bug flutter up and fly away in an unknown direction. There was nothing else for you to do but go look for your buddies.");
    ui->NextEventLabel->setText("fin");
}

void ExpertSystem::fin() {
    ui->TextLabel->hide();
    ui->NextEventLabel->setText("send_character");
    QPixmap portrait(":/resources/img/portrait.png");
    ui->PictureLabel->setPixmap(portrait);
    ui->CharacterInfo->show();
    ui->SaveHeroCheck->show();
    hero.set_age();
    hero.set_stats();
    hero.set_class_();
    hero.set_race();
    hero.set_profession();
    QStringList info = hero.get_character();
    for (auto str : info){
        ui->CharacterInfo->setText(ui->CharacterInfo->text() + str + "\r\n");
    }

    waitSubmitButton();

    if (ui->SaveHeroCheck->isChecked()){
        save_hero();
    }
}

void ExpertSystem::on_SubmitButton_clicked()
{
    QFile file(":/resources/txt/EventList.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray list = file.readAll();
    QStringList EventList = QString(list).split("\r\n");
    int index = EventList.indexOf(ui->NextEventLabel->text());
    switch (index)
    {
    case 1: begining_1();
        break;
    case 2: begining_2();
        break;
    case 3: begining_3();
        break;
    case 4: begining_4();
        break;
    case 5: gender_choice();
        break;
    case 6: origin();
        break;
    case 7: peasant_way();
        break;
    case 8: find_someone();
        break;
    case 9: keep_waiting();
        break;
    case 10: examine_bug();
        break;
    case 11: noble_way();
        break;
    case 12: studying();
        break;
    case 13: kaleidoscope();
        break;
    case 14: rest();
        break;
    case 15: orphan_way();
        break;
    case 16: steal_food();
        break;
    case 17: work_for_food();
        break;
    case 18: begging();
        break;
    case 19: go_plains();
        break;
    case 20: go_mountain();
        break;
    case 21: go_house();
        break;
    case 22: smash_bug();
        break;
    case 23: collect_bug();
        break;
    case 24: release_bug();
        break;
    case 25: continue_studying();
        break;
    case 26: give_up_studying();
        break;
    case 27: recall_kaleidoscope();
        break;
    case 28: studying_after_kaleidoscope();
        break;
    case 29: disassemble_kaleidoscope();
        break;
    case 30: rest_after_kaleidoscope();
        break;
    case 31: back_to_sleep();
        break;
    case 32: studying_after_rest();
        break;
    case 33: run_away();
        break;
    case 34: come_what_may();
        break;
    case 35: making_excuses();
        break;
    case 36: help_herbalist();
        break;
    case 37: help_tanner();
        break;
    case 38: help_miner();
        break;
    case 39: accept_offer();
        break;
    case 40: reject_offer();
        break;
    case 41: say_nothing();
        break;
    case 42: fin();
        break;
    case 0:  emit send_character(ui->CharacterInfo->text());
        this->close();
        on_ResetButton_clicked();
        break;
    }
}

void ExpertSystem::on_ResetButton_clicked()
{
    if (ui->SaveHeroCheck->isChecked()){
        save_hero();
    }
    hero.reset_character();
    ui->TextLabel->show();
    QPixmap WIP(":/resources/img/WIP.jpg");
    ui->PictureLabel->setPixmap(WIP);
    ui->CharacterInfo->hide();
    ui->SaveHeroCheck->hide();
    ui->CharacterInfo->clear();
    ui->SaveHeroCheck->setChecked(false);
    begining_1();
}
