/********************************************************************************
** Form generated from reading UI file 'newabout.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWABOUT_H
#define UI_NEWABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_newAbout
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_Version;
    QPushButton *Btn_Update;
    QPushButton *Btn_AboutFuyu;
    QComboBox *ComBox_Update;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_Version_2;

    void setupUi(QDialog *newAbout)
    {
        if (newAbout->objectName().isEmpty())
            newAbout->setObjectName(QStringLiteral("newAbout"));
        newAbout->resize(400, 240);
        groupBox = new QGroupBox(newAbout);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(70, 90, 261, 81));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 71, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 50, 131, 16));
        label_Version = new QLabel(groupBox);
        label_Version->setObjectName(QStringLiteral("label_Version"));
        label_Version->setGeometry(QRect(140, 20, 71, 21));
        Btn_Update = new QPushButton(newAbout);
        Btn_Update->setObjectName(QStringLiteral("Btn_Update"));
        Btn_Update->setGeometry(QRect(230, 190, 81, 31));
        Btn_AboutFuyu = new QPushButton(newAbout);
        Btn_AboutFuyu->setObjectName(QStringLiteral("Btn_AboutFuyu"));
        Btn_AboutFuyu->setGeometry(QRect(90, 190, 81, 31));
        ComBox_Update = new QComboBox(newAbout);
        ComBox_Update->setObjectName(QStringLiteral("ComBox_Update"));
        ComBox_Update->setGeometry(QRect(0, 220, 131, 22));
        groupBox_2 = new QGroupBox(newAbout);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(70, 20, 261, 51));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 20, 71, 21));
        label_Version_2 = new QLabel(groupBox_2);
        label_Version_2->setObjectName(QStringLiteral("label_Version_2"));
        label_Version_2->setGeometry(QRect(140, 20, 71, 21));

        retranslateUi(newAbout);

        QMetaObject::connectSlotsByName(newAbout);
    } // setupUi

    void retranslateUi(QDialog *newAbout)
    {
        newAbout->setWindowTitle(QApplication::translate("newAbout", "AMC4030", 0));
        groupBox->setTitle(QApplication::translate("newAbout", "\346\216\247\345\210\266\345\215\241\344\277\241\346\201\257\357\274\232", 0));
        label->setText(QApplication::translate("newAbout", "\346\216\247\345\210\266\345\231\250\347\211\210\346\234\254\357\274\232 ", 0));
        label_2->setText(QApplication::translate("newAbout", "\347\224\237\344\272\247\345\272\217\345\210\227\345\217\267\357\274\232 0x01", 0));
        label_Version->setText(QApplication::translate("newAbout", "TextLabel", 0));
        Btn_Update->setText(QApplication::translate("newAbout", "\345\233\272\344\273\266\345\215\207\347\272\247", 0));
        Btn_AboutFuyu->setText(QApplication::translate("newAbout", "\344\274\201\344\270\232\345\256\230\347\275\221", 0));
        groupBox_2->setTitle(QApplication::translate("newAbout", "\350\275\257\344\273\266\344\277\241\346\201\257\357\274\232", 0));
        label_3->setText(QApplication::translate("newAbout", "\350\275\257\344\273\266\347\211\210\346\234\254\357\274\232 ", 0));
        label_Version_2->setText(QApplication::translate("newAbout", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class newAbout: public Ui_newAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWABOUT_H
