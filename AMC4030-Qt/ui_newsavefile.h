/********************************************************************************
** Form generated from reading UI file 'newsavefile.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSAVEFILE_H
#define UI_NEWSAVEFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_newSaveFile
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QPushButton *Btn_ModifyName;

    void setupUi(QDialog *newSaveFile)
    {
        if (newSaveFile->objectName().isEmpty())
            newSaveFile->setObjectName(QStringLiteral("newSaveFile"));
        newSaveFile->resize(340, 170);
        label = new QLabel(newSaveFile);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 70, 91, 31));
        label->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(newSaveFile);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 70, 121, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));
        pushButton = new QPushButton(newSaveFile);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 120, 71, 31));
        pushButton->setStyleSheet(QStringLiteral(""));
        label_3 = new QLabel(newSaveFile);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 20, 151, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\256\213\344\275\223\";\n"
""));
        Btn_ModifyName = new QPushButton(newSaveFile);
        Btn_ModifyName->setObjectName(QStringLiteral("Btn_ModifyName"));
        Btn_ModifyName->setGeometry(QRect(240, 70, 81, 31));
        Btn_ModifyName->setStyleSheet(QStringLiteral(""));

        retranslateUi(newSaveFile);

        QMetaObject::connectSlotsByName(newSaveFile);
    } // setupUi

    void retranslateUi(QDialog *newSaveFile)
    {
        newSaveFile->setWindowTitle(QApplication::translate("newSaveFile", "AMC4030", 0));
        label->setText(QApplication::translate("newSaveFile", "\345\275\223\345\211\215\347\250\213\345\272\217\347\232\204\345\220\215\345\255\227\357\274\232", 0));
        label_2->setText(QString());
        pushButton->setText(QApplication::translate("newSaveFile", "\347\241\256\345\256\232", 0));
        label_3->setText(QApplication::translate("newSaveFile", "\344\277\235\345\255\230\346\210\220\345\212\237\357\274\201", 0));
        Btn_ModifyName->setText(QApplication::translate("newSaveFile", "\344\277\256\346\224\271\347\250\213\345\272\217\345\220\215", 0));
    } // retranslateUi

};

namespace Ui {
    class newSaveFile: public Ui_newSaveFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSAVEFILE_H
