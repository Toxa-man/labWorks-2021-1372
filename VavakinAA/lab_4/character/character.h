#include <QWidget>
#include <QFile>

enum _stats { Strength, Agility, Intelligence };
enum _profession { Herbalist, Tanner, Miner };
enum _race { Human, Elf, Dwarf, Orc };

class Character {
private:
    int hp = 500;
    int age = 10;
    QVector<QString>stats_names{"Strength", "Agility", "Intelligence"};
    QVector<int> stats = { 1000, 1000, 1000 }; // stats[0] - Strength, stats[1] - Agility, stats[2] - Intelligence
    QVector<float> stats_multipliers = { 1, 1, 1 }; // multipliers[0] - multiplier of Strength, multipliers[1] - multiplier of Agility, multipliers[2] - multiplier of Intelligence
    QVector<int> profession_points = { 0, 0, 0 }; // proffesion_points[0] - Herbalist, proffesion_points[1] - Tanner, proffesion_points[2] - Miner
    QVector<int> race_points = { 0, 0, 0, 0 }; // race_points[0] - Human points,  race_points[1] - Elf points, race_points[2] - Dwarf points, race_points[3] - Orc points
    QString class_ = "None";
    QString race = "None";
    QString profession = "None";
    QString gender = "None";
    const int buff = 200;

public:
    bool is_damage_reduction_active = false;
    double incoming_damage_reduction = 0.75;

    void modify_hp(int extra_hp);

    void modify_stats(_stats stat, int extra_stats);

    void modify_stats_multiplier(_stats stat, float extra_multiplier);

    void modify_profession_points(_profession prof, int extra_prof_points);

    void modify_race_points(_race type, int extra_race_points);

    void set_class_();

    void set_race();

    void set_profession();

    void set_gender(QString new_gender);

    void set_age();

    void set_stats();

    void reset_character();

    void set_character(QStringList& character_info);

    void save_to_file(QFile& file);

    int get_hp();

    QVector<int> get_stats();

    int get_max_stat();

    QString get_class();

    QStringList get_character();
};
