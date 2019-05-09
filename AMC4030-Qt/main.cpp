#include "amc4030.h"
#include <QApplication>

#include <QSplashScreen>
#include <QElapsedTimer>
#include <QSettings>
#include <QFile>
#include <QTextCodec>

void WriteUserSettingsCfgFile();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WriteUserSettingsCfgFile();

    //QString currentDir=QApplication::applicationDirPath()+"/Pictures/";//获取应用程序所在的文件夹的路径
    //a.setWindowIcon(QIcon(currentDir+"HeadLogo.png"));

    //Splash的原理大概是在你的主窗口运行之前再创建一个新窗口，这个新窗口显示想要显示的图片，
    //在新窗口上设一个定时器，时间到了就自动销毁。
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("StartLogo.png"));//设置图片
    splash->setDisabled(true); //禁用用户的输入事件响应

    //    //在显示的图片上加额外的显示信息
    //    Qt::Alignment top = Qt::AlignBottom | Qt::AlignCenter;
    //    splash->showMessage(QObject::tr("Loading ..."),top, Qt::green); //显示信息

    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QSettings *configIniRead = new QSettings("UserSettings.ini", QSettings::IniFormat);
    int ShowTime=configIniRead->value("/Showtime/PngTime").toInt();

    if(ShowTime!=0)
        splash->show();//显示图片

    //定义启动画面的存在时间
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<ShowTime)
    {
        QCoreApplication::processEvents();
    }
    AMC4030 w;
    w.show();

    splash->finish(&w);//图片一直显示到mainWin加载完成
    delete splash;//释放空间，节省内存

    int CUR_LANG_Select=configIniRead->value("/LanguageSelect/CurrentSelect").toInt();
    delete configIniRead;

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
        QString row3 = textList.at(2);
        QString ChineseTitle = row1.right(row1.length()-7);
        QString EnglishTitle = row3.right(row3.length()-7);
        if(CUR_LANG_Select==0)
            w.setWindowTitle(ChineseTitle);
        if(CUR_LANG_Select==1)
            w.setWindowTitle(EnglishTitle);
    }
    return a.exec();
}

void WriteUserSettingsCfgFile()
{
    QFile file("UserSettings.ini");
    if (!file.exists())
    {
        //Qt中使用QSettings类读写ini文件
        //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QSettings *configIniWrite = new QSettings("UserSettings.ini", QSettings::IniFormat);

        //向ini文件中写入内容,setValue函数的两个参数是键值对
        //向ini文件的第一个节[Head]写入内容,节下的第一个键值是
        configIniWrite->setValue("/Head/MachineType",4030);
        configIniWrite->setValue("/Head/Version",1000);

        configIniWrite->setValue("/LanguageSelect/CurrentSelect",0);

        configIniWrite->setValue("/ProgramSelect/CurrentProgram",0);

        configIniWrite->setValue("/Showtime/PngTime",1200);

        configIniWrite->setValue("/DMProgram/DMsign",0);

        delete configIniWrite; //写入完成后删除指针
    }

    QFile file1("CompanyInformation.txt");
    if (!file1.exists())
    {
        //以只写并且覆盖已有内容的形式操作文件，因为QIODevice::Truncate会直接将文件内容清空
        bool ret = file1.open( QIODevice::Truncate | QIODevice::WriteOnly);
        if(!ret)
            return;
        QTextStream stream(&file1);
        stream.setCodec("GBK");

        QString ChineseTitle="窗口中文标题：成都福誉科技有限公司  AMC4030 - 3轴运动控制器编程软件";
        QString EnglishTitle="EnglishTitle:Chengdu Fuyu Technology Co.,Ltd.  AMC4030 -  Motion Controller Programming Software For 3 Axis";
        QString OfficialWeb="Website:http://www.fuyuautomation.com/";
        stream << ChineseTitle+"\r\n"+EnglishTitle+"\r\n"+OfficialWeb;
        file1.close();
    }
}
