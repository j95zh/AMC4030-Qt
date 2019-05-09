#include "newmanualoperation.h"
#include "ui_newmanualoperation.h"

#include "amc4030.h"
#include "c_amc4030dll.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QtCore/QCoreApplication>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QComboBox>
#include <synchapi.h>

#define REFRESH_TIME 20

//newManualOperation *newManualOperation::_instance_MO = 0;

/*
int newManualOperation::tptest()
{
}
*/

newManualOperation::newManualOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newManualOperation)
{
    ui->setupUi(this);

    //设置界面大小
    this->setMaximumSize(710, 400);
    this->setMinimumSize(710, 400);

    //使输入口输出口状态里的checkBox都不能使用，只能读
    ui->CheckBox_In1->setEnabled(0);
    ui->CheckBox_In2->setEnabled(0);
    ui->CheckBox_In3->setEnabled(0);
    ui->CheckBox_In4->setEnabled(0);
    ui->CheckBox_Org1->setEnabled(0);
    ui->CheckBox_Org2->setEnabled(0);
    ui->CheckBox_Org3->setEnabled(0);
    ui->CheckBox_Out1_Status->setEnabled(0);
    ui->CheckBox_Out2_Status->setEnabled(0);
    ui->CheckBox_Out3_Status->setEnabled(0);
    ui->CheckBox_Out4_Status->setEnabled(0);

    newcombobox *newComboBox = new newcombobox();
    connect(ui->SelectProgram_Controller, SIGNAL(clicked(bool)), this, SLOT(GetFileName()));
    AMC4030::pComTimerWork->ComThrConPara.GetFileName = 1;//软件开启后首先执行一次获取文件名

    //使显示XYZ轴坐标的lineEdit不能编辑
    ui->X_Position->setEnabled(0);
    ui->Y_Position->setEnabled(0);
    ui->Z_Position->setEnabled(0);

    AMC4030_DLL.Q_OpenLink(5, 115200);

    //开启通信子线程
    AMC4030::pComTimerWork = new Communication;
    AMC4030::pComThread = new QThread(this);
    connect(AMC4030::pComThread , SIGNAL(started()),AMC4030::pComTimerWork, SLOT(readComDataSlot()));
    connect(AMC4030::pComThread , SIGNAL(finished()), AMC4030::pComTimerWork, SLOT(deleteLater()));
    AMC4030::pComTimerWork->moveToThread(AMC4030::pComThread);
    AMC4030::pComThread->start();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readComDataSlot()));
    timer->start(REFRESH_TIME);

    int result_GMS = 10;
    result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    if(result_GMS == 1) //表示当前已连接控制器
    {
        int Status = 100;
        Status = tMachineStatus.dwWorkStatus;
        qDebug() << "进入界面时tMachineStatus.dwWorkStatus的值：" << Status;

        if(Status & 0x02) //自动控制的状态
        {
            ui->Btn_OpenAutoControl->setEnabled(1);
            ui->Btn_OpenAutoControl->setText(QObject::tr("开启手动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Green;");
            ui->label->setText(QObject::tr("当前状态：自动控制"));
            ui->label->setStyleSheet("color:Blue;""font:75 11pt;");

            ControlCannotBeUsed();//使界面左边的控件都不能使用

            //emit seek(tr("自动控制"));
        }
        else
        {
            ui->Btn_OpenAutoControl->setEnabled(1);
            ui->Btn_OpenAutoControl->setText(QObject::tr("开启自动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Blue;");
            ui->label->setText(QObject::tr("当前状态：手动控制"));//状态显示
            ui->label->setStyleSheet("color:Green;""font:75 11pt;");//设置颜色和字体大小

            ControlCanBeUsed();//使界面左边的控件能正常使用使用

            //emit seek(tr("手动控制"));
        }
    }
    else
    {
        ui->X_Jog_L->setEnabled(0);
        ui->X_Jog_R->setEnabled(0);
        ui->X_Home->setEnabled(0);
        ui->Y_Jog_L->setEnabled(0);
        ui->Y_Jog_R->setEnabled(0);
        ui->Y_Home->setEnabled(0);
        ui->Z_Jog_L->setEnabled(0);
        ui->Z_Jog_R->setEnabled(0);
        ui->Z_Home->setEnabled(0);
        ui->StopAllAxis->setEnabled(0);

        ui->Btn_OpenAutoControl->setText(QObject::tr("未连接！"));
        ui->Btn_OpenAutoControl->setStyleSheet("color:Red;");
        ui->Btn_OpenAutoControl->setEnabled(0);

        //emit seek(tr("未连接"));
    }
    qDebug()<<"进入shoudong界面的构造函数";

    ui->label->setVisible(false);
    ui->SelectProgram_Controller->addItem(AMC4030::currentFilename);

    IO_Dialog = NULL;
    connect(IO_Dialog, SIGNAL(deleteIO_Dialog()), this, SLOT(deleteIOStatusDialog()));
}

newManualOperation::~newManualOperation()
{
    //timer->stop();
    AMC4030::currentFilename = ui->SelectProgram_Controller->currentText();
    delete ui;
}

void newManualOperation::readComDataSlot()
{
    //qDebug()<<"hahahahhaha";
    int i = 0;
    if(AMC4030::pComTimerWork->ComThrConPara.LinkStatus)
    {
        int result_GMS = 10;
        result_GMS = AMC4030::pComTimerWork->ComThrConPara.result_GMS;
        if(result_GMS == 1) //表示当前已连接控制器
        {
            //emit seek(tr("已连接"));

            int Status = 100;
            Status = AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwWorkStatus;

            //电机没有正常停止
            if(Status & 0x02) //自动控制的状态
            {
                ui->Btn_OpenAutoControl->setEnabled(1);
                ui->Btn_OpenAutoControl->setText(QObject::tr("开启手动控制"));
                ui->Btn_OpenAutoControl->setStyleSheet("color:Green;");
                ui->label->setText(QObject::tr("当前状态：自动控制"));
                ui->label->setStyleSheet("color:Blue;""font:75 11pt;");

                ControlCannotBeUsed();//使界面左边的控件都不能使用

                //emit seek(tr("自动控制"));
            }
            else
            {
                ui->Btn_OpenAutoControl->setEnabled(1);
                ui->Btn_OpenAutoControl->setText(QObject::tr("开启自动控制"));
                ui->Btn_OpenAutoControl->setStyleSheet("color:Blue;");
                ui->label->setText(QObject::tr("当前状态：手动控制"));
                ui->label->setStyleSheet("color:Green;""font:75 11pt;");

                ControlCanBeUsed();//使界面左边的控件能正常使用使用

                //emit seek(tr("手动控制"));
            }
            /////////////
            ui->X_Position->   setText(QString::number(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.nPos[0] / 100000.0));
            ui->Y_Position->   setText(QString::number(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.nPos[1] / 100000.0));
            ui->Z_Position->   setText(QString::number(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.nPos[2] / 100000.0));

            //输入口状态判定
            ui->CheckBox_In1->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x01);
            ui->CheckBox_In2->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x02);
            ui->CheckBox_In3->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x04);
            ui->CheckBox_In4->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x08);

            //原点状态判定
            ui->CheckBox_Org1->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x10);
            ui->CheckBox_Org2->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x20);
            ui->CheckBox_Org3->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwInputStatus & 0x40);

            //输出口状态判定
            ui->CheckBox_Out1_Status->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwOutputStatus & 0x01);
            ui->CheckBox_Out2_Status->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwOutputStatus & 0x02);
            ui->CheckBox_Out3_Status->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwOutputStatus & 0x04);
            ui->CheckBox_Out4_Status->setChecked(AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.dwOutputStatus & 0x08);

        }
        else
        {
            ui->X_Position->   setText("");
            ui->Y_Position->   setText("");
            ui->Z_Position->   setText("");

            ui->CheckBox_In1->setChecked(0);
            ui->CheckBox_In2->setChecked(0);
            ui->CheckBox_In3->setChecked(0);
            ui->CheckBox_In4->setChecked(0);

            ui->CheckBox_Org1->setChecked(0);
            ui->CheckBox_Org2->setChecked(0);
            ui->CheckBox_Org3->setChecked(0);

            ui->CheckBox_Out1_Status->setChecked(0);
            ui->CheckBox_Out2_Status->setChecked(0);
            ui->CheckBox_Out3_Status->setChecked(0);
            ui->CheckBox_Out4_Status->setChecked(0);

            /////////////
            ui->X_Jog_L->setEnabled(0);
            ui->X_Jog_R->setEnabled(0);
            ui->X_Home->setEnabled(0);
            ui->Y_Jog_L->setEnabled(0);
            ui->Y_Jog_R->setEnabled(0);
            ui->Y_Home->setEnabled(0);
            ui->Z_Jog_L->setEnabled(0);
            ui->Z_Jog_R->setEnabled(0);
            ui->Z_Home->setEnabled(0);
            ui->StopAllAxis->setEnabled(0);

            ui->Btn_OpenAutoControl->setText(QObject::tr("未连接！"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Red;");
            ui->Btn_OpenAutoControl->setEnabled(0);
            ui->label->setText("");

            //emit seek(tr("未连接"));
        }
    }
    else
    {
        ui->X_Jog_L->setEnabled(0);
        ui->X_Jog_R->setEnabled(0);
        ui->X_Home->setEnabled(0);
        ui->Y_Jog_L->setEnabled(0);
        ui->Y_Jog_R->setEnabled(0);
        ui->Y_Home->setEnabled(0);
        ui->Z_Jog_L->setEnabled(0);
        ui->Z_Jog_R->setEnabled(0);
        ui->Z_Home->setEnabled(0);
        ui->StopAllAxis->setEnabled(0);

        ui->Btn_OpenAutoControl->setText(QObject::tr("未连接！"));
        ui->Btn_OpenAutoControl->setStyleSheet("color:Red;");
        ui->Btn_OpenAutoControl->setEnabled(0);

        //emit seek(tr("未连接"));
    }
}

