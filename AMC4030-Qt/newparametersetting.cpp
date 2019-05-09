#include "newparametersetting.h"
#include "ui_newparametersetting.h"

#include "Transfer.h"
#include "ComInterface.h"
#include "SystemParam.h"
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
#include <QListView>
#include <QMouseEvent>

#define ONCE_SEND_DATA		500

newParameterSetting::newParameterSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newParameterSetting)
{
    ui->setupUi(this);

    //设置界面大小
    this->setMaximumSize(710, 400);
    this->setMinimumSize(710, 400);

    //设置XYZ轴的标签
    QFont font ( "Microsoft YaHei", 11, 25); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75,加粗）
    ui->label_X->setFont(font);
    ui->label_Y->setFont(font);
    ui->label_Z->setFont(font);

    //设置下拉选项高度
    ui->ComBox_HomeDirection_X->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}" );
    ui->ComBox_HomeDirection_X->setView(new QListView());
    ui->ComBox_HomeDirection_Y->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}" );
    ui->ComBox_HomeDirection_Y->setView(new QListView());
    ui->ComBox_HomeDirection_Z->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}" );
    ui->ComBox_HomeDirection_Z->setView(new QListView());

    //建立关于计算脉冲当量的信号槽
    connect(ui->LineEdit_PulseFactorDown_X,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));
    connect(ui->LineEdit_PulseFactorUp_X,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));
    connect(ui->LineEdit_PulseFactorDown_Y,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));
    connect(ui->LineEdit_PulseFactorUp_Y,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));
    connect(ui->LineEdit_PulseFactorDown_Z,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));
    connect(ui->LineEdit_PulseFactorUp_Z,SIGNAL(textEdited(QString)),this,SLOT(PulseFactor_SetText()));

    AMC4030_DLL.Q_OpenLink(5, 115200);

    //关于XYZ反向间隙的控件暂不使用，先让其不显示
    ui->LineEdit_BackLashLen_X->setVisible(false);
    ui->CheckBox_BackLash_X->setVisible(false);
    ui->LineEdit_BackLashLen_Y->setVisible(false);
    ui->CheckBox_BackLash_Y->setVisible(false);
    ui->LineEdit_BackLashLen_Z->setVisible(false);
    ui->CheckBox_BackLash_Z->setVisible(false);

    QDir dir;
    CurDir=dir.currentPath()+"/SystemCfg.INI";
    qDebug()<<"当前路径："<<CurDir;

    DisplayContentsAccordingFile();//根据参数文件显示不同的内容。

    qDebug()<<"进入参数界面的构造函数";
}

newParameterSetting::~newParameterSetting()
{
    qDebug()<<"进入参数界面的析构";
    delete ui;
}

//脉冲当量改变
void newParameterSetting::PulseFactor_SetText()
{
    double PulseFactor_X=(ui->LineEdit_PulseFactorDown_X->text().toDouble())/
            (ui->LineEdit_PulseFactorUp_X->text().toDouble());
    ui->LineEdit_PulseFactor_X->setText(QString::number(PulseFactor_X));

    double PulseFactor_Y=(ui->LineEdit_PulseFactorDown_Y->text().toDouble())/
            (ui->LineEdit_PulseFactorUp_Y->text().toDouble());
    ui->LineEdit_PulseFactor_Y->setText(QString::number(PulseFactor_Y));

    double PulseFactor_Z=(ui->LineEdit_PulseFactorDown_Z->text().toDouble())/
            (ui->LineEdit_PulseFactorUp_Z->text().toDouble());
    ui->LineEdit_PulseFactor_Z->setText(QString::number(PulseFactor_Z));
}

