/********************************************************************************
** Form generated from reading UI file 'iostatus.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOSTATUS_H
#define UI_IOSTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IOStatus
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pb_StopAll;
    QPushButton *pb_StartAll;
    QPushButton *pb_ResetCur;
    QPushButton *pb_StopCur;
    QPushButton *pb_StartCur;
    QPushButton *pb_ResetAll;
    QPushButton *pb_SetCur;
    QTreeWidget *treeWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_CurID;
    QLabel *label_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_5;

    void setupUi(QDialog *IOStatus)
    {
        if (IOStatus->objectName().isEmpty())
            IOStatus->setObjectName(QStringLiteral("IOStatus"));
        IOStatus->resize(870, 480);
        scrollArea = new QScrollArea(IOStatus);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(210, 30, 631, 361));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 629, 359));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pb_StopAll = new QPushButton(IOStatus);
        pb_StopAll->setObjectName(QStringLiteral("pb_StopAll"));
        pb_StopAll->setGeometry(QRect(661, 416, 74, 31));
        pb_StartAll = new QPushButton(IOStatus);
        pb_StartAll->setObjectName(QStringLiteral("pb_StartAll"));
        pb_StartAll->setGeometry(QRect(555, 416, 74, 31));
        pb_ResetCur = new QPushButton(IOStatus);
        pb_ResetCur->setObjectName(QStringLiteral("pb_ResetCur"));
        pb_ResetCur->setGeometry(QRect(423, 416, 74, 31));
        pb_StopCur = new QPushButton(IOStatus);
        pb_StopCur->setObjectName(QStringLiteral("pb_StopCur"));
        pb_StopCur->setGeometry(QRect(317, 416, 74, 31));
        pb_StartCur = new QPushButton(IOStatus);
        pb_StartCur->setObjectName(QStringLiteral("pb_StartCur"));
        pb_StartCur->setGeometry(QRect(211, 416, 74, 31));
        pb_ResetAll = new QPushButton(IOStatus);
        pb_ResetAll->setObjectName(QStringLiteral("pb_ResetAll"));
        pb_ResetAll->setGeometry(QRect(767, 416, 73, 31));
        pb_SetCur = new QPushButton(IOStatus);
        pb_SetCur->setObjectName(QStringLiteral("pb_SetCur"));
        pb_SetCur->setGeometry(QRect(70, 420, 75, 31));
        treeWidget = new QTreeWidget(IOStatus);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(33, 33, 149, 280));
        layoutWidget = new QWidget(IOStatus);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 330, 101, 21));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        label_CurID = new QLabel(layoutWidget);
        label_CurID->setObjectName(QStringLiteral("label_CurID"));
        label_CurID->setEnabled(true);

        horizontalLayout->addWidget(label_CurID);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        layoutWidget1 = new QWidget(IOStatus);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 370, 141, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        layoutWidget->raise();
        treeWidget->raise();
        layoutWidget->raise();
        scrollArea->raise();
        pb_StopAll->raise();
        pb_StartAll->raise();
        pb_ResetCur->raise();
        pb_StopCur->raise();
        pb_StartCur->raise();
        pb_ResetAll->raise();
        pb_SetCur->raise();

        retranslateUi(IOStatus);

        QMetaObject::connectSlotsByName(IOStatus);
    } // setupUi

    void retranslateUi(QDialog *IOStatus)
    {
        IOStatus->setWindowTitle(QApplication::translate("IOStatus", "Dialog", 0));
        pb_StopAll->setText(QApplication::translate("IOStatus", "\345\201\234\346\255\242\346\211\200\346\234\211", 0));
        pb_StartAll->setText(QApplication::translate("IOStatus", "\345\220\257\345\212\250\346\211\200\346\234\211", 0));
        pb_ResetCur->setText(QApplication::translate("IOStatus", "\345\244\215\344\275\215\351\200\211\344\270\255", 0));
        pb_StopCur->setText(QApplication::translate("IOStatus", "\345\201\234\346\255\242\351\200\211\344\270\255", 0));
        pb_StartCur->setText(QApplication::translate("IOStatus", "\345\220\257\345\212\250\351\200\211\344\270\255", 0));
        pb_ResetAll->setText(QApplication::translate("IOStatus", "\345\244\215\344\275\215\346\211\200\346\234\211", 0));
        pb_SetCur->setText(QApplication::translate("IOStatus", "\347\241\256\350\256\244\344\277\256\346\224\271", 0));
        label_3->setText(QApplication::translate("IOStatus", "\345\267\262\351\200\211\344\270\255", 0));
        label_CurID->setText(QApplication::translate("IOStatus", "0", 0));
        label_2->setText(QApplication::translate("IOStatus", "\345\217\267\350\212\202\347\202\271", 0));
        label_4->setText(QApplication::translate("IOStatus", "\344\277\256\346\224\271\344\270\272\357\274\232", 0));
        label_5->setText(QApplication::translate("IOStatus", "\345\217\267\350\212\202\347\202\271", 0));
    } // retranslateUi

};

namespace Ui {
    class IOStatus: public Ui_IOStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOSTATUS_H
