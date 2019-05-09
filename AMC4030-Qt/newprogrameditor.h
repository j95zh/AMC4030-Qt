#ifndef NEWPROGRAMEDITOR_H
#define NEWPROGRAMEDITOR_H

#include <QDialog>

#include "newsavefile.h"
#include "SystemParam.h"

#include <QTimer>
#include <QMutex>
#include <QString>
#include <QMessageBox>
#include <QLibrary>
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <QUrl>
#include <QDesktopServices> ///用于访问桌面服务的类
#include <QDialog>
#include <QComboBox>
#include <QTableWidgetItem>
#include <QEvent>
#include <QDir>
#include <QKeyEvent>//用于设置复制粘贴快捷键

#define TotalProgram 5//设置默认程序的数量

namespace Ui {
class newProgramEditor;
}

class newProgramEditor : public QDialog
{
    Q_OBJECT

public:
    explicit newProgramEditor(QWidget *parent = 0);
    ~newProgramEditor();

    //    //使用单例类
    //    static newProgramEditor *_instance_PE;
    //    static newProgramEditor *Instance_PE() {
    //        if (!_instance_PE) {
    //            _instance_PE = new newProgramEditor;
    //        }
    //        return _instance_PE;
    //    }

    QString Current_FileName;
    QString currentDir;

private:
    Ui::newProgramEditor *ui;

    //复制按钮，用于存放所选择行的内容
    QString name1,name2,name3,name4,name5,name6;

    //用于把表格某一行的数据转换成指令
    QString ISTR1,ISTR2,P1,P2,P3;
    QString last_name;

    MACHINE_STATUS  tMachineStatus;

    int DMSign;//用于DM指令显示的标志
    int CUR_PROG;//用于保存当前选择的程序

    int InitialProgram[TotalProgram];//用于记录program文件夹里是否存在对应的TotalProgram个默认txt文件
private slots:
    void onMyScrollClicked();

    void on_tableWidget_cellClicked(int row, int column);
    void ModifyOption();
    void ComboxToInitialPos();

    void on_Btn_DownLoad_clicked();
    void WriteBinaryFile();

    void on_Btn_NewProgram_clicked();
    void CreateAnEmptyFile();
    void on_Btn_SaveProgram_clicked();
    void WriteInTXT(QString TXT_Name);
    void ListRefresh();
    void WriteInitialProgram(int ProgramCase);
    void ProgramCase0();
    void ProgramCase1();
    void ProgramCase2();
    void ProgramCase3();
    void WriteDefault();
    void on_ComBox_SelectProgram_currentIndexChanged();
    void ImportExcel(QString fileName);
    void WriteEventToFile();
    void on_Btn_DeleteProgram_clicked();
    void DeleteProgram();

    void on_Btn_MoveUpRow_clicked();
    void on_Btn_MoveDownRow_clicked();

    void on_Btn_InsertRow_clicked();
    void on_Btn_RemoveRow_clicked();

    void on_Btn_CopyRow_clicked();
    void on_Btn_PasteRow_clicked();

    void ISTR_Sets_RowColor();
    void CenterContent();
    void reWriteTable();

    void changeEvent(QEvent *e);

    bool eventFilter(QObject *object, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void on_ComBox_SelectProgram_activated();
    void WriteUserSettingsCfgFile();
    void ReadUserSettingsCfgFile();
};

#endif // NEWPROGRAMEDITOR_H
