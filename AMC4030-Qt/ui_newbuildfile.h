/********************************************************************************
** Form generated from reading UI file 'newbuildfile.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWBUILDFILE_H
#define UI_NEWBUILDFILE_H

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

class Ui_newBuildFile
{
public:
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *newBuildFile)
    {
        if (newBuildFile->objectName().isEmpty())
            newBuildFile->setObjectName(QStringLiteral("newBuildFile"));
        newBuildFile->resize(300, 160);
        label_2 = new QLabel(newBuildFile);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 70, 31, 21));
        label_2->setStyleSheet(QStringLiteral(""));
        pushButton = new QPushButton(newBuildFile);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 110, 71, 31));
        pushButton->setStyleSheet(QStringLiteral(""));
        label = new QLabel(newBuildFile);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 261, 21));
        label->setStyleSheet(QStringLiteral(""));
        lineEdit = new QLineEdit(newBuildFile);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 60, 121, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 16pt \"\345\256\213\344\275\223\";"));

        retranslateUi(newBuildFile);

        QMetaObject::connectSlotsByName(newBuildFile);
    } // setupUi

    void retranslateUi(QDialog *newBuildFile)
    {
        newBuildFile->setWindowTitle(QApplication::translate("newBuildFile", "AMC4030", 0));
        label_2->setText(QApplication::translate("newBuildFile", ".txt", 0));
        pushButton->setText(QApplication::translate("newBuildFile", "\347\241\256\345\256\232", 0));
        label->setText(QApplication::translate("newBuildFile", "\350\257\267\350\276\223\345\205\245\346\226\260\345\273\272\347\250\213\345\272\217\347\232\204\345\220\215\345\255\227\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class newBuildFile: public Ui_newBuildFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWBUILDFILE_H
