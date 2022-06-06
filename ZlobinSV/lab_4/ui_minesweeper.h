/********************************************************************************
** Form generated from reading UI file 'minesweeper.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINESWEEPER_H
#define UI_MINESWEEPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Minesweeper
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Minesweeper)
    {
        if (Minesweeper->objectName().isEmpty())
            Minesweeper->setObjectName(QString::fromUtf8("Minesweeper"));
        Minesweeper->resize(600, 600);
        centralwidget = new QWidget(Minesweeper);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Minesweeper->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Minesweeper);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        Minesweeper->setMenuBar(menubar);
        statusbar = new QStatusBar(Minesweeper);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Minesweeper->setStatusBar(statusbar);

        retranslateUi(Minesweeper);

        QMetaObject::connectSlotsByName(Minesweeper);
    } // setupUi

    void retranslateUi(QMainWindow *Minesweeper)
    {
        Minesweeper->setWindowTitle(QCoreApplication::translate("Minesweeper", "Minesweeper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Minesweeper: public Ui_Minesweeper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINESWEEPER_H