//X轴回零
void newManualOperation::on_X_Home_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.xHome=1;
}

//Y轴回零
void newManualOperation::on_Y_Home_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.yHome=1;
}

//Z轴回零
void newManualOperation::on_Z_Home_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.zHome=1;
}

//所有轴停止
void newManualOperation::on_StopAllAxis_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.stopAll=1;
}

// X - 运动
void newManualOperation::on_X_Jog_L_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.xJogL=1;
}

void newManualOperation::on_X_Jog_L_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.xStop=1;
}

// X +运动
void newManualOperation::on_X_Jog_R_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.xJogR=1;
}

void newManualOperation::on_X_Jog_R_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.xStop=1;
}

// Y - 运动
void newManualOperation::on_Y_Jog_L_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.yJogL=1;
}

void newManualOperation::on_Y_Jog_L_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.yStop=1;
}

// Y+ 运动
void newManualOperation::on_Y_Jog_R_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.yJogR=1;
}

void newManualOperation::on_Y_Jog_R_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.yStop=1;
}

// Z - 运动
void newManualOperation::on_Z_Jog_L_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.zJogL=1;
}

void newManualOperation::on_Z_Jog_L_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.zStop=1;
}

// Z + 运动
void newManualOperation::on_Z_Jog_R_pressed()
{
    AMC4030::pComTimerWork->ComThrConPara.manuSpeed = ui->LineEdit_ManualSpeed->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.manuDis = 99999.999f;
    if(ui->CheckBox_Step->isChecked())  ///如果是选择了距离模式，则更新距离
        AMC4030::pComTimerWork->ComThrConPara.manuDis = ui->LineEdit_StepDistance->text().toFloat();
    AMC4030::pComTimerWork->ComThrConPara.zJogR=1;
}

