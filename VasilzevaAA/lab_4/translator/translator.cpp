#include "translator.h"
#include "ui_translator.h"

void Translator::addWord(QString a_word){

    QFile NET_WORD ("C:\\qt_projs\\translator\\wooordhunt.txt");

    NET_WORD.open(QIODevice::ReadOnly);

    QTextStream net_word(&NET_WORD);

    while (!net_word.atEnd()) {

        QString new_word = net_word.readLine();

        int flagNum;
        if (a_word[0] > 122){
            flagNum = new_word.indexOf("<p class=\"t_inline\">");
        }else{
            flagNum = new_word.indexOf("<div class=\"t_inline_en\">");
        }

         if (flagNum != -1){
              int begPos = new_word.indexOf(">", flagNum);
              int endPos = new_word.indexOf("<", begPos);

              QString add_word = new_word.mid(begPos+1, endPos-(begPos+1));

              NET_WORD.close();

              if (a_word[0] > 122){
                  QFile CHANGE_VOC ("C:\\qt_projs\\translator\\Russian vocabulary.txt");
                  CHANGE_VOC.open(QIODevice::Append);

                  QTextStream chan_in(&CHANGE_VOC);
                  chan_in << a_word + " " + add_word + "\n";
                  ui->line_trans->setText(add_word);
                  CHANGE_VOC.close();
                  break;
              }
              else{
                  QFile CHANGE_VOC ("C:\\qt_projs\\translator\\English vocabulary.txt");
                  CHANGE_VOC.open(QIODevice::Append);

                  QTextStream chan_in(&CHANGE_VOC);
                  chan_in << a_word + " " + add_word + "\n";
                  ui->line_trans->setText(add_word);
                  CHANGE_VOC.close();
                  break;
              }
         }
    }
}

Translator::Translator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Translator)
{
    ui->setupUi(this);
    QObject::connect(ui->push_btn, &QPushButton::clicked, [this](){

         QString a_word = ui->line_word->text();
         bool lenguage = (a_word[0] > 122); // 0 = eng, 1 = rus

         QFile ENG_VOC ("C:\\qt_projs\\translator\\English vocabulary.txt");
         ENG_VOC.open(QIODevice::ReadOnly);

         QFile RUS_VOC ("C:\\qt_projs\\translator\\Russian vocabulary.txt");
         RUS_VOC.open(QIODevice::ReadOnly);

         QTextStream eng_in(&ENG_VOC);
         QTextStream rus_in(&RUS_VOC);

         bool not_found_word = true;

         if (!lenguage){
             while (!eng_in.atEnd()) {

                 QString eng_word = eng_in.readLine();

                 // выделяем англ слово
                 int space_poz = 0, len_word = eng_word.length();
                 space_poz = eng_word.indexOf(" ");
                 QString rus_word = eng_word;
                 rus_word.remove(0,space_poz+1);
                 eng_word.remove(space_poz, len_word-space_poz);

                 if (eng_word == a_word){
                     ui->line_trans->setText(rus_word);
                     not_found_word = false;
                     break;
                 }
                 RUS_VOC.close();
                 ENG_VOC.close();
              }
         }
         else{
             while (!rus_in.atEnd()) {

                 QString rus_word = rus_in.readLine();

                 int space_poz = 0, len_word = rus_word.length();
                 space_poz = rus_word.indexOf(" ");
                 QString eng_word = rus_word;
                 eng_word.remove(0,space_poz+1);
                 rus_word.remove(space_poz, len_word-space_poz);

                 if (rus_word == a_word){
                 ui->line_trans->setText(eng_word);
                 not_found_word = false;
                 break;
                 }
             }
                 RUS_VOC.close();
                 ENG_VOC.close();
         }

         if (not_found_word){

             QNetworkAccessManager *manager = new QNetworkAccessManager(this);
             connect(manager, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(replyFinished(QNetworkReply*)));

             manager->get(QNetworkRequest(QUrl("https://wooordhunt.ru/word/" + a_word)));

             connect(manager, &QNetworkAccessManager::finished, [=]() {
                     addWord(a_word);
             });
         }
    });

    QObject::connect(ui->clean_btn, &QPushButton::clicked, [this](){
        ui->line_trans->setText("");
        ui->line_word->setText("");
    });

    QObject::connect(ui->btn_chang_rus, &QPushButton::clicked, [this](){
        ui->label_w->setText("Слово");
        ui->label_t->setText("Перевод");
        ui->clean_btn->setText("Очистить");
        ui->push_btn->setText("Перевести");
        ui->line_trans->setText("");
        ui->line_word->setText("");
    });

    QObject::connect(ui->btn_chang_eng, &QPushButton::clicked, [this](){
        ui->label_w->setText("A word");
        ui->label_t->setText("Translation");
        ui->clean_btn->setText("Clean");
        ui->push_btn->setText("Translate");
        ui->line_trans->setText("");
        ui->line_word->setText("");
    });
}

Translator::~Translator()
{
    delete ui;
}

