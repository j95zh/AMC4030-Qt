/********************************************************************************
** Form generated from reading UI file 'newmanualoperation.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMANUALOPERATION_H
#define UI_NEWMANUALOPERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "newcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_newManualOperation
{
public:
    QPushButton *X_Jog_L;
    QLabel *label_5;
    QPushButton *Y_Jog_R;
    QPushButton *StopAllAxis;
    QPushButton *X_Home;
    QPushButton *Z_Jog_L;
    QLineEdit *LineEdit_StepDistance;
    QPushButton *Y_Jog_L;
    QLineEdit *LineEdit_ManualSpeed;
    QCheckBox *CheckBox_Step;
    QGroupBox *groupBox_8;
    QLabel *label_4;
    QLineEdit *X_Position;
    QLabel *label_3;
    QLineEdit *Z_Position;
    QLabel *label_2;
    QLineEdit *Y_Position;
    QGroupBox *groupBox_2;
    QCheckBox *CheckBox_Org3;
    QCheckBox *CheckBox_Org1;
    QCheckBox *CheckBox_In4;
    QCheckBox *CheckBox_Org2;
    QCheckBox *CheckBox_In3;
    QCheckBox *CheckBox_In1;
    QCheckBox *CheckBox_In2;
    QGroupBox *groupBox_3;
    QCheckBox *CheckBox_Out1_Status;
    QCheckBox *CheckBox_Out2_Status;
    QCheckBox *CheckBox_Out3_Status;
    QCheckBox *CheckBox_Out4_Status;
    QPushButton *Z_Jog_R;
    QPushButton *Z_Home;
    QLabel *label_13;
    QPushButton *X_Jog_R;
    QPushButton *Y_Home;
    QGroupBox *groupBox_5;
    QCheckBox *CheckBox_Out1;
    QCheckBox *CheckBox_Out2;
    QCheckBox *CheckBox_Out3;
    QCheckBox *CheckBox_Out4;
    QLabel *label_6;
    QPushButton *Btn_OpenAutoControl;
    QLabel *label;
    QCheckBox *cb_RunOnTime;
    QPushButton *Btn_IOStatus;
    QPushButton *Btn_DeleteProgram_Controller;
    newcombobox *SelectProgram_Controller;
    QLabel *label_7;

    void setupUi(QDialog *newManualOperation)
    {
        if (newManualOperation->objectName().isEmpty())
            newManualOperation->setObjectName(QStringLiteral("newManualOperation"));
        newManualOperation->resize(710, 400);
        X_Jog_L = new QPushButton(newManualOperation);
        X_Jog_L->setObjectName(QStringLiteral("X_Jog_L"));
        X_Jog_L->setGeometry(QRect(30, 73, 41, 31));
        label_5 = new QLabel(newManualOperation);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 230, 61, 16));
        Y_Jog_R = new QPushButton(newManualOperation);
        Y_Jog_R->setObjectName(QStringLiteral("Y_Jog_R"));
        Y_Jog_R->setGeometry(QRect(88, 122, 41, 31));
        StopAllAxis = new QPushButton(newManualOperation);
        StopAllAxis->setObjectName(QStringLiteral("StopAllAxis"));
        StopAllAxis->setGeometry(QRect(210, 110, 61, 51));
        X_Home = new QPushButton(newManualOperation);
        X_Home->setObjectName(QStringLiteral("X_Home"));
        X_Home->setGeometry(QRect(146, 73, 41, 31));
        Z_Jog_L = new QPushButton(newManualOperation);
        Z_Jog_L->setObjectName(QStringLiteral("Z_Jog_L"));
        Z_Jog_L->setGeometry(QRect(30, 170, 41, 31));
        LineEdit_StepDistance = new QLineEdit(newManualOperation);
        LineEdit_StepDistance->setObjectName(QStringLiteral("LineEdit_StepDistance"));
        LineEdit_StepDistance->setGeometry(QRect(100, 260, 41, 20));
        Y_Jog_L = new QPushButton(newManualOperation);
        Y_Jog_L->setObjectName(QStringLiteral("Y_Jog_L"));
        Y_Jog_L->setGeometry(QRect(30, 122, 41, 31));
        LineEdit_ManualSpeed = new QLineEdit(newManualOperation);
        LineEdit_ManualSpeed->setObjectName(QStringLiteral("LineEdit_ManualSpeed"));
        LineEdit_ManualSpeed->setGeometry(QRect(100, 230, 41, 20));
        CheckBox_Step = new QCheckBox(newManualOperation);
        CheckBox_Step->setObjectName(QStringLiteral("CheckBox_Step"));
        CheckBox_Step->setEnabled(true);
        CheckBox_Step->setGeometry(QRect(30, 260, 59, 21));
        CheckBox_Step->setAcceptDrops(false);
        CheckBox_Step->setAutoFillBackground(false);
        CheckBox_Step->setCheckable(true);
        CheckBox_Step->setChecked(false);
        groupBox_8 = new QGroupBox(newManualOperation);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(300, 30, 281, 341));
        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 120, 71, 16));
        X_Position = new QLineEdit(groupBox_8);
        X_Position->setObjectName(QStringLiteral("X_Position"));
        X_Position->setGeometry(QRect(100, 40, 91, 20));
        label_3 = new QLabel(groupBox_8);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 80, 71, 16));
        Z_Position = new QLineEdit(groupBox_8);
        Z_Position->setObjectName(QStringLiteral("Z_Position"));
        Z_Position->setGeometry(QRect(100, 120, 91, 20));
        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 40, 71, 16));
        Y_Position = new QLineEdit(groupBox_8);
        Y_Position->setObjectName(QStringLiteral("Y_Position"));
        Y_Position->setGeometry(QRect(100, 80, 91, 20));
        groupBox_2 = new QGroupBox(groupBox_8);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 170, 231, 71));
        CheckBox_Org3 = new QCheckBox(groupBox_2);
        CheckBox_Org3->setObjectName(QStringLiteral("CheckBox_Org3"));
        CheckBox_Org3->setEnabled(false);
        CheckBox_Org3->setGeometry(QRect(160, 50, 71, 16));
        CheckBox_Org1 = new QCheckBox(groupBox_2);
        CheckBox_Org1->setObjectName(QStringLiteral("CheckBox_Org1"));
        CheckBox_Org1->setEnabled(false);
        CheckBox_Org1->setGeometry(QRect(20, 50, 71, 16));
        CheckBox_In4 = new QCheckBox(groupBox_2);
        CheckBox_In4->setObjectName(QStringLiteral("CheckBox_In4"));
        CheckBox_In4->setEnabled(false);
        CheckBox_In4->setGeometry(QRect(170, 20, 41, 16));
        CheckBox_Org2 = new QCheckBox(groupBox_2);
        CheckBox_Org2->setObjectName(QStringLiteral("CheckBox_Org2"));
        CheckBox_Org2->setEnabled(false);
        CheckBox_Org2->setGeometry(QRect(90, 50, 71, 16));
        CheckBox_In3 = new QCheckBox(groupBox_2);
        CheckBox_In3->setObjectName(QStringLiteral("CheckBox_In3"));
        CheckBox_In3->setEnabled(false);
        CheckBox_In3->setGeometry(QRect(120, 20, 51, 16));
        CheckBox_In1 = new QCheckBox(groupBox_2);
        CheckBox_In1->setObjectName(QStringLiteral("CheckBox_In1"));
        CheckBox_In1->setEnabled(false);
        CheckBox_In1->setGeometry(QRect(20, 20, 51, 16));
        CheckBox_In2 = new QCheckBox(groupBox_2);
        CheckBox_In2->setObjectName(QStringLiteral("CheckBox_In2"));
        CheckBox_In2->setEnabled(false);
        CheckBox_In2->setGeometry(QRect(70, 20, 51, 16));
        groupBox_3 = new QGroupBox(groupBox_8);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 260, 231, 71));
        CheckBox_Out1_Status = new QCheckBox(groupBox_3);
        CheckBox_Out1_Status->setObjectName(QStringLiteral("CheckBox_Out1_Status"));
        CheckBox_Out1_Status->setEnabled(false);
        CheckBox_Out1_Status->setGeometry(QRect(20, 20, 71, 16));
        CheckBox_Out2_Status = new QCheckBox(groupBox_3);
        CheckBox_Out2_Status->setObjectName(QStringLiteral("CheckBox_Out2_Status"));
        CheckBox_Out2_Status->setEnabled(false);
        CheckBox_Out2_Status->setGeometry(QRect(110, 20, 71, 16));
        CheckBox_Out3_Status = new QCheckBox(groupBox_3);
        CheckBox_Out3_Status->setObjectName(QStringLiteral("CheckBox_Out3_Status"));
        CheckBox_Out3_Status->setEnabled(false);
        CheckBox_Out3_Status->setGeometry(QRect(20, 40, 71, 16));
        CheckBox_Out4_Status = new QCheckBox(groupBox_3);
        CheckBox_Out4_Status->setObjectName(QStringLiteral("CheckBox_Out4_Status"));
        CheckBox_Out4_Status->setEnabled(false);
        CheckBox_Out4_Status->setGeometry(QRect(110, 40, 71, 16));
        Z_Jog_R = new QPushButton(newManualOperation);
        Z_Jog_R->setObjectName(QStringLiteral("Z_Jog_R"));
        Z_Jog_R->setGeometry(QRect(88, 170, 41, 31));
        Z_Home = new QPushButton(newManualOperation);
        Z_Home->setObjectName(QStringLiteral("Z_Home"));
        Z_Home->setGeometry(QRect(146, 170, 41, 31));
        label_13 = new QLabel(newManualOperation);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(150, 260, 21, 21));
        X_Jog_R = new QPushButton(newManualOperation);
        X_Jog_R->setObjectName(QStringLiteral("X_Jog_R"));
        X_Jog_R->setGeometry(QRect(88, 73, 41, 31));
        Y_Home = new QPushButton(newManualOperation);
        Y_Home->setObjectName(QStringLiteral("Y_Home"));
        Y_Home->setGeometry(QRect(146, 122, 41, 31));
        groupBox_5 = new QGroupBox(newManualOperation);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 300, 221, 71));
        CheckBox_Out1 = new QCheckBox(groupBox_5);
        CheckBox_Out1->setObjectName(QStringLiteral("CheckBox_Out1"));
        CheckBox_Out1->setGeometry(QRect(30, 20, 71, 16));
        CheckBox_Out2 = new QCheckBox(groupBox_5);
        CheckBox_Out2->setObjectName(QStringLiteral("CheckBox_Out2"));
        CheckBox_Out2->setGeometry(QRect(120, 20, 71, 16));
        CheckBox_Out3 = new QCheckBox(groupBox_5);
        CheckBox_Out3->setObjectName(QStringLiteral("CheckBox_Out3"));
        CheckBox_Out3->setGeometry(QRect(30, 40, 71, 16));
        CheckBox_Out4 = new QCheckBox(groupBox_5);
        CheckBox_Out4->setObjectName(QStringLiteral("CheckBox_Out4"));
        CheckBox_Out4->setGeometry(QRect(120, 40, 71, 16));
        label_6 = new QLabel(newManualOperation);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(150, 220, 41, 41));
        Btn_OpenAutoControl = new QPushButton(newManualOperation);
        Btn_OpenAutoControl->setObjectName(QStringLiteral("Btn_OpenAutoControl"));
        Btn_OpenAutoControl->setGeometry(QRect(30, 30, 91, 31));
        label = new QLabel(newManualOperation);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 30, 171, 31));
        label->setStyleSheet(QStringLiteral("font: 75 11pt \"Century\";"));
        cb_RunOnTime = new QCheckBox(newManualOperation);
        cb_RunOnTime->setObjectName(QStringLiteral("cb_RunOnTime"));
        cb_RunOnTime->setGeometry(QRect(140, 40, 101, 16));
        Btn_IOStatus = new QPushButton(newManualOperation);
        Btn_IOStatus->setObjectName(QStringLiteral("Btn_IOStatus"));
        Btn_IOStatus->setGeometry(QRect(620, 165, 75, 31));
        Btn_DeleteProgram_Controller = new QPushButton(newManualOperation);
        Btn_DeleteProgram_Controller->setObjectName(QStringLiteral("Btn_DeleteProgram_Controller"));
        Btn_DeleteProgram_Controller->setGeometry(QRect(619, 99, 75, 31));
        SelectProgram_Controller = new newcombobox(newManualOperation);
        SelectProgram_Controller->setObjectName(QStringLiteral("SelectProgram_Controller"));
        SelectProgram_Controller->setGeometry(QRect(620, 58, 71, 21));
        SelectProgram_Controller->setContextMenuPolicy(Qt::CustomContextMenu);
        label_7 = new QLabel(newManualOperation);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(620, 40, 84, 16));

        retranslateUi(newManualOperation);

        QMetaObject::connectSlotsByName(newManualOperation);
    } // setupUi

    void retranslateUi(QDialog *newManualOperation)
    {
        newManualOperation->setWindowTitle(QApplication::translate("newManualOperation", "Dialog", 0));
        X_Jog_L->setText(QApplication::translate("newManualOperation", "X -", 0));
        label_5->setText(QApplication::translate("newManualOperation", "\346\211\213\345\212\250\351\200\237\345\272\246\357\274\232", 0));
        Y_Jog_R->setText(QApplication::translate("newManualOperation", "Y +", 0));
        StopAllAxis->setText(QApplication::translate("newManualOperation", "\345\201\234\346\255\242", 0));
        X_Home->setText(QApplication::translate("newManualOperation", "\345\233\236\351\233\266", 0));
        Z_Jog_L->setText(QApplication::translate("newManualOperation", "Z -", 0));
        LineEdit_StepDistance->setText(QApplication::translate("newManualOperation", "20", 0));
        Y_Jog_L->setText(QApplication::translate("newManualOperation", "Y -", 0));
        LineEdit_ManualSpeed->setText(QApplication::translate("newManualOperation", "50", 0));
        CheckBox_Step->setText(QApplication::translate("newManualOperation", "\346\255\245\350\277\233\357\274\232", 0));
        groupBox_8->setTitle(QApplication::translate("newManualOperation", "\346\234\272\345\231\250\347\212\266\346\200\201\357\274\232", 0));
        label_4->setText(QApplication::translate("newManualOperation", "Z\350\275\264\344\275\215\347\275\256\357\274\232", 0));
        label_3->setText(QApplication::translate("newManualOperation", "Y\350\275\264\344\275\215\347\275\256\357\274\232", 0));
        label_2->setText(QApplication::translate("newManualOperation", "X\350\275\264\344\275\215\347\275\256\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("newManualOperation", "\350\276\223\345\205\245\345\217\243\347\212\266\346\200\201\357\274\232", 0));
        CheckBox_Org3->setText(QApplication::translate("newManualOperation", "ORG 3", 0));
        CheckBox_Org1->setText(QApplication::translate("newManualOperation", "ORG 1", 0));
        CheckBox_In4->setText(QApplication::translate("newManualOperation", "IN 4", 0));
        CheckBox_Org2->setText(QApplication::translate("newManualOperation", "ORG 2", 0));
        CheckBox_In3->setText(QApplication::translate("newManualOperation", "IN 3", 0));
        CheckBox_In1->setText(QApplication::translate("newManualOperation", "IN 1", 0));
        CheckBox_In2->setText(QApplication::translate("newManualOperation", "IN 2", 0));
        groupBox_3->setTitle(QApplication::translate("newManualOperation", "\350\276\223\345\207\272\345\217\243\347\212\266\346\200\201\357\274\232", 0));
        CheckBox_Out1_Status->setText(QApplication::translate("newManualOperation", "OUT 1", 0));
        CheckBox_Out2_Status->setText(QApplication::translate("newManualOperation", "OUT 2", 0));
        CheckBox_Out3_Status->setText(QApplication::translate("newManualOperation", "OUT 3", 0));
        CheckBox_Out4_Status->setText(QApplication::translate("newManualOperation", "OUT 4", 0));
        Z_Jog_R->setText(QApplication::translate("newManualOperation", "Z +", 0));
        Z_Home->setText(QApplication::translate("newManualOperation", "\345\233\236\351\233\266", 0));
        label_13->setText(QApplication::translate("newManualOperation", "<html><head/><body><p><span style=\" font-size:12pt;\">mm</span></p></body></html>", 0));
        X_Jog_R->setText(QApplication::translate("newManualOperation", "X +", 0));
        Y_Home->setText(QApplication::translate("newManualOperation", "\345\233\236\351\233\266", 0));
        groupBox_5->setTitle(QApplication::translate("newManualOperation", "\350\276\223\345\207\272\345\217\243\351\200\211\346\213\251\357\274\232", 0));
        CheckBox_Out1->setText(QApplication::translate("newManualOperation", "OUT 1", 0));
        CheckBox_Out2->setText(QApplication::translate("newManualOperation", "OUT 2", 0));
        CheckBox_Out3->setText(QApplication::translate("newManualOperation", "OUT 3", 0));
        CheckBox_Out4->setText(QApplication::translate("newManualOperation", "OUT 4", 0));
        label_6->setText(QApplication::translate("newManualOperation", "<html><head/><body><p><span style=\" font-size:12pt;\">mm/s</span></p></body></html>", 0));
        Btn_OpenAutoControl->setText(QString());
        label->setText(QString());
        cb_RunOnTime->setText(QApplication::translate("newManualOperation", "\344\270\212\347\224\265\350\207\252\345\212\250\350\277\220\350\241\214", 0));
        Btn_IOStatus->setText(QApplication::translate("newManualOperation", "IO\346\211\251\345\261\225", 0));
        Btn_DeleteProgram_Controller->setText(QApplication::translate("newManualOperation", "\345\210\240\351\231\244\347\250\213\345\272\217", 0));
        label_7->setText(QApplication::translate("newManualOperation", "\346\216\247\345\210\266\345\215\241\345\206\205\347\250\213\345\272\217\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class newManualOperation: public Ui_newManualOperation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMANUALOPERATION_H