void newManualOperation::on_Z_Jog_R_released()
{
    if(ui->CheckBox_Step->isChecked() == 0)
        AMC4030::pComTimerWork->ComThrConPara.zStop=1;
}

//输出口状态选择
void newManualOperation::on_CheckBox_Out1_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.SetOutNum=1;
    AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 0;
    if(ui->CheckBox_Out1->isChecked())
        AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 1;
    AMC4030::pComTimerWork->ComThrConPara.SetOutputBit=1;
}

void newManualOperation::on_CheckBox_Out2_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.SetOutNum=2;
    AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 0;
    if(ui->CheckBox_Out2->isChecked())
        AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 1;
    AMC4030::pComTimerWork->ComThrConPara.SetOutputBit=1;
}

void newManualOperation::on_CheckBox_Out3_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.SetOutNum=3;
    AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 0;
    if(ui->CheckBox_Out3->isChecked())
        AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 1;
    AMC4030::pComTimerWork->ComThrConPara.SetOutputBit=1;
}

void newManualOperation::on_CheckBox_Out4_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.SetOutNum=4;
    AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 0;
    if(ui->CheckBox_Out4->isChecked())
        AMC4030::pComTimerWork->ComThrConPara.SetOutStatus = 1;
    AMC4030::pComTimerWork->ComThrConPara.SetOutputBit=1;
}

