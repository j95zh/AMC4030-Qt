 #include "amc4030.h"
#include "ui_amc4030.h"

#include "Commdefine.h"
#include "SystemParam.h"
#include "ComInterface.h"

#include "newparametersetting.h"
#include "newmanualoperation.h"
#include "newprogrameditor.h"
#include "newabout.h"
#include "c_amc4030dll.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QtCore/QCoreApplication>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QComboBox>
#include <QTextCodec>
#include <synchapi.h>

Communication* AMC4030::pComTimerWork;
QThread* AMC4030::pComThread;
int AMC4030::CurrentPage;
QString AMC4030::currentFilename;

AMC4030::AMC4030(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AMC4030)
{
    ui->setupUi(this);

    this->setMaximumSize(870,480); //设置界面大小
    this->setMinimumSize(870,480);

    //判断当前目录是否存在Program文件夹，不存在则创建
    QDir dir;
    QString CurDir=dir.currentPath()+"/Program";
    QDir p_dir;
    if (!p_dir.exists(CurDir))
        p_dir.mkpath(CurDir);


    //根据配置文件选择界面显示的语言，0为中文，1为英文
    ReadUserSettingsCfgFile();

    if(CUR_LANG==0)
        ChooseChineseLanguage();
    else
        ChooseEnglishLanguage();

    ui->scrollArea->resize(730,410);
    ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
    ui->label->setStyleSheet("color:red;");//设置为红色

    ProgramEdite();//软件一运行就显示程序编辑界面

    CurrentPage=3;

    QObject::connect(ui->Btn_ParameterSet,SIGNAL(clicked()),this,SLOT(ParameterSet()));//参数设置的信号槽
    QObject::connect(ui->Btn_ManualOperate,SIGNAL(clicked()),this,SLOT(ManualOperate()));//手动操作的信号槽
    QObject::connect(ui->Btn_ProgramEdite,SIGNAL(clicked()),this,SLOT(ProgramEdite()));//程序编辑的信号槽

    QObject::connect(ui->actionChinese,SIGNAL(triggered()),this,SLOT(ChooseChineseLanguage()));
    QObject::connect(ui->actionEnglish,SIGNAL(triggered()),this,SLOT(ChooseEnglishLanguage()));

    //this->setWindowFlags(Qt::FramelessWindowHint);//没有边框的窗口
    //this->setWindowFlags(Qt::WindowCloseButtonHint); //只要关闭按钮
    //this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::CustomizeWindowHint);//隐藏最小化、最大化、关闭按钮,同时保留标题栏

//    newManualOperation*log=new newManualOperation(this);//在当前界面说实例化子类对象
//    //seek函数在手动操作类里面，而get定义在当前类里面
//    QObject::connect(log,SIGNAL(seek(const QString&)),this,SLOT(get(const QString&)));//连接信号 与 槽函数

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(ReadMachineStatus()));

}

AMC4030::~AMC4030()
{
    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    AMC4030_DLL.Q_StopAll();//当窗口主界面关闭时，执行所有轴停止

    delete ui;
}