//参数加载
void newParameterSetting::on_Btn_ParameterLoade_clicked()
{
    int result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    if(result_GMS == 1) //表示当前已连接控制器
    {
        QByteArray cpath = CurDir.toLocal8Bit();//包含中文路径的字符转换
        char* Path= cpath.data();//string转化为char*
        int result=AMC4030_DLL.Q_UploadSystemCfg(Path);
        if(result != 1)
        {
            qDebug()<<"上传错误，上传返回值："<<result;
            return;
        }
        DisplayContentsAccordingFile();//根据参数文件显示不同的内容。
    }
    else
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("未连接控制器！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
}

//参数保存
void newParameterSetting::on_Btn_ParameterSave_clicked()
{
    int i;

    m_dbPulseFactorDown[0] = ui->LineEdit_PulseFactorDown_X->text().toDouble(); ///每运动距离
    m_dbPulseFactorUp[0] = ui->LineEdit_PulseFactorUp_X->text().toDouble(); ///发脉冲数
    m_fMaxPos[0] = ui->LineEdit_MaxPos_X->text().toFloat(); ///行程
    m_dbHomeOffset[0] = ui->LineEdit_HomeOffset_X->text().toDouble(); ///原点回退距离
    m_dbHomeSpeed[0] = ui->LineEdit_HomeSpeed_X->text().toDouble(); ///回原点速度
    m_dbBackLashLen[0] = ui->LineEdit_BackLashLen_X->text().toDouble(); ///方向间隙

    m_dbPulseFactorDown[1] = ui->LineEdit_PulseFactorDown_Y->text().toDouble(); ///每运动距离
    m_dbPulseFactorUp[1] = ui->LineEdit_PulseFactorUp_Y->text().toDouble(); ///发脉冲数
    m_fMaxPos[1] = ui->LineEdit_MaxPos_Y->text().toFloat(); ///行程
    m_dbHomeOffset[1] = ui->LineEdit_HomeOffset_Y->text().toDouble(); ///原点回退距离
    m_dbHomeSpeed[1] = ui->LineEdit_HomeSpeed_Y->text().toDouble(); ///回原点速度
    m_dbBackLashLen[1] = ui->LineEdit_BackLashLen_Y->text().toDouble(); ///方向间隙

    m_dbPulseFactorDown[2] = ui->LineEdit_PulseFactorDown_Z->text().toDouble(); ///每运动距离
    m_dbPulseFactorUp[2] = ui->LineEdit_PulseFactorUp_Z->text().toDouble(); ///发脉冲数
    m_fMaxPos[2] = ui->LineEdit_MaxPos_Z->text().toFloat(); ///行程
    m_dbHomeOffset[2] = ui->LineEdit_HomeOffset_Z->text().toDouble(); ///原点回退距离
    m_dbHomeSpeed[2] = ui->LineEdit_HomeSpeed_Z->text().toDouble(); ///回原点速度
    m_dbBackLashLen[2] = ui->LineEdit_BackLashLen_Z->text().toDouble(); ///方向间隙

    m_dbSysAccSpeed = ui->LineEdit_SysAccSpeed->text().toDouble(); ///系统加速度

    //更新数据
    for( i = 0; i < 3; i++)
    {
        m_tAxisParam[i].nPulseFactorDown = m_dbPulseFactorDown[i];
        m_tAxisParam[i].nPulseFactorUp = m_dbPulseFactorUp[i];
        m_tAxisParam[i].fMaxPos = m_fMaxPos[i];
        m_tAxisParam[i].fHomePosOffset = m_dbHomeOffset[i];
        m_tAxisParam[i].fHomeSpeed = m_dbHomeSpeed[i];
        m_tAxisParam[i].fBackLashLen = m_dbBackLashLen[i];
        if(0==i)
        {
            //关于回零方向
            m_tAxisParam[i].nHomeDir = ui->ComBox_HomeDirection_X->currentIndex();
            if(m_tAxisParam[i].nHomeDir == 0)
                m_tAxisParam[i].nHomeDir = -1;
            //关于反向间隙
            m_tAxisParam[i].nEnableBackLash = 0;
            if(ui->CheckBox_BackLash_X->isChecked())
                m_tAxisParam[i].nEnableBackLash = 1;
        }
        else if(1==i)
        {
            //关于回零方向
            m_tAxisParam[i].nHomeDir = ui->ComBox_HomeDirection_Y->currentIndex();
            if(m_tAxisParam[i].nHomeDir == 0)
                m_tAxisParam[i].nHomeDir = -1;
            //关于反向间隙
            m_tAxisParam[i].nEnableBackLash = 0;
            if(ui->CheckBox_BackLash_Y->isChecked())
                m_tAxisParam[i].nEnableBackLash = 1;
        }
        else if(2==i)
        {
            //关于回零方向
            m_tAxisParam[i].nHomeDir = ui->ComBox_HomeDirection_Z->currentIndex();
            if(m_tAxisParam[i].nHomeDir == 0)
                m_tAxisParam[i].nHomeDir = -1;
            //关于反向间隙
            m_tAxisParam[i].nEnableBackLash = 0;
            if(ui->CheckBox_BackLash_Z->isChecked())
                m_tAxisParam[i].nEnableBackLash = 1;
        }
    }

    //保存到系统参数缓冲中。
    for( i = 0; i < 3; i++)
    {
        g_tSysParam.tAxisParam[i] = m_tAxisParam[i];
    }
    g_tSysParam.MachineParam.fAccelSpeed = m_dbSysAccSpeed;

    int result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    if(result_GMS == 1) //表示当前已连接控制器
    {
        //写配置文件，保存到硬盘
        WriteSysCfgFile();

        //下载到控制器中
        AMC4030_DLL.Q_OpenLink(5, 115200);

        QByteArray cpath = CurDir.toLocal8Bit();//包含中文路径的字符转换
        char* Path= cpath.data();//string转化为char*
        int result= AMC4030_DLL.Q_DownloadSystemCfg(Path); //下载到卡里面
        if(result == 1)
        {
            QMessageBox mBox(QMessageBox::Information,"",QObject::tr("已成功写入！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
        }
        else
            qDebug()<<"下载错误，下载返回值："<<result;
    }
    else
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("未连接控制器！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
}

//写配置文件
void newParameterSetting::WriteSysCfgFile()
{
    //Qt中使用QSettings类读写ini文件
    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QSettings *configIniWrite = new QSettings("SystemCfg.INI", QSettings::IniFormat);
    //向ini文件中写入内容,setValue函数的两个参数是键值对
    configIniWrite->setValue("/Head/MachineType", 4030);
    configIniWrite->setValue("/Head/Version", 1000); //版本号

    //向ini文件的第二个节[MachineParam]写入内容,节下的第一个键fTimerPeriod的值是g_tSysParam.MachineParam.fTimerPeriod的值
    configIniWrite->setValue("/MachineParam/fTimerPeriod", QString::number(g_tSysParam.MachineParam.fTimerPeriod));
    configIniWrite->setValue("/MachineParam/fWorkPrecision", QString::number(g_tSysParam.MachineParam.fWorkPrecision));
    configIniWrite->setValue("/MachineParam/fArcCheckPrecision", QString::number(g_tSysParam.MachineParam.fArcCheckPrecision));
    configIniWrite->setValue("/MachineParam/fMinLen", QString::number(g_tSysParam.MachineParam.fMinLen));
    configIniWrite->setValue("/MachineParam/fMaxFeedSpeed", QString::number(g_tSysParam.MachineParam.fMaxFeedSpeed));
    configIniWrite->setValue("/MachineParam/nAccelType", QString::number(g_tSysParam.MachineParam.nAccelType));
    configIniWrite->setValue("/MachineParam/nHomePowerOn", QString::number(g_tSysParam.MachineParam.nHomePowerOn));
    configIniWrite->setValue("/MachineParam/fMaxAccelSpeed", QString::number(g_tSysParam.MachineParam.fMaxAccelSpeed));
    configIniWrite->setValue("/MachineParam/fAccelSpeed", QString::number( g_tSysParam.MachineParam.fAccelSpeed));
    configIniWrite->setValue("/MachineParam/fFastAccelSpeed", QString::number(g_tSysParam.MachineParam.fFastAccelSpeed));
    configIniWrite->setValue("/MachineParam/fJAccelSpeed", QString::number(g_tSysParam.MachineParam.fJAccelSpeed));

    configIniWrite->setValue("/XAxisParam/nPulseFactorUp", QString::number(m_tAxisParam[0].nPulseFactorUp));
    configIniWrite->setValue("/XAxisParam/nPulseFactorDown", QString::number(m_tAxisParam[0].nPulseFactorDown));
    configIniWrite->setValue("/XAxisParam/nPulseLogic", QString::number(m_tAxisParam[0].nPulseLogic));
    configIniWrite->setValue("/XAxisParam/fMaxSpeed", QString::number(m_tAxisParam[0].fMaxSpeed));
    configIniWrite->setValue("/XAxisParam/fMaxPos", QString::number(m_tAxisParam[0].fMaxPos));
    configIniWrite->setValue("/XAxisParam/nEnableBackLash", QString::number(m_tAxisParam[0]. nEnableBackLash));
    configIniWrite->setValue("/XAxisParam/fBackLashLen", QString::number(m_tAxisParam[0].fBackLashLen));
    configIniWrite->setValue("/XAxisParam/fBackLashSpeed", QString::number(m_tAxisParam[0].fBackLashSpeed));
    configIniWrite->setValue("/XAxisParam/nHomeDir", QString::number(m_tAxisParam[0].nHomeDir));
    configIniWrite->setValue("/XAxisParam/fHomeSpeed", QString::number(m_tAxisParam[0].fHomeSpeed));
    configIniWrite->setValue("/XAxisParam/fHomeCheckDis", QString::number(m_tAxisParam[0]. fHomeCheckDis));
    configIniWrite->setValue("/XAxisParam/fHomeZeroSpeed", QString::number(m_tAxisParam[0].fHomeZeroSpeed));
    configIniWrite->setValue("/XAxisParam/fHomeOrgSpeed", QString::number(m_tAxisParam[0].fHomeOrgSpeed));
    configIniWrite->setValue("/XAxisParam/fHomePosOffset", QString::number(m_tAxisParam[0].fHomePosOffset));

    configIniWrite->setValue("/YAxisParam/nPulseFactorUp", QString::number(m_tAxisParam[1].nPulseFactorUp));
    configIniWrite->setValue("/YAxisParam/nPulseFactorDown", QString::number(m_tAxisParam[1].nPulseFactorDown));
    configIniWrite->setValue("/YAxisParam/nPulseLogic", QString::number(m_tAxisParam[1].nPulseLogic));
    configIniWrite->setValue("/YAxisParam/fMaxSpeed", QString::number(m_tAxisParam[1].fMaxSpeed));
    configIniWrite->setValue("/YAxisParam/fMaxPos", QString::number(m_tAxisParam[1].fMaxPos));
    configIniWrite->setValue("/YAxisParam/nEnableBackLash", QString::number(m_tAxisParam[1]. nEnableBackLash));
    configIniWrite->setValue("/YAxisParam/fBackLashLen", QString::number(m_tAxisParam[1].fBackLashLen));
    configIniWrite->setValue("/YAxisParam/fBackLashSpeed", QString::number(m_tAxisParam[1].fBackLashSpeed));
    configIniWrite->setValue("/YAxisParam/nHomeDir", QString::number(m_tAxisParam[1].nHomeDir));
    configIniWrite->setValue("/YAxisParam/fHomeSpeed", QString::number(m_tAxisParam[1].fHomeSpeed));
    configIniWrite->setValue("/YAxisParam/fHomeCheckDis", QString::number(m_tAxisParam[1]. fHomeCheckDis));
    configIniWrite->setValue("/YAxisParam/fHomeZeroSpeed", QString::number(m_tAxisParam[1].fHomeZeroSpeed));
    configIniWrite->setValue("/YAxisParam/fHomeOrgSpeed", QString::number(m_tAxisParam[1].fHomeOrgSpeed));
    configIniWrite->setValue("/YAxisParam/fHomePosOffset", QString::number(m_tAxisParam[1].fHomePosOffset));

    configIniWrite->setValue("/ZAxisParam/nPulseFactorUp", QString::number(m_tAxisParam[2].nPulseFactorUp));
    configIniWrite->setValue("/ZAxisParam/nPulseFactorDown", QString::number(m_tAxisParam[2].nPulseFactorDown));
    configIniWrite->setValue("/ZAxisParam/nPulseLogic", QString::number(m_tAxisParam[2].nPulseLogic));
    configIniWrite->setValue("/ZAxisParam/fMaxSpeed", QString::number(m_tAxisParam[2].fMaxSpeed));
    configIniWrite->setValue("/ZAxisParam/fMaxPos", QString::number(m_tAxisParam[2].fMaxPos));
    configIniWrite->setValue("/ZAxisParam/nEnableBackLash", QString::number(m_tAxisParam[2]. nEnableBackLash));
    configIniWrite->setValue("/ZAxisParam/fBackLashLen", QString::number(m_tAxisParam[2].fBackLashLen));
    configIniWrite->setValue("/ZAxisParam/fBackLashSpeed", QString::number(m_tAxisParam[2].fBackLashSpeed));
    configIniWrite->setValue("/ZAxisParam/nHomeDir", QString::number(m_tAxisParam[2].nHomeDir));
    configIniWrite->setValue("/ZAxisParam/fHomeSpeed", QString::number(m_tAxisParam[2].fHomeSpeed));
    configIniWrite->setValue("/ZAxisParam/fHomeCheckDis", QString::number(m_tAxisParam[2]. fHomeCheckDis));
    configIniWrite->setValue("/ZAxisParam/fHomeZeroSpeed", QString::number(m_tAxisParam[2].fHomeZeroSpeed));
    configIniWrite->setValue("/ZAxisParam/fHomeOrgSpeed", QString::number(m_tAxisParam[2].fHomeOrgSpeed));
    configIniWrite->setValue("/ZAxisParam/fHomePosOffset", QString::number(m_tAxisParam[2].fHomePosOffset));

    delete configIniWrite; //写入完成后删除指针
}

//恢复出厂设置
void newParameterSetting::on_Btn_RestoreFactorySettings_clicked()
{
    AMC4030_DLL.Q_OpenLink(5, 115200);
    int result_GMS = 10;
    result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    if(result_GMS == 1) //表示当前已连接控制器
    {
        QFile f;

        QMessageBox megBox(QMessageBox::Question,"",QObject::tr("是否确定恢复出厂设置？"));
        megBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        megBox.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
        int ret= megBox.exec();//用于messagebox显示

        switch(ret)
        {
        case QMessageBox::AcceptRole:
        {
            f.remove("SystemCfg.INI");
            //使下位机也恢复出厂设置
            unsigned char buf[10];
            buf[0] = 0x0B;
            buf[1] = 0x01;
            int result=AMC4030_DLL.Q_SendData(2, buf);

            if(1==result)
            {
                QMessageBox mBox(QMessageBox::Information,"",QObject::tr("已成功恢复出厂设置，请重新启动控制卡和软件！"));
                mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                mBox.exec();
            }
            else
                qDebug()<<"恢复控制卡参数的返回值："<<result;

            break;
        }
        default:
            break;

        }
        return;
    }
    else
    {
        QMessageBox Box(QMessageBox::Warning,"",QObject::tr("未连接控制器！"));
        Box.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        Box.exec();
    }
}

//根据参数文件显示不同的内容。
void newParameterSetting::DisplayContentsAccordingFile()
{
    ReadSysCfgFile();//读文件

    int i;
    for(i = 0; i < 3; i++)
    {
        m_dbPulseFactor[i] = g_tSysParam.tAxisParam[i].nPulseFactorDown / g_tSysParam.tAxisParam[i].nPulseFactorUp;
        m_dbPulseFactorDown[i] = g_tSysParam.tAxisParam[i].nPulseFactorDown;
        m_dbPulseFactorUp[i] = g_tSysParam.tAxisParam[i].nPulseFactorUp;
        m_fMaxPos[i] = g_tSysParam.tAxisParam[i].fMaxPos;
        m_dbHomeSpeed[i] = g_tSysParam.tAxisParam[i].fHomeSpeed;
        m_dbHomeOffset[i] = g_tSysParam.tAxisParam[i].fHomePosOffset;
        m_dbBackLashLen[i] = g_tSysParam.tAxisParam[i].fBackLashLen;
        if(0==i)
        {
            //回零方向。
            if(g_tSysParam.tAxisParam[i].nHomeDir == 1)
                ui->ComBox_HomeDirection_X->setCurrentIndex(1);
            else
                ui->ComBox_HomeDirection_X->setCurrentIndex(0);
            //反向间隙使能。
            ui->CheckBox_BackLash_X->setChecked(0);
            if(g_tSysParam.tAxisParam[i].nEnableBackLash)
                ui->CheckBox_BackLash_X->setChecked(1);
        }
        else if(1==i)
        {
            //回零方向。
            if(g_tSysParam.tAxisParam[i].nHomeDir == 1)
                ui->ComBox_HomeDirection_Y->setCurrentIndex(1);
            else
                ui->ComBox_HomeDirection_Y->setCurrentIndex(0);
            //反向间隙使能。
            ui->CheckBox_BackLash_Y->setChecked(0);
            if(g_tSysParam.tAxisParam[i].nEnableBackLash)
                ui->CheckBox_BackLash_Y->setChecked(1);
        }
        else if(2==i)
        {
            //回零方向。
            if(g_tSysParam.tAxisParam[i].nHomeDir == 1)
                ui->ComBox_HomeDirection_Z->setCurrentIndex(1);
            else
                ui->ComBox_HomeDirection_Z->setCurrentIndex(0);
            //反向间隙使能。
            ui->CheckBox_BackLash_Z->setChecked(0);
            if(g_tSysParam.tAxisParam[i].nEnableBackLash)
                ui->CheckBox_BackLash_Z->setChecked(1);
        }
    }

    m_dbSysAccSpeed = g_tSysParam.MachineParam.fAccelSpeed;
    ui->LineEdit_SysAccSpeed->setText(QString::number(m_dbSysAccSpeed));

    ui->LineEdit_PulseFactor_X->setText(QString::number(m_dbPulseFactor[0]));
    ui->LineEdit_PulseFactorDown_X->setText(QString::number(m_dbPulseFactorDown[0]));
    ui->LineEdit_PulseFactorUp_X->setText(QString::number(m_dbPulseFactorUp[0]));
    ui->LineEdit_MaxPos_X->setText(QString::number(m_fMaxPos[0]));
    ui->LineEdit_HomeOffset_X->setText(QString::number(m_dbHomeOffset[0]));
    ui->LineEdit_HomeSpeed_X->setText(QString::number(m_dbHomeSpeed[0]));
    ui->LineEdit_BackLashLen_X->setText(QString::number(m_dbBackLashLen[0]));

    ui->LineEdit_PulseFactor_Y->setText(QString::number(m_dbPulseFactor[1]));
    ui->LineEdit_PulseFactorDown_Y->setText(QString::number(m_dbPulseFactorDown[1]));
    ui->LineEdit_PulseFactorUp_Y->setText(QString::number(m_dbPulseFactorUp[1]));
    ui->LineEdit_MaxPos_Y->setText(QString::number(m_fMaxPos[1]));
    ui->LineEdit_HomeOffset_Y->setText(QString::number(m_dbHomeOffset[1]));
    ui->LineEdit_HomeSpeed_Y->setText(QString::number(m_dbHomeSpeed[1]));
    ui->LineEdit_BackLashLen_Y->setText(QString::number(m_dbBackLashLen[1]));

    ui->LineEdit_PulseFactor_Z->setText(QString::number(m_dbPulseFactor[2]));
    ui->LineEdit_PulseFactorDown_Z->setText(QString::number(m_dbPulseFactorDown[2]));
    ui->LineEdit_PulseFactorUp_Z->setText(QString::number(m_dbPulseFactorUp[2]));
    ui->LineEdit_MaxPos_Z->setText(QString::number(m_fMaxPos[2]));
    ui->LineEdit_HomeOffset_Z->setText(QString::number(m_dbHomeOffset[2]));
    ui->LineEdit_HomeSpeed_Z->setText(QString::number(m_dbHomeSpeed[2]));
    ui->LineEdit_BackLashLen_Z->setText(QString::number(m_dbBackLashLen[2]));

    OnSetActive();
}

//读配置文件
void newParameterSetting::ReadSysCfgFile()
{
    QFile file("SystemCfg.INI");
    if (file.exists())
    {
        QSettings *configIniRead = new QSettings("SystemCfg.INI", QSettings::IniFormat);

        g_tSysParam.MachineParam.fTimerPeriod = configIniRead->value("/MachineParam/fTimerPeriod").toFloat();
        g_tSysParam.MachineParam.fWorkPrecision = configIniRead->value("/MachineParam/fWorkPrecision").toFloat();
        g_tSysParam.MachineParam.fArcCheckPrecision = configIniRead->value("/MachineParam/fArcCheckPrecision").toFloat();
        g_tSysParam.MachineParam.fMinLen = configIniRead->value("/MachineParam/fMinLen").toFloat();
        g_tSysParam.MachineParam.fMaxFeedSpeed = configIniRead->value("/MachineParam/fMaxFeedSpeed").toFloat();
        g_tSysParam.MachineParam.nAccelType = configIniRead->value("/MachineParam/nAccelType ").toInt();
        g_tSysParam.MachineParam.nHomePowerOn = configIniRead->value("/MachineParam/nHomePowerOn").toInt();
        g_tSysParam.MachineParam.fMaxAccelSpeed = configIniRead->value("/MachineParam/fMaxAccelSpeed").toFloat();
        g_tSysParam.MachineParam.fAccelSpeed = configIniRead->value("/MachineParam/fAccelSpeed").toFloat();/////////
        g_tSysParam.MachineParam.fFastAccelSpeed = configIniRead->value("/MachineParam/fFastAccelSpeed").toFloat();
        g_tSysParam.MachineParam.fJAccelSpeed = configIniRead->value("/MachineParam/fJAccelSpeed").toFloat();

        g_tSysParam.tAxisParam[0].nPulseFactorUp = configIniRead->value("/XAxisParam/nPulseFactorUp").toFloat();/////////
        g_tSysParam.tAxisParam[0].nPulseFactorDown = configIniRead->value("/XAxisParam/nPulseFactorDown").toFloat();/////////
        g_tSysParam.tAxisParam[0].nPulseLogic = configIniRead->value("/XAxisParam/fPulseFactor").toInt();
        g_tSysParam.tAxisParam[0].fMaxSpeed = configIniRead->value("/XAxisParam/fMaxSpeed").toFloat();
        g_tSysParam.tAxisParam[0].fMaxPos = configIniRead->value("/XAxisParam/fMaxPos").toFloat();/////////
        g_tSysParam.tAxisParam[0].nEnableBackLash = configIniRead->value("/XAxisParam/nEnableBackLash").toInt();/////////
        g_tSysParam.tAxisParam[0].fBackLashLen = configIniRead->value("/XAxisParam/fBacklashLen").toFloat();/////////
        g_tSysParam.tAxisParam[0].fBackLashSpeed = configIniRead->value("/XAxisParam/fBackLashSpeed").toFloat();
        g_tSysParam.tAxisParam[0].nHomeDir = configIniRead->value("/XAxisParam/nHomeDir").toInt();/////////
        g_tSysParam.tAxisParam[0].fHomeSpeed = configIniRead->value("/XAxisParam/fHomeSpeed").toFloat();/////////
        g_tSysParam.tAxisParam[0].fHomeCheckDis = configIniRead->value("/XAxisParam/fHomeCheckDis").toFloat();
        g_tSysParam.tAxisParam[0].fHomeZeroSpeed = configIniRead->value("/XAxisParam/fHomeZeroSpeed").toFloat();
        g_tSysParam.tAxisParam[0].fHomeOrgSpeed = configIniRead->value("/XAxisParam/fHomeOrgSpeed").toFloat();
        g_tSysParam.tAxisParam[0].fHomePosOffset = configIniRead->value("/XAxisParam/fHomePosOffset").toFloat();/////////

        g_tSysParam.tAxisParam[1].nPulseFactorUp = configIniRead->value("/YAxisParam/nPulseFactorUp").toFloat();/////////
        g_tSysParam.tAxisParam[1].nPulseFactorDown = configIniRead->value("/YAxisParam/nPulseFactorDown").toFloat();/////////
        g_tSysParam.tAxisParam[1].nPulseLogic = configIniRead->value("/YAxisParam/fPulseFactor").toInt();
        g_tSysParam.tAxisParam[1].fMaxSpeed = configIniRead->value("/YAxisParam/fMaxSpeed").toFloat();
        g_tSysParam.tAxisParam[1].fMaxPos = configIniRead->value("/YAxisParam/fMaxPos").toFloat();/////////
        g_tSysParam.tAxisParam[1].nEnableBackLash = configIniRead->value("/YAxisParam/nEnableBackLash").toInt();/////////
        g_tSysParam.tAxisParam[1].fBackLashLen = configIniRead->value("/YAxisParam/fBacklashLen").toFloat();/////////
        g_tSysParam.tAxisParam[1].fBackLashSpeed = configIniRead->value("/YAxisParam/fBackLashSpeed").toFloat();
        g_tSysParam.tAxisParam[1].nHomeDir = configIniRead->value("/YAxisParam/nHomeDir").toInt();/////////
        g_tSysParam.tAxisParam[1].fHomeSpeed = configIniRead->value("/YAxisParam/fHomeSpeed").toFloat();/////////
        g_tSysParam.tAxisParam[1].fHomeCheckDis = configIniRead->value("/YAxisParam/fHomeCheckDis").toFloat();
        g_tSysParam.tAxisParam[1].fHomeZeroSpeed = configIniRead->value("/YAxisParam/fHomeZeroSpeed").toFloat();
        g_tSysParam.tAxisParam[1].fHomeOrgSpeed = configIniRead->value("/YAxisParam/fHomeOrgSpeed").toFloat();
        g_tSysParam.tAxisParam[1].fHomePosOffset = configIniRead->value("/YAxisParam/fHomePosOffset").toFloat();/////////

        g_tSysParam.tAxisParam[2].nPulseFactorUp = configIniRead->value("/ZAxisParam/nPulseFactorUp").toFloat();/////////
        g_tSysParam.tAxisParam[2].nPulseFactorDown = configIniRead->value("/ZAxisParam/nPulseFactorDown").toFloat();/////////
        g_tSysParam.tAxisParam[2].nPulseLogic = configIniRead->value("/ZAxisParam/fPulseFactor").toInt();
        g_tSysParam.tAxisParam[2].fMaxSpeed = configIniRead->value("/ZAxisParam/fMaxSpeed").toFloat();
        g_tSysParam.tAxisParam[2].fMaxPos = configIniRead->value("/ZAxisParam/fMaxPos").toFloat();/////////
        g_tSysParam.tAxisParam[2].nEnableBackLash = configIniRead->value("/ZAxisParam/nEnableBackLash").toInt();/////////
        g_tSysParam.tAxisParam[2].fBackLashLen = configIniRead->value("/ZAxisParam/fBacklashLen").toFloat();/////////
        g_tSysParam.tAxisParam[2].fBackLashSpeed = configIniRead->value("/ZAxisParam/fBackLashSpeed").toFloat();
        g_tSysParam.tAxisParam[2].nHomeDir = configIniRead->value("/ZAxisParam/nHomeDir").toInt();/////////
        g_tSysParam.tAxisParam[2].fHomeSpeed = configIniRead->value("/ZAxisParam/fHomeSpeed").toFloat();/////////
        g_tSysParam.tAxisParam[2].fHomeCheckDis = configIniRead->value("/ZAxisParam/fHomeCheckDis").toFloat();
        g_tSysParam.tAxisParam[2].fHomeZeroSpeed = configIniRead->value("/ZAxisParam/fHomeZeroSpeed").toFloat();
        g_tSysParam.tAxisParam[2].fHomeOrgSpeed = configIniRead->value("/ZAxisParam/fHomeOrgSpeed").toFloat();
        g_tSysParam.tAxisParam[2].fHomePosOffset = configIniRead->value("/ZAxisParam/fHomePosOffset").toFloat();/////////

        delete configIniRead;
    }
    else
    {
        LoadDefaultSysCfgFile();//加载默认的配置参数
    }
}

//加载默认的配置参数
void newParameterSetting:: LoadDefaultSysCfgFile()
{
    for(int i = 0; i < MAX_AXIS_NUM; i++)
    {
        g_tSysParam.tAxisParam[i].fMaxPos = 200;//最大行程
        g_tSysParam.tAxisParam[i].nPulseFactorDown = 10.0;
        g_tSysParam.tAxisParam[i].nPulseFactorUp = 5000.0;//细分
        g_tSysParam.tAxisParam[i].fHomeSpeed = 20;
        g_tSysParam.tAxisParam[i].nHomeDir = -1;
        g_tSysParam.tAxisParam[i].fHomePosOffset = 5.0;
        g_tSysParam.tAxisParam[i].nEnableBackLash = 0;//不使能
        g_tSysParam.tAxisParam[i].fBackLashLen = 0;

        g_tSysParam.tAxisParam[i].fBackLashSpeed = 10;
        g_tSysParam.tAxisParam[i].nPulseLogic = 1;
        g_tSysParam.tAxisParam[i].fMaxSpeed = 400;
        g_tSysParam.tAxisParam[i].fHomeCheckDis = 50;
        g_tSysParam.tAxisParam[i].fHomeZeroSpeed = 10;
        g_tSysParam.tAxisParam[i].fHomeOrgSpeed = 5;

    }
    g_tSysParam.MachineParam.fTimerPeriod = 1.0;
    g_tSysParam.MachineParam.fWorkPrecision = 0.005;
    g_tSysParam.MachineParam.fArcCheckPrecision = 0.01 ;
    g_tSysParam.MachineParam.fMinLen = 0.02 ;
    g_tSysParam.MachineParam.fMaxFeedSpeed = 400;

    g_tSysParam.MachineParam.nAccelType = 0;
    g_tSysParam.MachineParam.nHomePowerOn = 0;

    g_tSysParam.MachineParam.fMaxAccelSpeed = 20000;
    g_tSysParam.MachineParam.fAccelSpeed = 200;
    g_tSysParam.MachineParam.fFastAccelSpeed = 400;
    g_tSysParam.MachineParam.fJAccelSpeed = 10000 ;
}

//更新数据
void newParameterSetting::OnSetActive()
{
    int i;
    for(i = 0; i < 3; i++)
    {
        m_tAxisParam[i] = g_tSysParam.tAxisParam[i];
    }
}

void newParameterSetting::changeEvent(QEvent *e)    //重写的事件处理方法
{
    QDialog::changeEvent(e);    //让基类执行事件处理方法
    switch (e->type())          //根据事件类型判别
    {
    case QEvent::LanguageChange:  //如果是语言改变事件
        ui->retranslateUi(this);    //更新UI的语言（看方法字面的，用户自定义方法）
        break;
    default:
        break;
    }
}
