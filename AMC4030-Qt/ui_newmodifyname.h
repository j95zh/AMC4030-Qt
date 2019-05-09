/********************************************************************************
** Form generated from reading UI file 'newmodifyname.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMODIFYNAME_H
#define UI_NEWMODIFYNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_newModifyName
{
public:
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *newModifyName)
    {
        if (newModifyName->objectName().isEmpty())
            newModifyName->setObjectName(QStringLiteral("newModifyName"));
        newModifyName->resize(300, 160);
        pushButton = new QPushButton(newModifyName);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 110, 71, 31));
        pushButton->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(newModifyName);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 70, 31, 21));
        label_2->setStyleSheet(QStringLiteral(""));
        lineEdit = new QLineEdit(newModifyName);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 60, 121, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 16pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(newModifyName);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 261, 21));
        label->setStyleSheet(QStringLiteral(""));

        retranslateUi(newModifyName);

        QMetaObject::connectSlotsByName(newModifyName);
    } // setupUi

    void retranslateUi(QDialog *newModifyName)
    {
        newModifyName->setWindowTitle(QApplication::translate("newModifyName", "AMC4030", 0));
        pushButton->setText(QApplication::translate("newModifyName", "\347\241\256\345\256\232", 0));
        label_2->setText(QApplication::translate("newModifyName", ".txt", 0));
        label->setText(QApplication::translate("newModifyName", "\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245\347\250\213\345\272\217\347\232\204\345\220\215\345\255\227\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class newModifyName: public Ui_newModifyName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMODIFYNAME_H
