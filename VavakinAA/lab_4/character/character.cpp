#include "character.h"
#include <QFile>
#include <QTextStream>

void Character::modify_hp(int extra_hp) {
    hp += buff * extra_hp;
}

void Character::modify_stats(_stats stat, int extra_stats) {
    stats[stat] += 2 * buff * extra_stats;
}

void Character::modify_stats_multiplier(_stats stat, float extra_multiplier) {
    stats_multipliers[stat] += extra_multiplier;
}

void Character::modify_profession_points(_profession prof, int extra_prof_points) {
    profession_points[prof] += extra_prof_points;
}

void Character::modify_race_points(_race type, int extra_race_points) {
    race_points[type] += extra_race_points;
}

void Character::set_class_() {
    int max = stats[0];
    int index = 0;
    for (int i = 1; i < 3; i++){
        if (stats[i] > max){
            max = stats[i];
            index = i;
        }
    }
    switch (index)
    {
    case 0: class_ = "Warrior";
        break;
    case 1: class_ = "Assasin";
        break;
    case 2: class_ = "Mage";
        break;
    }
}

void Character::set_race() {
    int max = race_points[0];
    int index = 0;
    for (int i = 1; i < 4; i++){
        if (race_points[i] > max) {
            max = race_points[i];
            index = i;
        }
    }
    switch (index)
    {
    case 0: race = "Human";
        break;
    case 1: race = "Elf";
        break;
    case 2: race = "Dwarf";
        break;
    case 3: race = "Orc";
        break;
    }
}

void Character::set_profession() {
    int max = profession_points[0];
    int index = 0;
    for (int i = 1; i < 3; i++)
        if (profession_points[i] > max) {
            max = profession_points[i];
            index = i;
        }
    if (max == 0) {}
    else{
    switch (index)
    {
    case 0: profession = "Herbalist";
        break;
    case 1: profession = "Tanner";
        break;
    case 2: profession = "Miner";
        break;
    }
    }
}

void Character::set_gender(QString new_gender) {
    gender = new_gender;
}

void Character::set_age() {
    srand(time(NULL));
    age = (rand() % 90) / 2 + age;
}

void Character::set_stats() {
    for (int i = 0; i < 3; i++) {
        stats[i] = round(stats[i] * stats_multipliers[i]);
    }
}

void Character::reset_character(){
    hp = 500;
    age = 10;
    stats = { 1000, 1000, 1000 };
    stats_multipliers = { 1, 1, 1 };
    profession_points = { 0, 0, 0 };
    race_points = { 0, 0, 0, 0 };
    class_ = "None";
    race = "None";
    profession = "None";
    gender = "None";
}

void Character::save_to_file(QFile& file) {
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "Gender: " << gender << Qt::endl;
    stream << "Age: " << age << Qt::endl;
    stream << "Race: " << race << Qt::endl;
    stream << "Class: " << class_ << Qt::endl;
    stream << "Profession: " << profession << Qt::endl;
    stream << "HP: " << hp << Qt::endl;

    for (int i = 0; i < 3; i++) {
        stream << stats_names[i] << ": ";
        stream << stats[i] << Qt::endl;
    }
}

void Character::set_character(QStringList& character_info){
    gender = character_info[0];
    age = character_info[1].toInt();
    race = character_info[2];
    class_ = character_info[3];
    profession = character_info[4];
    hp = character_info[5].toInt();
    stats = { character_info[6].toInt(), character_info[7].toInt(), character_info[8].toInt() };
}

int Character::get_hp(){
    return hp;
}

QVector<int> Character::get_stats(){
    return stats;
}

int Character::get_max_stat(){
    int max = stats[0];
    int index = 0;
    for (int i = 1; i < 3; i++){
        if (stats[i] > max){
            max = stats[i];
            index = i;
        }
    }
    return stats[index];
}

QString Character::get_class()
{
    return class_;
}

QStringList Character::get_character(){

    QStringList info;

    info.append("Gender: " + gender);
    info.append("Age: " + QString::number(age));
    info.append("Race: " + race);
    info.append("Class: " + class_);
    info.append("Profession: " + profession);
    info.append("HP: " + QString::number(hp));

    for (int i = 0; i < 3; i++) {
        info.append(stats_names[i] + ": " + QString::number(stats[i]));
    }
    return info;
}
