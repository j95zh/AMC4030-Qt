/********************************************************************************
** Form generated from reading UI file 'amc4030.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMC4030_H
#define UI_AMC4030_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AMC4030
{
public:
    QAction *actionChinese;
    QAction *actionEnglish;
    QWidget *centralWidget;
    QPushButton *Btn_ConnectController;
    QPushButton *Btn_About;
    QPushButton *Btn_ParameterSet;
    QPushButton *Btn_ManualOperate;
    QPushButton *Btn_ProgramEdite;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_4;
    QLabel *label;
    QLabel *label_2;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu11;

    void setupUi(QMainWindow *AMC4030)
    {
        if (AMC4030->objectName().isEmpty())
            AMC4030->setObjectName(QStringLiteral("AMC4030"));
        AMC4030->resize(870, 500);
        actionChinese = new QAction(AMC4030);
        actionChinese->setObjectName(QStringLiteral("actionChinese"));
        actionEnglish = new QAction(AMC4030);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        centralWidget = new QWidget(AMC4030);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Btn_ConnectController = new QPushButton(centralWidget);
        Btn_ConnectController->setObjectName(QStringLiteral("Btn_ConnectController"));
        Btn_ConnectController->setGeometry(QRect(20, 20, 81, 41));
        Btn_About = new QPushButton(centralWidget);
        Btn_About->setObjectName(QStringLiteral("Btn_About"));
        Btn_About->setGeometry(QRect(20, 390, 81, 41));
        Btn_ParameterSet = new QPushButton(centralWidget);
        Btn_ParameterSet->setObjectName(QStringLiteral("Btn_ParameterSet"));
        Btn_ParameterSet->setGeometry(QRect(20, 210, 81, 41));
        Btn_ManualOperate = new QPushButton(centralWidget);
        Btn_ManualOperate->setObjectName(QStringLiteral("Btn_ManualOperate"));
        Btn_ManualOperate->setGeometry(QRect(20, 120, 81, 41));
        Btn_ProgramEdite = new QPushButton(centralWidget);
        Btn_ProgramEdite->setObjectName(QStringLiteral("Btn_ProgramEdite"));
        Btn_ProgramEdite->setGeometry(QRect(20, 300, 81, 41));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(120, 20, 721, 401));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 719, 399));
        scrollArea->setWidget(scrollAreaWidgetContents_4);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 0, 261, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(410, 0, 261, 16));
        AMC4030->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AMC4030);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AMC4030->setStatusBar(statusBar);
        menuBar = new QMenuBar(AMC4030);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 870, 23));
        menu11 = new QMenu(menuBar);
        menu11->setObjectName(QStringLiteral("menu11"));
        AMC4030->setMenuBar(menuBar);

        menuBar->addAction(menu11->menuAction());
        menu11->addAction(actionChinese);
        menu11->addSeparator();
        menu11->addAction(actionEnglish);

        retranslateUi(AMC4030);

        QMetaObject::connectSlotsByName(AMC4030);
    } // setupUi

    void retranslateUi(QMainWindow *AMC4030)
    {
        AMC4030->setWindowTitle(QString());
        actionChinese->setText(QApplication::translate("AMC4030", "\344\270\255\346\226\207", 0));
        actionEnglish->setText(QApplication::translate("AMC4030", "English", 0));
        Btn_ConnectController->setText(QApplication::translate("AMC4030", "\350\277\236\346\216\245\346\216\247\345\210\266\345\231\250", 0));
        Btn_About->setText(QApplication::translate("AMC4030", "\345\205\263\344\272\216", 0));
        Btn_ParameterSet->setText(QApplication::translate("AMC4030", "\345\217\202\346\225\260\350\256\276\347\275\256 ", 0));
        Btn_ManualOperate->setText(QApplication::translate("AMC4030", "\346\211\213\345\212\250\346\223\215\344\275\234", 0));
        Btn_ProgramEdite->setText(QApplication::translate("AMC4030", "\347\250\213\345\272\217\347\274\226\350\276\221", 0));
        label->setText(QApplication::translate("AMC4030", "\345\275\223\345\211\215\347\212\266\346\200\201\357\274\232\346\234\252\350\277\236\346\216\245\346\216\247\345\210\266\345\231\250\357\274\201", 0));
        label_2->setText(QString());
        menu11->setTitle(QApplication::translate("AMC4030", "Language", 0));
    } // retranslateUi

};

namespace Ui {
    class AMC4030: public Ui_AMC4030 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMC4030_H