//连接控制器
void AMC4030::on_Btn_ConnectController_clicked()
{
    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    if(ui->Btn_ConnectController->text() ==  QObject::tr("连接控制器"))
    {
        QTime timedebuge;//声明一个时钟对象
        timedebuge.start();//开始计时

        AMC4030_DLL.Q_SetComType(2);//设置通讯类型为2
        AMC4030_DLL.Q_OpenLink(5,115200);

        int result_GMS = 10;
        result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
        qDebug()<<"现在的机器状态："<<result_GMS;
        if(result_GMS==1)//表示当前已连接控制器
        {
            AMC4030::pComTimerWork->ComThrConPara.GetFileName = 1;//链接成功后先获取一次文件名
            ui->Btn_ConnectController->setText( QObject::tr("断开控制器"));
            ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:red;"); //设置为红色

            ui->label->setText( QObject::tr("当前状态：已连接控制器！"));
            ui->label->setStyleSheet("color:blue;");//设置为蓝色

            Timer->start(10);//直接在这个地方启动定时器，会占用主界面ui的线程，就会挂起主界面
            //如果在槽函数ReadMachineStatus()中执行的时间过长，导致鼠标拖动界面时出现卡顿，正确做法是使用另一个工作线程来执行定时器
        }
        qDebug()<<"该段程序耗时："<<timedebuge.elapsed()<<"ms";//输出计时
        //当控制卡一重新上电，立即点击“连接控制器”，该用时为4秒钟。这种情况是因为控制卡上电的初始化，没必要优化
    }
    else
    {
        AMC4030_DLL.Q_SetComType(0);///把原本的通讯类型由2改为0，则不能通信
        ui->Btn_ConnectController->setText( QObject::tr("连接控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
        ui->label->setText( QObject::tr("当前状态：未连接控制器！"));
        ui->label->setStyleSheet("color:red;");//设置为红色

        ui->label_2->setText(" ");

        Timer->stop();
        qDebug()<<"已断开控制器"<<endl;
    }
    if(CurrentPage==1){
        if(ui->Btn_ConnectController->text() ==  QObject::tr("连接控制器"))
        {
            pComTimerWork->ComThrConPara.result_GMS=0;
        }
        else
        {
            pComTimerWork = new Communication;
            pComThread = new QThread(this);
            connect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
            connect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
            pComTimerWork->moveToThread(pComThread);
            pComThread->start();
        }
    }
}

void AMC4030::ReadMachineStatus()
{
    //Sleep(50);//作用不大，故注释掉，若不注释，导致timer定时任务执行的时间过长，则会影响整个界面的响应
    int result_GMS = 10;
    result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    //qDebug()<<"现在的机器状态："<<result_GMS;
    if(result_GMS==1)//表示当前已连接控制器
    {
        ui->Btn_ConnectController->setText( QObject::tr("断开控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:red;"); //设置为红色

        ui->label->setText( QObject::tr("当前状态：已连接控制器！"));
        ui->label->setStyleSheet("color:blue;");//设置为蓝色

        int Status = tMachineStatus.dwWorkStatus;
        if(Status & 0x02) //自动控制的状态
        {
            ui->label_2->setText(QObject::tr("机器状态：自动控制"));
            ui->label_2->setStyleSheet("color:Blue;""font:70 11pt;");
        }
        else
        {
            ui->label_2->setText(QObject::tr("机器状态：手动控制"));
            ui->label_2->setStyleSheet("color:Green;""font:70 11pt;");
        }

       // qDebug() << "已连接上控制器"<<endl;
    }
    else
    {
        ui->Btn_ConnectController->setText( QObject::tr("连接控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
        ui->label->setText( QObject::tr("当前状态：未连接控制器！"));
        ui->label->setStyleSheet("color:red;");//设置为红色

        ui->label_2->setText(" ");
       // qDebug() << "未连接上控制器"<<endl;
    }
}

//实现改变连接状态
void AMC4030::get(const QString&txt)
{
    //    if(txt=="未连接")
    //    {
    //        //AMC4030_DLL.Q_SetComType(0);///把原本的通讯类型由2改为0，则不能通信
    //        ui->Btn_ConnectController->setText( QObject::tr("连接控制器"));
    //        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
    //        ui->label->setText( QObject::tr("当前状态：未连接控制器！"));
    //        ui->label->setStyleSheet("color:red;");//设置为红色
    //        qDebug()<<"通过seek信号已断开控制器"<<endl;
    //    }
    //    else if(txt=="已连接")
    //    {
    //        ui->Btn_ConnectController->setText( QObject::tr("断开控制器"));
    //        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:red;"); //设置为红色
    //        ui->label->setText( QObject::tr("当前状态：已连接控制器！"));
    //        ui->label->setStyleSheet("color:blue;");//设置为蓝色
    //        qDebug() << "通过seek信号已连接上控制器"<<endl;
    //    }

    if(txt=="未连接")
    {
        ui->label_2->setText(" ");
    }
    if(txt=="手动控制")
    {
        ui->label_2->setText(QObject::tr("机器状态：手动控制"));
        ui->label_2->setStyleSheet("color:Green;""font:70 11pt;");
    }
    else if(txt=="自动控制")
    {
        ui->label_2->setText(QObject::tr("机器状态：自动控制"));
        ui->label_2->setStyleSheet("color:Blue;""font:70 11pt;");
    }
}

//转到“手动操作”界面
void AMC4030::ManualOperate()
{
    //Timer->stop();
    CurrentPage=1;

    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    ui->Btn_ManualOperate->setStyleSheet("background-color: rgb(84,255,159);");
    ui->Btn_ParameterSet->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_ProgramEdite->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_About->setStyleSheet("background-color: rgb(232,232,232);");

    qDebug()<<"选择手动界面";
    // 另一种方法，但是如果增加的界面没有关闭按钮，则每次点击显示这个界面就会另外占用内存，之前的内存也都无效了
    newManualOperation*dialog_MO=new newManualOperation;
    ui->scrollArea->setWidget(dialog_MO);
    //  dialog_MO.tptest();
    dialog_MO->show();
    //    ui->scrollArea->setWidget(newManualOperation::Instance_MO());
    //    newManualOperation::Instance_MO()->show();
}

//转到“参数设置”界面
void AMC4030::ParameterSet()
{
    CurrentPage=2;
    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    ui->Btn_ManualOperate->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_ParameterSet->setStyleSheet("background-color: rgb(84,255,159);");
    ui->Btn_ProgramEdite->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_About->setStyleSheet("background-color: rgb(232,232,232);");

    qDebug()<<"选择参数界面";

    //    ui->scrollArea->setWidget(newParameterSetting::Instance_PS());
    //    //    dialog->resize(710,400);
    //    //    dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//设置自定义无边框
    //    newParameterSetting::Instance_PS()->show();//在非构造函数不加show()则不显示
    newParameterSetting*dialog_PS=new newParameterSetting;
    ui->scrollArea->setWidget(dialog_PS);
    dialog_PS->show();
}

//转到“程序编辑”界面
void AMC4030::ProgramEdite()
{
    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    ui->Btn_ManualOperate->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_ParameterSet->setStyleSheet("background-color: rgb(232,232,232);");
    ui->Btn_ProgramEdite->setStyleSheet("background-color: rgb(84,255,159);");
    ui->Btn_About->setStyleSheet("background-color: rgb(232,232,232);");

    qDebug()<<"选择程序界面";

    //    ui->scrollArea->setWidget(newProgramEditor::Instance_PE());
    //    newProgramEditor::Instance_PE()->show();
    newProgramEditor*dialog_PE=new newProgramEditor;
    ui->scrollArea->setWidget(dialog_PE);
    dialog_PE->show();
}

//转到“关于”界面
void AMC4030::on_Btn_About_clicked()
{
    pComTimerWork->ComThrConPara.loopNow=0;
    disconnect(pComThread , SIGNAL(started()),pComTimerWork, SLOT(readComDataSlot()));
    disconnect(pComThread , SIGNAL(finished()),pComTimerWork, SLOT(deleteLater()));
    if (pComThread)
    {
        if (pComThread->isRunning())
        {
            pComThread->quit();
            pComThread->wait();
        }
        delete pComThread;
        pComThread = NULL;
    }
    if (pComTimerWork)
    {
        delete pComTimerWork;
        pComTimerWork = NULL;
    }

    newAbout*dialog_About=new newAbout;
    //dialog_About->show();
    dialog_About->exec();
}

void AMC4030::ChooseEnglishLanguage()
{
    CUR_LANG=1;
    WriteUserSettingsCfgFile();

    QTranslator *translator = new QTranslator;
    translator->load("AMC4030_ENGLISH_CN.qm");
    qApp->installTranslator(translator);

    //保存连接控制器状态
    QString BtnTXT=ui->Btn_ConnectController->text();

    ui->retranslateUi(this);
    //连接控制器动态语言切换
    if(BtnTXT=="连接控制器"||BtnTXT=="CNCT CTL")
    {
        ui->Btn_ConnectController->setText( QObject::tr("连接控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
    }
    else if(BtnTXT=="断开控制器"||BtnTXT=="BRK CTL")
    {
        ui->Btn_ConnectController->setText( QObject::tr("断开控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:red;"); //设置为红色
    }

    QFile txt_file("CompanyInformation.txt");
    if (txt_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList textList;   //记录文件中每一行的数据
        QTextStream in(&txt_file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            textList.append(line);          //保存文件的数据
        }
        txt_file.close();       //关闭文件
        QString row2 = textList.at(1);
        QString EnglishTitle = row2.right(row2.length()-13);
        AMC4030::setWindowTitle(EnglishTitle);
    }
}

void AMC4030::ChooseChineseLanguage()
{
    CUR_LANG=0;
    WriteUserSettingsCfgFile();

    QTranslator *translator = new QTranslator;
    translator->load("AMC4030_CHINESE_CN.qm");
    qApp->installTranslator(translator);

    //保存连接控制器状态
    QString BtnTXT=ui->Btn_ConnectController->text();
    QString label_txt=ui->label->text();

    ui->retranslateUi(this);
    //连接控制器动态语言切换
    if(BtnTXT=="连接控制器"||BtnTXT=="CNCT CTL")
    {
        ui->Btn_ConnectController->setText( QObject::tr("连接控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:blue;"); //设置为蓝色
    }
    if(BtnTXT=="断开控制器"||BtnTXT=="BRK CTL")
    {
        ui->Btn_ConnectController->setText( QObject::tr("断开控制器"));
        ui->Btn_ConnectController->setStyleSheet("background-color: rgb(232,232,232);color:red;"); //设置为红色
    }

    //连接状态的动态语言切换
    if(label_txt=="当前状态：已连接控制器！"||label_txt=="Current State:The controller has connected!")
    {
        ui->label->setText(QObject::tr("当前状态：已连接控制器！"));
        ui->label->setStyleSheet("color:blue;");
    }
    if(label_txt=="当前状态：未连接控制器！"||label_txt=="Current State:The controller is not present!")
    {
        ui->label->setText(QObject::tr("当前状态：未连接控制器！"));
        ui->label->setStyleSheet("color:red;");
    }

    QFile txt_file("CompanyInformation.txt");
    if (txt_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList textList;   //记录文件中每一行的数据
        QTextStream in(&txt_file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            textList.append(line);          //保存文件的数据
        }
        txt_file.close();       //关闭文件
        QString row1 = textList.at(0);
        QString ChineseTitle = row1.right(row1.length()-7);
        AMC4030::setWindowTitle(ChineseTitle);
    }
}

void AMC4030::WriteUserSettingsCfgFile()
{
    //Qt中使用QSettings类读写ini文件
    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QSettings *configIniWrite = new QSettings("UserSettings.ini", QSettings::IniFormat);

    //向ini文件的节[LanguageSelect]写入内容,节下的第一个键值是CUR_LANG
    configIniWrite->setValue("/LanguageSelect/CurrentSelect",QString::number(CUR_LANG));
    delete configIniWrite; //写入完成后删除指针
}

void AMC4030::ReadUserSettingsCfgFile()
{
    QSettings *configIniRead = new QSettings("UserSettings.ini", QSettings::IniFormat);
    CUR_LANG = configIniRead->value("/LanguageSelect/CurrentSelect").toInt();
    delete configIniRead;
}