//开启自动控制或者开启手动控制
void newManualOperation::on_Btn_OpenAutoControl_clicked()
{
    if(ui->Btn_OpenAutoControl->text() == tr("开启自动控制"))
    {
        int result_GMS = 10;
        result_GMS = AMC4030::pComTimerWork->ComThrConPara.result_GMS;
        if(result_GMS == 1) //表示当前已连接控制器
        {
            /*2019年2月27日增加，根据当前选中文件名开启控制卡内对应的加工文件自动控制*/
            if(ui->SelectProgram_Controller->currentText().isEmpty())
                return;
            memset(AMC4030::pComTimerWork->ComThrConPara.filename, 0, sizeof(AMC4030::pComTimerWork->ComThrConPara.filename));

            //获取文件名
            QString filename = ui->SelectProgram_Controller->currentText();

            //转换为char字符型
            QByteArray temp = filename.toLatin1();

            int i = temp.size();
            for(i = 0; i < temp.size();i++)
            {
                AMC4030::pComTimerWork->ComThrConPara.filename[i] = temp[i];
            }
            AMC4030::pComTimerWork->ComThrConPara.NameSize = temp.size();
            AMC4030::pComTimerWork->ComThrConPara.isRunOnTime = ui->cb_RunOnTime->isChecked();
            /*************************************************************/

            AMC4030::pComTimerWork->ComThrConPara.autoRun=1;

            ui->Btn_OpenAutoControl->setText(QObject::tr("开启手动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Green;");
            ui->label->setText(QObject::tr("当前状态：自动控制"));
            ui->label->setStyleSheet("color:Blue;""font:75 11pt;");

            ControlCannotBeUsed();//使界面左边的控件都不能使用

            emit seek(tr("自动控制"));
        }
    }

    else if(ui->Btn_OpenAutoControl->text() == tr ("开启手动控制"))
    {
        int result_GMS = 10;
        result_GMS = AMC4030::pComTimerWork->ComThrConPara.result_GMS;
        if(result_GMS == 1) //表示当前已连接控制器
        {
            on_StopAllAxis_clicked();//先停止所有

            ui->Btn_OpenAutoControl->setText(QObject::tr("开启自动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Blue;");
            ui->label->setText(QObject::tr("当前状态：手动控制"));
            ui->label->setStyleSheet("color:Green;""font:75 11pt;");

            ControlCanBeUsed();//使界面左边的控件能正常使用使用
            emit seek(tr("手动控制"));
        }
    }
}

//使界面左边的控件都不能使用
void newManualOperation::ControlCannotBeUsed()
{
    ui->X_Jog_L->setEnabled(0);
    ui->X_Jog_R->setEnabled(0);
    ui->X_Home->setEnabled(0);
    ui->Y_Jog_L->setEnabled(0);
    ui->Y_Jog_R->setEnabled(0);
    ui->Y_Home->setEnabled(0);
    ui->Z_Jog_L->setEnabled(0);
    ui->Z_Jog_R->setEnabled(0);
    ui->Z_Home->setEnabled(0);

    ui->label_5->setEnabled(0);
    ui->LineEdit_ManualSpeed->setEnabled(0);
    ui->label_6->setEnabled(0);
    ui->CheckBox_Step->setEnabled(0);
    ui->LineEdit_StepDistance->setEnabled(0);
    ui->label_13->setEnabled(0);
    ui->groupBox_5->setEnabled(0);

    ui->StopAllAxis->setEnabled(1);
}

//使界面左边的控件能正常使用使用
void newManualOperation::ControlCanBeUsed()
{
    ui->X_Jog_L->setEnabled(1);
    ui->X_Jog_R->setEnabled(1);
    ui->X_Home->setEnabled(1);
    ui->Y_Jog_L->setEnabled(1);
    ui->Y_Jog_R->setEnabled(1);
    ui->Y_Home->setEnabled(1);
    ui->Z_Jog_L->setEnabled(1);
    ui->Z_Jog_R->setEnabled(1);
    ui->Z_Home->setEnabled(1);

    ui->label_5->setEnabled(1);
    ui->LineEdit_ManualSpeed->setEnabled(1);
    ui->label_6->setEnabled(1);
    ui->CheckBox_Step->setEnabled(1);
    ui->LineEdit_StepDistance->setEnabled(1);
    ui->label_13->setEnabled(1);
    ui->groupBox_5->setEnabled(1);

    ui->StopAllAxis->setEnabled(1);
}

//change event一般是当前widget状态改变后触发的
//如字体改变、语言改变之类的。
//该方法主要捕获改变事件，当语言改变后搜索，执行相关操作。
void newManualOperation::changeEvent(QEvent *e)    //重写的事件处理方法
{
    QDialog::changeEvent(e);    //让基类执行事件处理方法
    switch (e->type())          //根据事件类型判别
    {
    case QEvent::LanguageChange:  //如果是语言改变事件
    {
        QString BtnTXT = ui->Btn_OpenAutoControl->text();
        ui->retranslateUi(this);    //更新UI的语言（看方法字面的，用户自定义方法）
        if(BtnTXT == "开启手动控制" || BtnTXT == "Start MC")
        {
            ui->Btn_OpenAutoControl->setText(QObject::tr("开启手动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Green;");
            ui->label->setText(QObject::tr("当前状态：自动控制"));
            ui->label->setStyleSheet("color:Blue;""font:75 11pt;");
            ControlCannotBeUsed();//使界面左边的控件都不能使用
        }
        else if(BtnTXT == "开启自动控制" || BtnTXT == "Start AC")
        {
            ui->Btn_OpenAutoControl->setText(QObject::tr("开启自动控制"));
            ui->Btn_OpenAutoControl->setStyleSheet("color:Blue;");
            ui->label->setText(QObject::tr("当前状态：手动控制"));
            ui->label->setStyleSheet("color:Green;""font:75 11pt;");
            ControlCanBeUsed();//使界面左边的控件能正常使用使用
        }
    }
        break;
    default:
        break;
    }
}

//功能：获取文件名槽函数
void newManualOperation::GetFileName()
{
    ui->SelectProgram_Controller->clear();
    filelist.clear();

    AMC4030::pComTimerWork->ComThrConPara.GetFileName = 1;

    int filecount = AMC4030::pComTimerWork->ComThrConPara.comFileInfo.file_total;
    qDebug()<<filecount;

    int i = 0;
    for(i = 0;i < filecount;i++)
    {
        if(strncmp(AMC4030::pComTimerWork->ComThrConPara.comFileInfo.filename[i], "__CONFIG", 8))
            filelist<<AMC4030::pComTimerWork->ComThrConPara.comFileInfo.filename[i];
    }

    ui->SelectProgram_Controller->addItems(filelist);

    //记录当前选中的文件名
    AMC4030::currentFilename = ui->SelectProgram_Controller->currentText();

}

//功能：删除卡内程序
void newManualOperation::on_Btn_DeleteProgram_Controller_clicked()
{
    if(ui->SelectProgram_Controller->currentText().isEmpty())
        return;
    memset(AMC4030::pComTimerWork->ComThrConPara.filename, 0, sizeof(AMC4030::pComTimerWork->ComThrConPara.filename));

    //获取文件名
    QString filename = ui->SelectProgram_Controller->currentText();
    int CurrentIndex = ui->SelectProgram_Controller->currentIndex();
    qDebug()<<filename;

    //转换为char字符型
    QByteArray temp = filename.toLatin1();

    int i = temp.size();
    for(i = 0; i < temp.size();i++)
    {
        AMC4030::pComTimerWork->ComThrConPara.filename[i] = temp[i];
    }
    AMC4030::pComTimerWork->ComThrConPara.NameSize = temp.size();

    //移除下拉框中的文件名
    ui->SelectProgram_Controller->removeItem(CurrentIndex);

    qDebug()<<temp.size();
    qDebug()<<AMC4030::pComTimerWork->ComThrConPara.filename;

    AMC4030::pComTimerWork->ComThrConPara.DeleteFile = 1;

    AMC4030::pComTimerWork->ComThrConPara.comFileInfo.file_total--;

}




void newManualOperation::on_Btn_IOStatus_clicked()
{
    if(IO_Dialog == NULL)
    {
        IO_Dialog = new IOStatus;
        IO_Dialog->show();
    }
    else
    {
        IO_Dialog->show();
    }
}

void newManualOperation::deleteIOStatusDialog()
{
    if(IO_Dialog != NULL)
    {
        delete IO_Dialog;
        IO_Dialog = NULL;
        qDebug()<<"删除IO窗口";
    }
}
