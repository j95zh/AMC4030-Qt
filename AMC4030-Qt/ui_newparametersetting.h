/********************************************************************************
** Form generated from reading UI file 'newparametersetting.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPARAMETERSETTING_H
#define UI_NEWPARAMETERSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_newParameterSetting
{
public:
    QPushButton *Btn_RestoreFactorySettings;
    QGroupBox *groupBox_4;
    QLabel *label_7;
    QLineEdit *LineEdit_SysAccSpeed;
    QLabel *label_26;
    QLineEdit *LineEdit_BackLashLen_X;
    QCheckBox *CheckBox_BackLash_X;
    QLineEdit *LineEdit_BackLashLen_Y;
    QCheckBox *CheckBox_BackLash_Y;
    QLineEdit *LineEdit_BackLashLen_Z;
    QCheckBox *CheckBox_BackLash_Z;
    QPushButton *Btn_ParameterSave;
    QGroupBox *groupBox;
    QLineEdit *LineEdit_PulseFactor_X;
    QLabel *label;
    QLineEdit *LineEdit_HomeSpeed_X;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *LineEdit_MaxPos_X;
    QLabel *label_11;
    QComboBox *ComBox_HomeDirection_X;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *LineEdit_PulseFactorDown_X;
    QLineEdit *LineEdit_PulseFactorUp_X;
    QLabel *label_19;
    QLabel *label_X;
    QLabel *label_Y;
    QLabel *label_Z;
    QFrame *line;
    QLabel *label_8;
    QLineEdit *LineEdit_HomeOffset_X;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *label_20;
    QLineEdit *LineEdit_PulseFactor_Y;
    QLineEdit *LineEdit_HomeOffset_Y;
    QLineEdit *LineEdit_HomeSpeed_Y;
    QLineEdit *LineEdit_MaxPos_Y;
    QComboBox *ComBox_HomeDirection_Y;
    QLineEdit *LineEdit_PulseFactorUp_Y;
    QLineEdit *LineEdit_PulseFactorDown_Y;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *LineEdit_PulseFactor_Z;
    QLineEdit *LineEdit_HomeOffset_Z;
    QLineEdit *LineEdit_HomeSpeed_Z;
    QLineEdit *LineEdit_MaxPos_Z;
    QComboBox *ComBox_HomeDirection_Z;
    QLineEdit *LineEdit_PulseFactorUp_Z;
    QLineEdit *LineEdit_PulseFactorDown_Z;
    QLabel *label_23;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_24;
    QLabel *label_25;
    QPushButton *Btn_ParameterLoade;

    void setupUi(QDialog *newParameterSetting)
    {
        if (newParameterSetting->objectName().isEmpty())
            newParameterSetting->setObjectName(QStringLiteral("newParameterSetting"));
        newParameterSetting->resize(710, 400);
        Btn_RestoreFactorySettings = new QPushButton(newParameterSetting);
        Btn_RestoreFactorySettings->setObjectName(QStringLiteral("Btn_RestoreFactorySettings"));
        Btn_RestoreFactorySettings->setGeometry(QRect(510, 350, 81, 31));
        groupBox_4 = new QGroupBox(newParameterSetting);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 270, 721, 61));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(100, 20, 81, 21));
        LineEdit_SysAccSpeed = new QLineEdit(groupBox_4);
        LineEdit_SysAccSpeed->setObjectName(QStringLiteral("LineEdit_SysAccSpeed"));
        LineEdit_SysAccSpeed->setEnabled(true);
        LineEdit_SysAccSpeed->setGeometry(QRect(180, 20, 51, 20));
        label_26 = new QLabel(groupBox_4);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(240, 20, 61, 21));
        LineEdit_BackLashLen_X = new QLineEdit(groupBox_4);
        LineEdit_BackLashLen_X->setObjectName(QStringLiteral("LineEdit_BackLashLen_X"));
        LineEdit_BackLashLen_X->setGeometry(QRect(350, 10, 71, 20));
        CheckBox_BackLash_X = new QCheckBox(groupBox_4);
        CheckBox_BackLash_X->setObjectName(QStringLiteral("CheckBox_BackLash_X"));
        CheckBox_BackLash_X->setGeometry(QRect(350, 30, 91, 21));
        CheckBox_BackLash_X->setCheckable(true);
        LineEdit_BackLashLen_Y = new QLineEdit(groupBox_4);
        LineEdit_BackLashLen_Y->setObjectName(QStringLiteral("LineEdit_BackLashLen_Y"));
        LineEdit_BackLashLen_Y->setGeometry(QRect(460, 10, 71, 20));
        CheckBox_BackLash_Y = new QCheckBox(groupBox_4);
        CheckBox_BackLash_Y->setObjectName(QStringLiteral("CheckBox_BackLash_Y"));
        CheckBox_BackLash_Y->setGeometry(QRect(460, 30, 91, 21));
        CheckBox_BackLash_Y->setCheckable(true);
        LineEdit_BackLashLen_Z = new QLineEdit(groupBox_4);
        LineEdit_BackLashLen_Z->setObjectName(QStringLiteral("LineEdit_BackLashLen_Z"));
        LineEdit_BackLashLen_Z->setGeometry(QRect(570, 10, 71, 20));
        CheckBox_BackLash_Z = new QCheckBox(groupBox_4);
        CheckBox_BackLash_Z->setObjectName(QStringLiteral("CheckBox_BackLash_Z"));
        CheckBox_BackLash_Z->setGeometry(QRect(570, 30, 91, 21));
        CheckBox_BackLash_Z->setCheckable(true);
        Btn_ParameterSave = new QPushButton(newParameterSetting);
        Btn_ParameterSave->setObjectName(QStringLiteral("Btn_ParameterSave"));
        Btn_ParameterSave->setGeometry(QRect(310, 350, 81, 31));
        groupBox = new QGroupBox(newParameterSetting);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(0, 20, 731, 231));
        LineEdit_PulseFactor_X = new QLineEdit(groupBox);
        LineEdit_PulseFactor_X->setObjectName(QStringLiteral("LineEdit_PulseFactor_X"));
        LineEdit_PulseFactor_X->setEnabled(false);
        LineEdit_PulseFactor_X->setGeometry(QRect(101, 71, 51, 20));
        LineEdit_PulseFactor_X->setFrame(true);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 61, 21));
        LineEdit_HomeSpeed_X = new QLineEdit(groupBox);
        LineEdit_HomeSpeed_X->setObjectName(QStringLiteral("LineEdit_HomeSpeed_X"));
        LineEdit_HomeSpeed_X->setGeometry(QRect(520, 70, 31, 20));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(520, 20, 61, 21));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(330, 20, 51, 21));
        LineEdit_MaxPos_X = new QLineEdit(groupBox);
        LineEdit_MaxPos_X->setObjectName(QStringLiteral("LineEdit_MaxPos_X"));
        LineEdit_MaxPos_X->setGeometry(QRect(320, 70, 31, 21));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(420, 20, 71, 21));
        ComBox_HomeDirection_X = new QComboBox(groupBox);
        ComBox_HomeDirection_X->setObjectName(QStringLiteral("ComBox_HomeDirection_X"));
        ComBox_HomeDirection_X->setGeometry(QRect(420, 70, 61, 21));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(160, 20, 16, 21));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 20, 41, 21));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(220, 20, 16, 21));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(240, 20, 61, 21));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(160, 70, 16, 16));
        LineEdit_PulseFactorDown_X = new QLineEdit(groupBox);
        LineEdit_PulseFactorDown_X->setObjectName(QStringLiteral("LineEdit_PulseFactorDown_X"));
        LineEdit_PulseFactorDown_X->setEnabled(true);
        LineEdit_PulseFactorDown_X->setGeometry(QRect(180, 70, 31, 20));
        LineEdit_PulseFactorUp_X = new QLineEdit(groupBox);
        LineEdit_PulseFactorUp_X->setObjectName(QStringLiteral("LineEdit_PulseFactorUp_X"));
        LineEdit_PulseFactorUp_X->setGeometry(QRect(240, 70, 41, 20));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(220, 70, 16, 21));
        label_X = new QLabel(groupBox);
        label_X->setObjectName(QStringLiteral("label_X"));
        label_X->setGeometry(QRect(30, 60, 51, 41));
        label_X->setLineWidth(1);
        label_X->setTextFormat(Qt::AutoText);
        label_Y = new QLabel(groupBox);
        label_Y->setObjectName(QStringLiteral("label_Y"));
        label_Y->setGeometry(QRect(30, 120, 51, 41));
        label_Z = new QLabel(groupBox);
        label_Z->setObjectName(QStringLiteral("label_Z"));
        label_Z->setGeometry(QRect(30, 180, 51, 41));
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 40, 691, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(620, 20, 71, 21));
        LineEdit_HomeOffset_X = new QLineEdit(groupBox);
        LineEdit_HomeOffset_X->setObjectName(QStringLiteral("LineEdit_HomeOffset_X"));
        LineEdit_HomeOffset_X->setGeometry(QRect(630, 70, 21, 20));
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 100, 691, 21));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(20, 160, 691, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(160, 130, 16, 16));
        LineEdit_PulseFactor_Y = new QLineEdit(groupBox);
        LineEdit_PulseFactor_Y->setObjectName(QStringLiteral("LineEdit_PulseFactor_Y"));
        LineEdit_PulseFactor_Y->setEnabled(false);
        LineEdit_PulseFactor_Y->setGeometry(QRect(101, 131, 51, 20));
        LineEdit_PulseFactor_Y->setFrame(true);
        LineEdit_HomeOffset_Y = new QLineEdit(groupBox);
        LineEdit_HomeOffset_Y->setObjectName(QStringLiteral("LineEdit_HomeOffset_Y"));
        LineEdit_HomeOffset_Y->setGeometry(QRect(630, 130, 21, 20));
        LineEdit_HomeSpeed_Y = new QLineEdit(groupBox);
        LineEdit_HomeSpeed_Y->setObjectName(QStringLiteral("LineEdit_HomeSpeed_Y"));
        LineEdit_HomeSpeed_Y->setGeometry(QRect(520, 130, 31, 20));
        LineEdit_MaxPos_Y = new QLineEdit(groupBox);
        LineEdit_MaxPos_Y->setObjectName(QStringLiteral("LineEdit_MaxPos_Y"));
        LineEdit_MaxPos_Y->setGeometry(QRect(320, 130, 31, 21));
        ComBox_HomeDirection_Y = new QComboBox(groupBox);
        ComBox_HomeDirection_Y->setObjectName(QStringLiteral("ComBox_HomeDirection_Y"));
        ComBox_HomeDirection_Y->setGeometry(QRect(420, 130, 61, 21));
        LineEdit_PulseFactorUp_Y = new QLineEdit(groupBox);
        LineEdit_PulseFactorUp_Y->setObjectName(QStringLiteral("LineEdit_PulseFactorUp_Y"));
        LineEdit_PulseFactorUp_Y->setGeometry(QRect(240, 130, 41, 20));
        LineEdit_PulseFactorDown_Y = new QLineEdit(groupBox);
        LineEdit_PulseFactorDown_Y->setObjectName(QStringLiteral("LineEdit_PulseFactorDown_Y"));
        LineEdit_PulseFactorDown_Y->setEnabled(true);
        LineEdit_PulseFactorDown_Y->setGeometry(QRect(180, 130, 31, 20));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(220, 130, 16, 21));
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(160, 190, 16, 16));
        LineEdit_PulseFactor_Z = new QLineEdit(groupBox);
        LineEdit_PulseFactor_Z->setObjectName(QStringLiteral("LineEdit_PulseFactor_Z"));
        LineEdit_PulseFactor_Z->setEnabled(false);
        LineEdit_PulseFactor_Z->setGeometry(QRect(101, 191, 51, 20));
        LineEdit_PulseFactor_Z->setFrame(true);
        LineEdit_HomeOffset_Z = new QLineEdit(groupBox);
        LineEdit_HomeOffset_Z->setObjectName(QStringLiteral("LineEdit_HomeOffset_Z"));
        LineEdit_HomeOffset_Z->setGeometry(QRect(630, 190, 21, 20));
        LineEdit_HomeSpeed_Z = new QLineEdit(groupBox);
        LineEdit_HomeSpeed_Z->setObjectName(QStringLiteral("LineEdit_HomeSpeed_Z"));
        LineEdit_HomeSpeed_Z->setGeometry(QRect(520, 190, 31, 20));
        LineEdit_MaxPos_Z = new QLineEdit(groupBox);
        LineEdit_MaxPos_Z->setObjectName(QStringLiteral("LineEdit_MaxPos_Z"));
        LineEdit_MaxPos_Z->setGeometry(QRect(320, 190, 31, 21));
        ComBox_HomeDirection_Z = new QComboBox(groupBox);
        ComBox_HomeDirection_Z->setObjectName(QStringLiteral("ComBox_HomeDirection_Z"));
        ComBox_HomeDirection_Z->setGeometry(QRect(420, 190, 61, 21));
        LineEdit_PulseFactorUp_Z = new QLineEdit(groupBox);
        LineEdit_PulseFactorUp_Z->setObjectName(QStringLiteral("LineEdit_PulseFactorUp_Z"));
        LineEdit_PulseFactorUp_Z->setGeometry(QRect(240, 190, 41, 20));
        LineEdit_PulseFactorDown_Z = new QLineEdit(groupBox);
        LineEdit_PulseFactorDown_Z->setObjectName(QStringLiteral("LineEdit_PulseFactorDown_Z"));
        LineEdit_PulseFactorDown_Z->setEnabled(true);
        LineEdit_PulseFactorDown_Z->setGeometry(QRect(180, 190, 31, 20));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(220, 190, 16, 21));
        line_4 = new QFrame(groupBox);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(70, 20, 20, 201));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(groupBox);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(290, 20, 20, 201));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(groupBox);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(390, 20, 20, 201));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(groupBox);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(490, 20, 20, 201));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(groupBox);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(600, 20, 20, 201));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 70, 31, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(350, 130, 41, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(350, 190, 31, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(550, 70, 51, 21));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(550, 130, 51, 21));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(550, 190, 51, 21));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(650, 70, 31, 21));
        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(650, 130, 31, 21));
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(650, 190, 31, 21));
        LineEdit_HomeSpeed_X->raise();
        LineEdit_MaxPos_X->raise();
        label_14->raise();
        label_15->raise();
        label_16->raise();
        label_17->raise();
        label_18->raise();
        LineEdit_PulseFactorDown_X->raise();
        LineEdit_PulseFactorUp_X->raise();
        label_19->raise();
        ComBox_HomeDirection_X->raise();
        LineEdit_PulseFactor_X->raise();
        label->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        label_X->raise();
        label_Y->raise();
        label_Z->raise();
        line->raise();
        label_8->raise();
        LineEdit_HomeOffset_X->raise();
        line_2->raise();
        line_3->raise();
        label_20->raise();
        LineEdit_PulseFactor_Y->raise();
        LineEdit_HomeOffset_Y->raise();
        LineEdit_HomeSpeed_Y->raise();
        LineEdit_MaxPos_Y->raise();
        ComBox_HomeDirection_Y->raise();
        LineEdit_PulseFactorUp_Y->raise();
        LineEdit_PulseFactorDown_Y->raise();
        label_21->raise();
        label_22->raise();
        LineEdit_PulseFactor_Z->raise();
        LineEdit_HomeOffset_Z->raise();
        LineEdit_HomeSpeed_Z->raise();
        LineEdit_MaxPos_Z->raise();
        ComBox_HomeDirection_Z->raise();
        LineEdit_PulseFactorUp_Z->raise();
        LineEdit_PulseFactorDown_Z->raise();
        label_23->raise();
        line_4->raise();
        line_5->raise();
        line_6->raise();
        line_7->raise();
        line_8->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_12->raise();
        label_13->raise();
        label_24->raise();
        label_25->raise();
        Btn_ParameterLoade = new QPushButton(newParameterSetting);
        Btn_ParameterLoade->setObjectName(QStringLiteral("Btn_ParameterLoade"));
        Btn_ParameterLoade->setGeometry(QRect(110, 350, 81, 31));

        retranslateUi(newParameterSetting);

        QMetaObject::connectSlotsByName(newParameterSetting);
    } // setupUi

    void retranslateUi(QDialog *newParameterSetting)
    {
        newParameterSetting->setWindowTitle(QApplication::translate("newParameterSetting", "Dialog", 0));
        Btn_RestoreFactorySettings->setText(QApplication::translate("newParameterSetting", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", 0));
        groupBox_4->setTitle(QApplication::translate("newParameterSetting", "\345\205\266\345\256\203\345\217\202\346\225\260", 0));
        label_7->setText(QApplication::translate("newParameterSetting", "\347\263\273\347\273\237\345\212\240\351\200\237\345\272\246\357\274\232", 0));
        LineEdit_SysAccSpeed->setText(QApplication::translate("newParameterSetting", "200", 0));
        label_26->setText(QApplication::translate("newParameterSetting", "\357\274\210mm/s^2\357\274\211", 0));
        LineEdit_BackLashLen_X->setText(QApplication::translate("newParameterSetting", "0", 0));
        CheckBox_BackLash_X->setText(QApplication::translate("newParameterSetting", "\345\220\257\347\224\250\345\217\215\345\220\221\351\227\264\351\232\231", 0));
        LineEdit_BackLashLen_Y->setText(QApplication::translate("newParameterSetting", "0", 0));
        CheckBox_BackLash_Y->setText(QApplication::translate("newParameterSetting", "\345\220\257\347\224\250\345\217\215\345\220\221\351\227\264\351\232\231", 0));
        LineEdit_BackLashLen_Z->setText(QApplication::translate("newParameterSetting", "0", 0));
        CheckBox_BackLash_Z->setText(QApplication::translate("newParameterSetting", "\345\220\257\347\224\250\345\217\215\345\220\221\351\227\264\351\232\231", 0));
        Btn_ParameterSave->setText(QApplication::translate("newParameterSetting", "\345\217\202\346\225\260\345\206\231\345\205\245", 0));
        groupBox->setTitle(QApplication::translate("newParameterSetting", "\350\275\264\345\217\202\346\225\260", 0));
        LineEdit_PulseFactor_X->setText(QApplication::translate("newParameterSetting", "0.004", 0));
        label->setText(QApplication::translate("newParameterSetting", "\350\204\211\345\206\262\345\275\223\351\207\217", 0));
        LineEdit_HomeSpeed_X->setText(QApplication::translate("newParameterSetting", "20", 0));
        label_9->setText(QApplication::translate("newParameterSetting", "\345\233\236\345\216\237\347\202\271\351\200\237\345\272\246", 0));
        label_10->setText(QApplication::translate("newParameterSetting", "\350\241\214\347\250\213", 0));
        LineEdit_MaxPos_X->setText(QApplication::translate("newParameterSetting", "200", 0));
        label_11->setText(QApplication::translate("newParameterSetting", "\345\233\236\345\216\237\347\202\271\346\226\271\345\220\221", 0));
        ComBox_HomeDirection_X->clear();
        ComBox_HomeDirection_X->insertItems(0, QStringList()
         << QApplication::translate("newParameterSetting", "    N", 0)
         << QApplication::translate("newParameterSetting", "    P", 0)
        );
        label_14->setText(QApplication::translate("newParameterSetting", "=", 0));
        label_15->setText(QApplication::translate("newParameterSetting", "\345\257\274\347\250\213", 0));
        label_16->setText(QApplication::translate("newParameterSetting", "/", 0));
        label_17->setText(QApplication::translate("newParameterSetting", "\347\273\206\345\210\206\346\225\260", 0));
        label_18->setText(QApplication::translate("newParameterSetting", "=", 0));
        LineEdit_PulseFactorDown_X->setText(QApplication::translate("newParameterSetting", "20", 0));
        LineEdit_PulseFactorUp_X->setText(QApplication::translate("newParameterSetting", "5000", 0));
        label_19->setText(QApplication::translate("newParameterSetting", "/", 0));
        label_X->setText(QApplication::translate("newParameterSetting", "X \350\275\264", 0));
        label_Y->setText(QApplication::translate("newParameterSetting", "Y \350\275\264", 0));
        label_Z->setText(QApplication::translate("newParameterSetting", "Z \350\275\264", 0));
        label_8->setText(QApplication::translate("newParameterSetting", "\345\216\237\347\202\271\345\233\236\351\200\200\350\267\235\347\246\273", 0));
        LineEdit_HomeOffset_X->setText(QApplication::translate("newParameterSetting", "5", 0));
        label_20->setText(QApplication::translate("newParameterSetting", "=", 0));
        LineEdit_PulseFactor_Y->setText(QApplication::translate("newParameterSetting", "0.004", 0));
        LineEdit_HomeOffset_Y->setText(QApplication::translate("newParameterSetting", "5", 0));
        LineEdit_HomeSpeed_Y->setText(QApplication::translate("newParameterSetting", "20", 0));
        LineEdit_MaxPos_Y->setText(QApplication::translate("newParameterSetting", "200", 0));
        ComBox_HomeDirection_Y->clear();
        ComBox_HomeDirection_Y->insertItems(0, QStringList()
         << QApplication::translate("newParameterSetting", "    N", 0)
         << QApplication::translate("newParameterSetting", "    P", 0)
        );
        LineEdit_PulseFactorUp_Y->setText(QApplication::translate("newParameterSetting", "5000", 0));
        LineEdit_PulseFactorDown_Y->setText(QApplication::translate("newParameterSetting", "20", 0));
        label_21->setText(QApplication::translate("newParameterSetting", "/", 0));
        label_22->setText(QApplication::translate("newParameterSetting", "=", 0));
        LineEdit_PulseFactor_Z->setText(QApplication::translate("newParameterSetting", "0.004", 0));
        LineEdit_HomeOffset_Z->setText(QApplication::translate("newParameterSetting", "5", 0));
        LineEdit_HomeSpeed_Z->setText(QApplication::translate("newParameterSetting", "20", 0));
        LineEdit_MaxPos_Z->setText(QApplication::translate("newParameterSetting", "200", 0));
        ComBox_HomeDirection_Z->clear();
        ComBox_HomeDirection_Z->insertItems(0, QStringList()
         << QApplication::translate("newParameterSetting", "    N", 0)
         << QApplication::translate("newParameterSetting", "    P", 0)
        );
        LineEdit_PulseFactorUp_Z->setText(QApplication::translate("newParameterSetting", "5000", 0));
        LineEdit_PulseFactorDown_Z->setText(QApplication::translate("newParameterSetting", "20", 0));
        label_23->setText(QApplication::translate("newParameterSetting", "/", 0));
        label_2->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        label_3->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        label_4->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        label_5->setText(QApplication::translate("newParameterSetting", "\357\274\210mm/s\357\274\211", 0));
        label_6->setText(QApplication::translate("newParameterSetting", "\357\274\210mm/s\357\274\211", 0));
        label_12->setText(QApplication::translate("newParameterSetting", "\357\274\210mm/s\357\274\211", 0));
        label_13->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        label_24->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        label_25->setText(QApplication::translate("newParameterSetting", "\357\274\210mm\357\274\211", 0));
        Btn_ParameterLoade->setText(QApplication::translate("newParameterSetting", "\345\217\202\346\225\260\350\257\273\345\217\226", 0));
    } // retranslateUi

};

namespace Ui {
    class newParameterSetting: public Ui_newParameterSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPARAMETERSETTING_H
