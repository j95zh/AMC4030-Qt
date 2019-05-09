#include "newabout.h"
#include "ui_newabout.h"

#include "SystemParam.h"
#include "amc4030.h"
#include "c_amc4030dll.h"

#include <QLibrary>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices> ///用于访问桌面服务的类
#include <QDebug>
#include <QByteArray>
#include <QFileDialog>
#include <QListView>
#include <QSettings>

newAbout::newAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newAbout)
{
    ui->setupUi(this);

    ui->label_Version_2->setText("V 2.0.2.1");
    RefreshVersion();//更新版本号

    //    ui->ComBox_Update->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}" );//下拉选项高度
    //    ui->ComBox_Update->setView(new QListView());
    //    Combox_ListRefresh();//查找有哪些升级文件
    ui->ComBox_Update->setVisible(false);//Combox不可见。。//该功能形式暂时不采用
}

newAbout::~newAbout()
{
    delete ui;
}

//固件升级（把关于升级的二进制文件的数据传输到卡里，使下位机的程序升级）
void newAbout::on_Btn_Update_clicked()
{
    AMC4030_DLL.Q_OpenLink(5,115200);

    int result_GMS = 10;
    result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
    if(result_GMS==1)//表示当前已连接控制器
    {
        AMC4030_DLL.Q_StopAll();//先执行停止所有

        RefreshProgram();//更新程序
    }
    else
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("未连接控制器！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
}

//ComBox_Update的列表刷新
void newAbout::Combox_ListRefresh()
{
    ui->ComBox_Update->clear();
    QString dir = QApplication::applicationDirPath()+"/Update";
    //获取exe文件下的所有文件
    QFileInfoList InfoList = QDir(dir).entryInfoList();
    QStringList qssName;
    //遍历
    foreach(QFileInfo fileInfo,InfoList)
    {
        if(!fileInfo.isFile())
            continue;//不是文件则继续，只用于加速
        else if(fileInfo.suffix()=="bin")
        {
            //去掉文件的后缀名“.bin”
            QString string = fileInfo.fileName().left(fileInfo.fileName().length()-4);
            qssName<<string;
        }
    }
    if(!qssName.isEmpty())
        ui->ComBox_Update->addItems(qssName);
    else
    {
        ui->ComBox_Update->addItem(QObject::tr("目录下没有升级文件！"));
        ui->Btn_Update->setEnabled(0);
    }
}

//更新程序
void newAbout::RefreshProgram()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath());
    qDebug()<<"选中的文件路径"<<filename;

    if(filename!="")
    {
        //包含中文路径的字符转换
        QByteArray cpath = filename.toLocal8Bit();
        char* Path= cpath.data();
        qDebug()<<"升级的路径"<<Path;

        int result_DowloadFile = AMC4030_DLL.Q_DownloadFile(Path,3,1);
        qDebug()<<"升级时的返回值："<<result_DowloadFile;
        if(result_DowloadFile==1)
        {
            QMessageBox mBox(QMessageBox::Information,"",QObject::tr("固件升级成功！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
            RefreshVersion();//更新版本号
        }
        else
        {
            QMessageBox mBox(QMessageBox::Information,"",QObject::tr("固件升级失败！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
        }
    }
    //    QString dir = QApplication::applicationDirPath()+"/Update";
    //    QString FileName= (dir + "/" + ui->ComBox_Update->currentText() +".bin");

    //    //                    //QString转化为string类型，然后由string转化为const char*，最后const char*转化char*
    //    //                    std::string F_N = FileName.toStdString();//QString转化为string类型
    //    //                    const char*PATH;
    //    //                    PATH = F_N.c_str();//string转化为const char*
    //    //                    char* Path =const_cast<char*>(PATH);//const char*转化char*

    //    //包含中文路径的字符转换
    //    QByteArray cpath = FileName.toLocal8Bit();
    //    char* Path= cpath.data();
    //    qDebug()<<"升级的路径"<<Path;

    //    int result_DowloadFile = AMC4030_DLL.Q_DownloadFile(Path,3,1);
    //    qDebug()<<"升级时的返回值："<<result_DowloadFile;
    //    if(result_DowloadFile==1)
    //    {
    //        QMessageBox::information(this,"", QObject::tr("固件升级成功！"));
    //        RefreshVersion();//更新版本号
    //    }
    //    else
    //        QMessageBox::warning(this,"", QObject::tr("固件升级失败！"));
}

//更新版本号
void newAbout::RefreshVersion()
{
    AMC4030_DLL.Q_OpenLink(5,115200);
    AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);

    int result=tMachineStatus.FirmVer;//int为十进制,4530
    QString key =  QString("%1").arg(result,4,16,QLatin1Char('0'));//十进制转成16进制,2002

    //截取字符串，mid()函数接受两个参数，第一个是起始位置，第二个是取串的长度。如果省略第二个参数，则会从起始位置截取到末尾
    QString key_1 = key.mid(0,1);
    QString key_2 = key.mid(1,1);
    QString key_3 = key.mid(2,1);
    QString key_4 = key.mid(3);

    ui->label_Version->setText("V "+key_1+"."+key_2+"."+key_3+"."+key_4);
}

//打开公司官网
void newAbout::on_Btn_AboutFuyu_clicked()
{
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
        QString row3 = textList.at(2);
        QString OfficialWeb = row3.right(row3.length()-8);
        QDesktopServices::openUrl(QUrl(OfficialWeb));//打开网站
    }
    else
    {
        QString OfficialWeb="http://www.fuyuautomation.com/";
        QDesktopServices::openUrl(QUrl(OfficialWeb));//打开网站
    }
}

void newAbout::changeEvent(QEvent *e)    //重写的事件处理方法
{
    QDialog::changeEvent(e);    //让基类执行事件处理方法
    switch (e->type()) {        //根据事件类型判别
    case QEvent::LanguageChange:  //如果是语言改变事件
        ui->retranslateUi(this);    //更新UI的语言（看方法字面的，用户自定义方法）
        break;
    default:
        break;
    }
}
