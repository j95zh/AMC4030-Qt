#ifndef NEWMANUALOPERATION_H
#define NEWMANUALOPERATION_H

#include <QDialog>

#include "Commdefine.h"
#include "SystemParam.h"
#include "Communication.h"

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
#include "newcombobox.h"
#include "c_amc4030dll.h"
#include "iostatus.h"

namespace Ui {
class newManualOperation;
}

class newManualOperation : public QDialog
{
    Q_OBJECT

public:
    explicit newManualOperation(QWidget *parent = 0);
    ~newManualOperation();

//    //使用单例类
//    static newManualOperation *_instance_MO;
//    static newManualOperation *Instance_MO() {
//        if (!_instance_MO) {
//            _instance_MO = new newManualOperation;
//        }
//        return _instance_MO;
//    }
//    int tptest();
private:
    Ui::newManualOperation *ui;

    MACHINE_STATUS  tMachineStatus;
    FILESYSTEM      tFileInfo;
    QTimer *timer;

    QMutex mutex;

    QStringList filelist;

    IOStatus * IO_Dialog;

    bool X_Axis_Stop=false;
    bool Y_Axis_Stop=false;
    bool Z_Axis_Stop=false;
    bool All_Axis_Stop=false;

private slots:
    void on_StopAllAxis_clicked();
    void on_X_Home_clicked();
    void on_Y_Home_clicked();
    void on_Z_Home_clicked();

    void readComDataSlot();

    void on_X_Jog_L_pressed();
    void on_X_Jog_L_released();
    void on_X_Jog_R_pressed();
    void on_X_Jog_R_released();
    void on_Y_Jog_L_pressed();
    void on_Y_Jog_L_released();
    void on_Y_Jog_R_pressed();
    void on_Y_Jog_R_released();
    void on_Z_Jog_L_pressed();
    void on_Z_Jog_L_released();
    void on_Z_Jog_R_pressed();
    void on_Z_Jog_R_released();

    void on_CheckBox_Out1_clicked();
    void on_CheckBox_Out2_clicked();
    void on_CheckBox_Out3_clicked();
    void on_CheckBox_Out4_clicked();

    void changeEvent(QEvent *e);
    void on_Btn_OpenAutoControl_clicked();
    void ControlCannotBeUsed();
    void ControlCanBeUsed();
    void GetFileName();

    void on_Btn_DeleteProgram_Controller_clicked();

    void on_Btn_IOStatus_clicked();
    void deleteIOStatusDialog();

signals://自定义信号
    void seek(const QString&);//断开连接时需要发送的信号函数，只需要写类型就可以
};

#endif // NEWMANUALOPERATION_H
