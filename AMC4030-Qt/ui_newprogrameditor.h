/********************************************************************************
** Form generated from reading UI file 'newprogrameditor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROGRAMEDITOR_H
#define UI_NEWPROGRAMEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_newProgramEditor
{
public:
    QTableWidget *tableWidget;
    QPushButton *Btn_PasteRow;
    QPushButton *Btn_RemoveRow;
    QComboBox *ComBox_SelectProgram;
    QPushButton *Btn_NewProgram;
    QPushButton *Btn_CopyRow;
    QComboBox *Combox;
    QPushButton *Btn_SaveProgram;
    QPushButton *Btn_MoveUpRow;
    QPushButton *Btn_MoveDownRow;
    QPushButton *Btn_InsertRow;
    QPushButton *Btn_DeleteProgram;
    QFrame *line;
    QFrame *line_2;
    QPushButton *Btn_DownLoad;

    void setupUi(QDialog *newProgramEditor)
    {
        if (newProgramEditor->objectName().isEmpty())
            newProgramEditor->setObjectName(QStringLiteral("newProgramEditor"));
        newProgramEditor->resize(710, 400);
        tableWidget = new QTableWidget(newProgramEditor);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 601, 431));
        Btn_PasteRow = new QPushButton(newProgramEditor);
        Btn_PasteRow->setObjectName(QStringLiteral("Btn_PasteRow"));
        Btn_PasteRow->setGeometry(QRect(630, 220, 71, 23));
        Btn_RemoveRow = new QPushButton(newProgramEditor);
        Btn_RemoveRow->setObjectName(QStringLiteral("Btn_RemoveRow"));
        Btn_RemoveRow->setGeometry(QRect(630, 160, 71, 23));
        ComBox_SelectProgram = new QComboBox(newProgramEditor);
        ComBox_SelectProgram->setObjectName(QStringLiteral("ComBox_SelectProgram"));
        ComBox_SelectProgram->setGeometry(QRect(630, 20, 71, 21));
        ComBox_SelectProgram->setContextMenuPolicy(Qt::CustomContextMenu);
        Btn_NewProgram = new QPushButton(newProgramEditor);
        Btn_NewProgram->setObjectName(QStringLiteral("Btn_NewProgram"));
        Btn_NewProgram->setGeometry(QRect(630, 280, 71, 23));
        Btn_CopyRow = new QPushButton(newProgramEditor);
        Btn_CopyRow->setObjectName(QStringLiteral("Btn_CopyRow"));
        Btn_CopyRow->setGeometry(QRect(630, 190, 71, 23));
        Combox = new QComboBox(newProgramEditor);
        Combox->setObjectName(QStringLiteral("Combox"));
        Combox->setGeometry(QRect(490, 360, 101, 31));
        Btn_SaveProgram = new QPushButton(newProgramEditor);
        Btn_SaveProgram->setObjectName(QStringLiteral("Btn_SaveProgram"));
        Btn_SaveProgram->setGeometry(QRect(630, 310, 71, 23));
        Btn_MoveUpRow = new QPushButton(newProgramEditor);
        Btn_MoveUpRow->setObjectName(QStringLiteral("Btn_MoveUpRow"));
        Btn_MoveUpRow->setGeometry(QRect(630, 70, 71, 23));
        Btn_MoveDownRow = new QPushButton(newProgramEditor);
        Btn_MoveDownRow->setObjectName(QStringLiteral("Btn_MoveDownRow"));
        Btn_MoveDownRow->setGeometry(QRect(630, 100, 71, 23));
        Btn_InsertRow = new QPushButton(newProgramEditor);
        Btn_InsertRow->setObjectName(QStringLiteral("Btn_InsertRow"));
        Btn_InsertRow->setGeometry(QRect(630, 130, 71, 23));
        Btn_DeleteProgram = new QPushButton(newProgramEditor);
        Btn_DeleteProgram->setObjectName(QStringLiteral("Btn_DeleteProgram"));
        Btn_DeleteProgram->setGeometry(QRect(630, 340, 71, 23));
        line = new QFrame(newProgramEditor);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(620, 40, 91, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(newProgramEditor);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(620, 250, 91, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        Btn_DownLoad = new QPushButton(newProgramEditor);
        Btn_DownLoad->setObjectName(QStringLiteral("Btn_DownLoad"));
        Btn_DownLoad->setGeometry(QRect(630, 370, 71, 23));

        retranslateUi(newProgramEditor);

        QMetaObject::connectSlotsByName(newProgramEditor);
    } // setupUi

    void retranslateUi(QDialog *newProgramEditor)
    {
        newProgramEditor->setWindowTitle(QApplication::translate("newProgramEditor", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("newProgramEditor", "\346\214\207\344\273\244\351\233\206", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("newProgramEditor", "\346\214\207\344\273\244", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("newProgramEditor", "\345\217\202\346\225\260 1", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("newProgramEditor", "\345\217\202\346\225\260 2", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("newProgramEditor", "\345\217\202\346\225\260 3", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("newProgramEditor", "\345\244\207\346\263\250\344\277\241\346\201\257", 0));
        Btn_PasteRow->setText(QApplication::translate("newProgramEditor", "\347\262\230\350\264\264\344\273\243\347\240\201\350\241\214", 0));
        Btn_RemoveRow->setText(QApplication::translate("newProgramEditor", "\345\210\240\351\231\244\344\273\243\347\240\201\350\241\214", 0));
        Btn_NewProgram->setText(QApplication::translate("newProgramEditor", "\346\226\260\345\273\272\347\250\213\345\272\217", 0));
        Btn_CopyRow->setText(QApplication::translate("newProgramEditor", "\345\244\215\345\210\266\351\200\211\344\270\255\350\241\214", 0));
        Btn_SaveProgram->setText(QApplication::translate("newProgramEditor", "\344\277\235\345\255\230\347\250\213\345\272\217", 0));
        Btn_MoveUpRow->setText(QApplication::translate("newProgramEditor", "\346\214\207\345\256\232\350\241\214\344\270\212\347\247\273", 0));
        Btn_MoveDownRow->setText(QApplication::translate("newProgramEditor", "\346\214\207\345\256\232\350\241\214\344\270\213\347\247\273", 0));
        Btn_InsertRow->setText(QApplication::translate("newProgramEditor", "\346\217\222\345\205\245\344\273\243\347\240\201\350\241\214", 0));
        Btn_DeleteProgram->setText(QApplication::translate("newProgramEditor", "\345\210\240\351\231\244\347\250\213\345\272\217", 0));
        Btn_DownLoad->setText(QApplication::translate("newProgramEditor", "\344\270\213\350\275\275\347\250\213\345\272\217", 0));
    } // retranslateUi

};

namespace Ui {
    class newProgramEditor: public Ui_newProgramEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROGRAMEDITOR_H
