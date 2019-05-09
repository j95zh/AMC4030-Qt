#include "newprogrameditor.h"
#include "ui_newprogrameditor.h"

#include "amc4030.h"
#include "newsavefile.h"
#include "MC_CmdInterface.h"
#include "CmdFile.h"
#include "newbuildfile.h"
#include "c_amc4030dll.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QtCore/QCoreApplication>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QComboBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QListView>
#include <QScrollBar>
#include <QMouseEvent>
#include <QByteArray>

//newProgramEditor *newProgramEditor::_instance_PE = 0;

newProgramEditor::newProgramEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProgramEditor)
{
    ui->setupUi(this);

    (ui->tableWidget->viewport())->installEventFilter(this);    //插入事件过滤器

    ui->ComBox_SelectProgram->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}" );//下拉选项高度
    ui->ComBox_SelectProgram->setView(new QListView());

    //设置界面大小
    this->setMaximumSize(710,408);
    this->setMinimumSize(710,408);

    AMC4030_DLL.Q_OpenLink(5,115200);

    ui->Combox->addItem("ZhangJi");
    ui->Combox->setStyleSheet("QComboBox QAbstractItemView::item{height:30px;}" );//下拉选项高度
    ui->Combox->setView(new QListView());
    ui->Combox->setVisible(false);//Combox不可见

    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QSettings *configIniRead = new QSettings("UserSettings.ini", QSettings::IniFormat);
    DMSign=configIniRead->value("/DMProgram/DMsign").toInt();

    QDir dir;
    currentDir=dir.currentPath()+"/Program";//获取工程所在的文件夹的路径+tr("/Program")

    for(int i=0;i<TotalProgram;i++)
        InitialProgram[i]=0;////用于记录program文件夹里是否存在对应的TotalProgram个默认txt文件,初始化为0 不存在

    ListRefresh();//ComBox_SelectProgram里的列表加载
    ListRefresh();//列表再刷新一次，避免重新生成默认程序后，列表不显示

    ui->tableWidget->resize(600,415);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    //ui->tableWidget->setFocusPolicy(Qt::NoFocus);//让tableWidget失去焦点，点击删除选中行按钮时，如果不选中行的话是不能删除的
    // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    // ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);   //双击可以修改内容
    ui->tableWidget->setMouseTracking(true);    //开启捕获鼠标功能
    ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    //ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->setStyleSheet("selection-background-color:Red");  //设置选中行颜色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    //设置每列宽
    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//设置列宽不能拖动
    QStringList qsl;
    qsl<<tr("指令集")<<tr("指令")<<tr("参数 1")<<tr("参数 2")<<tr("参数 3")<<tr("备注信息");
    ui->tableWidget->setHorizontalHeaderLabels(qsl);
    ISTR_Sets_RowColor();//设置不同指令集所在行的颜色

    /*
    //表格第一二列不能编辑
    for(int i = 0; i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->item(i, 0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i, 1)->setFlags(Qt::NoItemFlags);
    }
    */
    //ui->tableWidget->cellWidget(row,column)->setContextMenuPolicy(Qt::NoContextMenu);//屏蔽表格中(row,column)的右键菜单
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *scrolbar =ui->tableWidget->verticalScrollBar();
    ui->tableWidget->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);//屏蔽滚动条右键菜单

    QObject::connect((QWidget*)scrolbar, SIGNAL(valueChanged(int)),this, SLOT(onMyScrollClicked()));
    QObject::connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
}
newProgramEditor::~newProgramEditor()
{
    delete ui;
}

//表格的竖直滚动条事件
void newProgramEditor::onMyScrollClicked()
{
    ui->Combox->setVisible(false);//Combox不可见
    qDebug()<<"表格有垂直滚动条，且已滚动";
}

//单击表格（row，column）使能
void newProgramEditor::on_tableWidget_cellClicked(int row, int column)
{
    int ROW = ui->tableWidget->rowCount(); //获取表格总行数
    //    int COLUMN=ui->tableWidget->columnCount();//获取表格总列数
    //    qDebug()<<"表格共"<<ROW<<"行"<<COLUMN<<"列";

    //    QRect widgetRect0 = ui->Combox->geometry();
    //    int a0=widgetRect0.width();
    //    int b0=widgetRect0.height();
    //    qDebug()<<"初始的Combox"<<widgetRect0<<"长"<<a0<<"宽"<<b0;//坐标(490,360)，长101，宽31

    QRect widgetRect = ui->Combox->geometry();
    if(ui->tableWidget->item( row,column)!=NULL) //判断指向该cell的指针不为空
    {
        row = ui->tableWidget->currentRow();;//获取选中的行
        column= ui->tableWidget->currentColumn();//获取选中的列
        QString name= ui->tableWidget->item(row,column)->text();//取出字符串
        qDebug()<<"选中"<<row+1<<"行"<<column+1<<"列的"<<name<<endl;
        last_name=name;

        QStringList qssName;
        if(column==0)
        {
            if(name== QObject::tr("系统操作"))
            {
                ui->Combox->clear();
                //                qssName<<QObject::tr("系统操作")<<QObject::tr("流程控制")<<QObject::tr("输出口操作")
                //                      <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("独立插补运动");
                if(DMSign==1)//要修改配置文件才能使用DM功能
                    qssName<<QObject::tr("系统操作")<<QObject::tr("流程控制")<<QObject::tr("输出口操作")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("DM寄存器");
                else//一般用户不提供DM寄存器功能
                    qssName<<QObject::tr("系统操作")<<QObject::tr("流程控制")<<QObject::tr("输出口操作")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(name== QObject::tr( "流程控制") )
            {
                ui->Combox->clear();
                if(DMSign==1)
                    qssName<<QObject::tr("流程控制")<<QObject::tr("系统操作")<<QObject::tr("输出口操作")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("DM寄存器");
                else
                    qssName<<QObject::tr("流程控制")<<QObject::tr("系统操作")<<QObject::tr("输出口操作")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(name== QObject::tr( "输出口操作") )
            {
                ui->Combox->clear();
                if(DMSign==1)
                    qssName<<QObject::tr("输出口操作")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("DM寄存器");
                else
                    qssName<<QObject::tr("输出口操作")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("回零运动")<<QObject::tr("直线点位运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(name== QObject::tr( "回零运动") )
            {
                ui->Combox->clear();
                if(DMSign==1)
                    qssName<<QObject::tr("回零运动")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("输出口操作")<<QObject::tr("直线点位运动")<<QObject::tr("DM寄存器");
                else
                    qssName<<QObject::tr("回零运动")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("输出口操作")<<QObject::tr("直线点位运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(name== QObject::tr( "直线点位运动") )
            {
                ui->Combox->clear();
                if(DMSign==1)
                    qssName<<QObject::tr("直线点位运动")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("输出口操作")<<QObject::tr("回零运动")<<QObject::tr("DM寄存器");
                else
                    qssName<<QObject::tr("直线点位运动")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                          <<QObject::tr("输出口操作")<<QObject::tr("回零运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            //            else if(name==QObject::tr("独立插补运动"))
            //            {
            //                ui->Combox->clear();
            //                qssName<<QObject::tr("独立插补运动")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
            //                      <<QObject::tr("输出口操作")<<QObject::tr("回零运动")<<QObject::tr("直线点位运动");
            //                ui->Combox->addItems(qssName);

            //                if(ROW<10)
            //                    widgetRect.setX(15);
            //                else if(ROW>=10)
            //                    widgetRect.setX(22);
            //                int Row_First=ui->tableWidget->verticalScrollBar()->value();
            //                widgetRect.setY((row-Row_First)*30+25);
            //                widgetRect.setWidth(110);
            //                widgetRect.setHeight(30);
            //                ui->Combox->setGeometry(widgetRect);
            //                ui->Combox->setVisible(true);//Combox可见

            //                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            //            }
            else if(name== QObject::tr( "DM寄存器") )
            {
                ui->Combox->clear();
                qssName<<QObject::tr("DM寄存器")<<QObject::tr("系统操作")<<QObject::tr("流程控制")
                      <<QObject::tr("输出口操作")<<QObject::tr("回零运动")<<QObject::tr("直线点位运动");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(name=="")
            {
                ui->tableWidget->setItem( row,column,new QTableWidgetItem( QObject::tr("系统操作")));
                ui->tableWidget->setItem( row,column+1,new QTableWidgetItem( QObject::tr("停止")));
                ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);//当前单元格内容居中
                ui->tableWidget->item(row,column+1)->setTextAlignment(Qt::AlignCenter);//当前单元格的后一列内容居中

                ui->Combox->clear();
                //                qssName<<QObject::tr("系统操作")<<QObject::tr("流程控制")<<QObject::tr("输出口操作")
                //                      <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("独立插补运动");
                qssName<<QObject::tr("系统操作")<<QObject::tr("流程控制")<<QObject::tr("输出口操作")
                      <<QObject::tr("回零运动")<<QObject::tr("直线点位运动")<<QObject::tr("DM寄存器");
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(15);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(22);
                else
                    widgetRect.setX(29);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(110);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
        }
        else if(column==1)
        {
            QString NAME= ui->tableWidget->item(row,column-1)->text();//取出前一列的字符串

            if(NAME== QObject::tr("系统操作"))
            {
                if(name==QObject::tr("停止"))
                     qssName<<QObject::tr("停止")<<QObject::tr("延时等待")<<QObject::tr("常等待")<<QObject::tr("暂停")<<QObject::tr("恢复");
                //                else if(name==QObject::tr("启动"))
                //                    qssName<<QObject::tr("启动")<<QObject::tr("停止")
                //                          <<QObject::tr("延时等待")<<QObject::tr("等待电机完成")<<QObject::tr("停止电机运动")
                //                         <<QObject::tr("常等待");
                //                else if(name==QObject::tr("暂停"))
                //                    qssName<<QObject::tr("暂停")<<QObject::tr("停止")<<QObject::tr("启动")<<QObject::tr("恢复")
                //                          <<QObject::tr("延时等待")<<QObject::tr("等待电机完成")<<QObject::tr("停止电机运动")
                //                         <<QObject::tr("常等待");
                //                else if(name==QObject::tr("恢复"))
                //                    qssName<<QObject::tr("恢复")<<QObject::tr("停止")<<QObject::tr("启动")<<QObject::tr("暂停")
                //                          <<QObject::tr("延时等待")<<QObject::tr("等待电机完成")<<QObject::tr("停止电机运动")
                //                         <<QObject::tr("常等待");
                else if(name==QObject::tr("延时等待"))
                    qssName<<QObject::tr("延时等待")<<QObject::tr("停止")<<QObject::tr("常等待")<<QObject::tr("暂停")<<QObject::tr("恢复");
                //                else if(name==QObject::tr("等待电机完成"))
                //                    qssName<<QObject::tr("等待电机完成")<<QObject::tr("停止")<<QObject::tr("延时等待")
                //                          <<QObject::tr("停止电机运动")<<QObject::tr("常等待");
                //                else if(name==QObject::tr("停止电机运动"))
                //                    qssName<<QObject::tr("停止电机运动")<<QObject::tr("停止")
                //                          <<QObject::tr("延时等待")<<QObject::tr("等待电机完成")<<QObject::tr("常等待");
                else if(name==QObject::tr("常等待"))
                    qssName<<QObject::tr("常等待")<<QObject::tr("暂停")<<QObject::tr("恢复")<<QObject::tr("停止")<<QObject::tr("延时等待");
                else if(name==QObject::tr("暂停"))
                    qssName<<QObject::tr("暂停")<<QObject::tr("恢复")<<QObject::tr("停止")<<QObject::tr("延时等待")<<QObject::tr("常等待");
                else if(name==QObject::tr("恢复"))
                    qssName<<QObject::tr("恢复")<<QObject::tr("停止")<<QObject::tr("延时等待")<<QObject::tr("常等待")<<QObject::tr("暂停");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(NAME== QObject::tr("流程控制"))
            {
                if(name==QObject::tr("程序行间跳转"))
                    qssName<<QObject::tr("程序行间跳转")<<QObject::tr("程序循环")<<QObject::tr("单次检测跳转")
                          <<QObject::tr("持续检测跳转")<<QObject::tr("关闭持续检测");
                else if(name==QObject::tr("程序循环"))
                    qssName<<QObject::tr("程序循环")<<QObject::tr("程序行间跳转")<<QObject::tr("单次检测跳转")
                          <<QObject::tr("持续检测跳转")<<QObject::tr("关闭持续检测");
                else if(name==QObject::tr("单次检测跳转"))
                    qssName<<QObject::tr("单次检测跳转")<<QObject::tr("程序行间跳转")<<QObject::tr("程序循环")
                          <<QObject::tr("持续检测跳转")<<QObject::tr("关闭持续检测");
                else if(name==QObject::tr("持续检测跳转"))
                    qssName<<QObject::tr("持续检测跳转")<<QObject::tr("程序行间跳转")<<QObject::tr("程序循环")
                          <<QObject::tr("单次检测跳转")<<QObject::tr("关闭持续检测");
                else if(name==QObject::tr("关闭持续检测"))
                    qssName<<QObject::tr("关闭持续检测")<<QObject::tr("程序行间跳转")<<QObject::tr("程序循环")
                          <<QObject::tr("单次检测跳转")<<QObject::tr("持续检测跳转");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(NAME== QObject::tr("输出口操作"))
            {
                if(name==QObject::tr("输出口设置"))
                    qssName<<QObject::tr("输出口设置");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(NAME== QObject::tr("回零运动"))
            {
                //                if(name==QObject::tr("设置回零速度"))
                //                    qssName<<QObject::tr("设置回零速度")<<QObject::tr("启动回零");
                //                else if(name==QObject::tr("启动回零"))
                //                    qssName<<QObject::tr("启动回零")<<QObject::tr("设置回零速度");
                if(name==QObject::tr("设置回零速度"))
                    qssName<<QObject::tr("设置回零速度");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(NAME== QObject::tr("直线点位运动"))
            {
                //                if(name==QObject::tr("设置点位速度"))
                //                    qssName<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("XZ绝对运动")<<QObject::tr("YZ绝对运动") <<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("三轴相对运动"))
                //                    qssName<<QObject::tr("三轴相对运动")<<QObject::tr("设置点位速度")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("XZ绝对运动")<<QObject::tr("YZ绝对运动") <<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("单轴绝对运动"))
                //                    qssName<<QObject::tr("单轴绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("XZ绝对运动")<<QObject::tr("YZ绝对运动") <<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("XY绝对运动"))
                //                    qssName<<QObject::tr("XY绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XZ绝对运动")<<QObject::tr("YZ绝对运动") <<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("XZ绝对运动"))
                //                    qssName<<QObject::tr("XZ绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("YZ绝对运动") <<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("YZ绝对运动"))
                //                    qssName<<QObject::tr("YZ绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("XZ绝对运动")<<QObject::tr("三轴绝对运动");
                //                else if(name==QObject::tr("三轴绝对运动"))
                //                    qssName<<QObject::tr("三轴绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("单轴绝对运动")
                //                          <<QObject::tr("XY绝对运动")<<QObject::tr("XZ绝对运动")<<QObject::tr("YZ绝对运动");

                if(name==QObject::tr("设置点位速度"))
                    qssName<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动")<<QObject::tr("三轴绝对运动");
                else if(name==QObject::tr("三轴相对运动"))
                    qssName<<QObject::tr("三轴相对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴绝对运动");
                else if(name==QObject::tr("三轴绝对运动"))
                    qssName<<QObject::tr("三轴绝对运动")<<QObject::tr("设置点位速度")<<QObject::tr("三轴相对运动");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            //            else if(NAME== QObject::tr("独立插补运动"))
            //            {
            //                if(name==QObject::tr("设置独立运动速度"))
            //                    qssName<<QObject::tr("设置独立运动速度")<<QObject::tr("三轴独立相对插补");
            //                else if(name==QObject::tr("三轴独立相对插补"))
            //                    qssName<<QObject::tr("三轴独立相对插补")<<QObject::tr("设置独立运动速度");

            //                ui->Combox->clear();
            //                ui->Combox->addItems(qssName);

            //                if(ROW<10)
            //                    widgetRect.setX(125);
            //                else if(ROW>=10)
            //                    widgetRect.setX(132);
            //                int Row_First=ui->tableWidget->verticalScrollBar()->value();
            //                widgetRect.setY((row-Row_First)*30+25);
            //                widgetRect.setWidth(130);
            //                widgetRect.setHeight(30);
            //                ui->Combox->setGeometry(widgetRect);
            //                ui->Combox->setVisible(true);//Combox可见

            //                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            //            }
            else if(NAME== QObject::tr("DM寄存器"))
            {
                if(name==QObject::tr("DM赋值"))
                    qssName<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")<<QObject::tr("DM作延时")
                          <<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM加常数"))
                    qssName<<QObject::tr("DM加常数")<<QObject::tr("DM赋值")<<QObject::tr("DM加DM")<<QObject::tr("DM作延时")
                          <<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM加DM"))
                    qssName<<QObject::tr("DM加DM")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM作延时")
                          <<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作延时"))
                    qssName<<QObject::tr("DM作延时")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作程序循环"))
                    qssName<<QObject::tr("DM作程序循环")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作延时")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作回零"))
                    qssName<<QObject::tr("DM作回零")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作延时")<<QObject::tr("DM作程序循环")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作点位速度"))
                    qssName<<QObject::tr("DM作点位速度")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作延时")<<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")
                         <<QObject::tr("DM作相对运动")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作相对运动"))
                    qssName<<QObject::tr("DM作相对运动")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作延时")<<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")
                         <<QObject::tr("DM作点位速度")<<QObject::tr("DM作绝对运动");
                else if(name==QObject::tr("DM作绝对运动"))
                    qssName<<QObject::tr("DM作绝对运动")<<QObject::tr("DM赋值")<<QObject::tr("DM加常数")<<QObject::tr("DM加DM")
                          <<QObject::tr("DM作延时")<<QObject::tr("DM作程序循环")<<QObject::tr("DM作回零")<<QObject::tr("DM作点位速度")
                         <<QObject::tr("DM作相对运动");

                ui->Combox->clear();
                ui->Combox->addItems(qssName);

                if(ROW<10)
                    widgetRect.setX(125);
                else if((ROW>=10)&&(ROW<100))
                    widgetRect.setX(132);
                else
                    widgetRect.setX(139);
                int Row_First=ui->tableWidget->verticalScrollBar()->value();
                widgetRect.setY((row-Row_First)*30+25);
                widgetRect.setWidth(130);
                widgetRect.setHeight(30);
                ui->Combox->setGeometry(widgetRect);
                ui->Combox->setVisible(true);//Combox可见

                //connect(ui->Combox, SIGNAL(currentIndexChanged(int)), this, SLOT(ModifyOption()));
            }
            else if(NAME=="")
            {
                QMessageBox mBox(QMessageBox::Information,"",QObject::tr("请先选择第一列的指令集！"));
                mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                mBox.exec();
            }
        }
        else
        {
            //ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);//选中的内容居中
            ComboxToInitialPos();//combox 移动到初始位置
        }
        ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
        CenterContent();//表格内容居中
    }
}

void newProgramEditor:: ModifyOption()
{
    int row = ui->tableWidget->currentRow();;//获取选中的行
    int column= ui->tableWidget->currentColumn();//获取选中的列
    QString string=ui->Combox->currentText();

    ComboxToInitialPos();//combox 移动到初始位置

    if(column==1)
    {
        ui->tableWidget->setItem(row,column,new QTableWidgetItem(string));
        ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);//选中的内容居中
    }

    else if(column==0)
    {
        ui->tableWidget->setItem(row,column,new QTableWidgetItem(string));
        QString name= ui->tableWidget->item(row,column+1)->text();//取出后一列的字符串

        if(last_name!=string)
        {
            QString STRING;
            if(string== QObject::tr("系统操作"))
                STRING= QObject::tr("停止");
            else if(string== QObject::tr("流程控制"))
                STRING= QObject::tr("程序行间跳转");
            else if(string== QObject::tr("输出口操作"))
                STRING= QObject::tr("输出口设置");
            else if(string== QObject::tr("回零运动"))
                STRING= QObject::tr("设置回零速度");
            else if(string== QObject::tr("直线点位运动"))
                STRING= QObject::tr("设置点位速度");
            else if(string== QObject::tr("独立插补运动"))
                STRING= QObject::tr("设置独立运动速度");
            else if(string== QObject::tr("DM寄存器"))
                STRING= QObject::tr("DM赋值");
            else
                STRING=name;
            ui->tableWidget->setItem(row,column+1,new QTableWidgetItem(STRING));
            ui->tableWidget->item(row,column+1)->setTextAlignment(Qt::AlignCenter);//选中的后一格的内容居中
        }

        ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);//选中的内容居中
        ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
    }
}

//Combox移动到界面上的初始位置
void newProgramEditor::ComboxToInitialPos()
{
    QRect widgetRect = ui->Combox->geometry();
    widgetRect.setX(490);
    widgetRect.setY(360);
    widgetRect.setWidth(101);
    widgetRect.setHeight(31);
    ui->Combox->setGeometry(widgetRect);
    ui->Combox->setVisible(false);//Combox不可见
}

//下载程序，把当前程序写成二进制文件并写入卡内
void newProgramEditor::on_Btn_DownLoad_clicked()
{
    if(ui->ComBox_SelectProgram->currentText()!="")
    {
        QString program=ui->ComBox_SelectProgram->itemText(ui->ComBox_SelectProgram->currentIndex());
        QString FileName_elo= (currentDir +"/"+program+".elo");
        QString FileName_txt= (currentDir +"/"+program+".txt");

        char* ch;
        QByteArray ba = program.toLatin1();
        ch = ba.data();
        int ans;

        WriteInTXT(FileName_txt);//更新程序的txt文件

        WriteBinaryFile();//写二进制文件到硬盘里

        AMC4030_DLL.Q_OpenLink(5,115200);
        int result_GMS = 10;
        result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&tMachineStatus);
        if(result_GMS==1)
        {
            /*2019年3月 8日增加，下载文件前先判断卡内文件个数，若超过11个则提示无法下载*/
            if(AMC4030::pComTimerWork->ComThrConPara.comFileInfo.file_total >= 11)
            {
                for(int i = 0;i < 11;i++)
                {
                    if(!strcmp(AMC4030::pComTimerWork->ComThrConPara.comFileInfo.filename[i], ch))
                    {
                        QMessageBox Message(QMessageBox::Question, "", "控制卡内存在同名文件，是否覆盖？");
                        Message.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                        Message.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
                        ans = Message.exec();
                    }
                    else
                    {
                        QMessageBox Message(QMessageBox::NoIcon, "提示！", "控制卡内程序已满，请删除后再下载！");
                        Message.exec();
                        return;
                    }
                }
            }
            if(!strcmp(AMC4030::pComTimerWork->ComThrConPara.comFileInfo.filename[0], ch))
            {
                QMessageBox Message(QMessageBox::Question, "", "控制卡内存在同名文件，是否覆盖？");
                Message.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                Message.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
                ans = Message.exec();
            }
            else
            {
                QMessageBox Message(QMessageBox::Question, "", "是否确定把当前程序写入控制卡？");
                Message.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                Message.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
                ans = Message.exec();
            }
            //QMessageBox megBox(QMessageBox::Question,"",QObject::tr("是否确定把当前程序写入控制卡？"));
            //megBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            //megBox.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
            //int ret= megBox.exec();//用于messagebox显示
            switch(ans)
            {
            case QMessageBox::AcceptRole:////////把二进制文件的数据传输到卡里///////
            {
                int Status = 100;
                Status = tMachineStatus.dwWorkStatus;
                qDebug()<<"下载程序时的Status状态"<<Status;

                if(Status&0x02)//如果当前控制卡里有程序且正在执行自动控制
                {
                    QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("控制器正在执行自动控制，请先转到“手动操作”界面并将当前状态切换为手动控制！"));
                    mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                    mBox.exec();
                }
                else
                {

                    //                    //QString转化为string类型，然后由string转化为const char*，最后const char*转化char*
                    //                    std::string F_N = FileName.toStdString();//QString转化为string类型
                    //                    const char*PATH;
                    //                    PATH = F_N.c_str();//string转化为const char*
                    //                    char* Path =const_cast<char*>(PATH);//const char*转化char*

                    QByteArray cpath = FileName_elo.toLocal8Bit();//包含中文路径的字符转换
                    char* Path= cpath.data();//string转化为char*

                    int result_DF = AMC4030_DLL.Q_DownloadFile(Path,2,1);
                    qDebug()<<"下载到控制卡的路径"<<Path<<",返回值："<<result_DF;

                    if(result_DF==1)
                    {
                        QMessageBox mBox(QMessageBox::Information,"",QObject::tr("程序已成功写入控制卡！"));
                        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                        mBox.exec();
                        AMC4030::pComTimerWork->ComThrConPara.comFileInfo.file_total++;
                    }
                    else
                    {
                        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("程序写入控制卡失败！"));
                        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                        mBox.exec();
                    }
                }
            }
                break;
            default:
                break;
            }
            return;
        }
        else
        {
            QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("未连接控制器！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
        }
    }
    else
    {
        //因为自动填缺省文件，没有使用
        switch(QMessageBox::question(this,"", QObject::tr("当前程序列表为空，请先新建一个程序。是否新建程序？"),
                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
        {
        case QMessageBox::Ok:
            CreateAnEmptyFile();//新建一个空程序
            break;
        default:
            break;
        }
        return;
    }
}

//写二进制文件
void newProgramEditor::WriteBinaryFile()
{
    int ROW = ui->tableWidget->rowCount(); //获取表格总行数

    //建立对应的二进制文件，并打开
    QString program=ui->ComBox_SelectProgram->itemText(ui->ComBox_SelectProgram->currentIndex());
    QString FileName= (currentDir +"/"+program+".elo");
    QString File = program;
    MC_CMD_WriteBegin(FileName, File);

    //按行写二进制文件
    for ( int i = 0 ; i < ROW; i++ )
    {
        ISTR1 = ui->tableWidget->item(i,0)->text();//指令集
        ISTR2 = ui->tableWidget->item(i,1)->text();//具体指令
        P1 = ui->tableWidget->item(i,2)->text();//第一个参数
        P2 = ui->tableWidget->item(i,3)->text();//第二个参数
        P3 = ui->tableWidget->item(i,4)->text();//第三个参数

        WriteEventToFile();//把数据写入二进制文件
    }
    MC_CMD_End();//关闭对应的二进制文件
}

//把数据写入二进制文件
void newProgramEditor::WriteEventToFile()
{
    g_tCmdFile.WriteHead();

    //系统操作
    if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("停止")))
        MC_CMD_StopAll();
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("启动")))
        MC_CMD_Start();
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("暂停")))
        MC_CMD_Pause();
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("恢复")))
        MC_CMD_Resume();
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("延时等待")))
        MC_CMD_DelayTime(P1.toInt());
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("等待电机完成")))
        MC_CMD_CheckMotorDone(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("停止电机运动")))
        MC_CMD_StopNamedMotor(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("系统操作"))&&(ISTR2==QObject::tr("常等待")))
        MC_CMD_Waiting();

    //流程控制
    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("程序行间跳转")))
        MC_CMD_ProgramJump(P1.toInt());
    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("程序循环")))
        MC_CMD_ProgramLoop(P1.toInt(),P2.toInt());
    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("单次检测跳转")))
        MC_CMD_InputJump(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("持续检测跳转")))
        MC_CMD_OpenInputInterrupt(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("关闭持续检测")))
        MC_CMD_CloseInputInterrupt(P1.toInt(),P2.toInt());
    //    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("子程序调用")))
    //        MC_CMD_SubroutineCall(P1.toInt());
    //    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("子程序返回")))
    //        MC_CMD_SubroutineReturn();
    //    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("开启定时中断")))
    //        MC_CMD_OpenTimerInterrupt(P1.toInt(),P2.toInt(),P3.toInt());
    //    else if((ISTR1==QObject::tr("流程控制"))&&(ISTR2==QObject::tr("关闭定时中断")))
    //        MC_CMD_CloseTimerInterrupt();

    //输出口操作
    else if((ISTR1==QObject::tr("输出口操作"))&&(ISTR2==QObject::tr("输出口设置")))
        MC_CMD_SetOutputBit(P1.toInt(),P2.toInt());

    //    //回零运动
    //    else if((ISTR1==QObject::tr("回零运动"))&&(ISTR2==QObject::tr("设置回零速度")))
    //        MC_CMD_SetHomeSpeed(P1.toFloat(),P2.toFloat(),P3.toFloat());
    //    else if((ISTR1==QObject::tr("回零运动"))&&(ISTR2==QObject::tr("启动回零")))
    //        MC_CMD_StartHome(P1.toInt(),P2.toInt(),P3.toInt());
    //    //回零运动
    //    else if((ISTR1==QObject::tr("回零运动"))&&(ISTR2==QObject::tr("设置回零速度")))
    //    {
    //        MC_CMD_SetHomeSpeed(P1.toFloat(),P2.toFloat(),P3.toFloat());
    //        int X=1,Y=1,Z=1;
    //        if(P1.toFloat()==0)
    //            X=0;
    //        if(P2.toFloat()==0)
    //            Y=0;
    //        if(P3.toFloat()==0)
    //            Z=0;
    //        MC_CMD_StartHome(X,Y,Z);
    //    }
    //回零运动
    else if((ISTR1==QObject::tr("回零运动"))&&(ISTR2==QObject::tr("设置回零速度")))
        MC_CMD_SetAndStartHome(P1.toFloat(),P2.toFloat(),P3.toFloat());

    //直线点位运动
    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("设置点位速度")))
        MC_CMD_SetPointSpeed(P1.toFloat(),P2.toFloat());
    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("三轴相对运动")))
        MC_CMD_ThreeAxisRelativeMotion(P1.toFloat(),P2.toFloat(),P3.toFloat());
    //    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("单轴绝对运动")))
    //    {
    //        if(P1.toInt()==1)
    //            MC_CMD_AbsoluteMotion(0x01,P2.toFloat(),0.00,0.00);
    //        else if(P1.toInt()==2)
    //            MC_CMD_AbsoluteMotion(0x02,0.00,P2.toFloat(),0.00);//0x02是16进制，换成2进制0010
    //        else if(P1.toInt()==3)
    //            MC_CMD_AbsoluteMotion(0x04,0.00,0.00,P2.toFloat());//0x04是16进制，换成2进制0100，表示Z轴
    //    }
    //    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("XY绝对运动")))
    //        MC_CMD_AbsoluteMotion(0x03,P1.toFloat(),P2.toFloat(),0.00);//换成2进制0011，表示X、Y轴
    //    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("XZ绝对运动")))
    //        MC_CMD_AbsoluteMotion(0x05,P1.toFloat(),0.00,P2.toFloat());
    //    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("YZ绝对运动")))
    //        MC_CMD_AbsoluteMotion(0x06,0.00,P1.toFloat(),P2.toFloat());
    //    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("三轴绝对运动")))
    //        MC_CMD_AbsoluteMotion(0x07,P1.toFloat(),P2.toFloat(),P3.toFloat());

    else if((ISTR1==QObject::tr("直线点位运动"))&&(ISTR2==QObject::tr("三轴绝对运动")))
    {
        if(P1.toFloat()!=0&&P2.toFloat()==0&&P3.toFloat()==0)
            MC_CMD_AbsoluteMotion(0x01,P1.toFloat(),0.00,0.00);//单轴X
        else if(P1.toFloat()==0&&P2.toFloat()!=0&&P3.toFloat()==0)
            MC_CMD_AbsoluteMotion(0x02,0.00,P2.toFloat(),0.00);//单轴Y
        else if(P1.toFloat()==0&&P2.toFloat()==0&&P3.toFloat()!=0)
            MC_CMD_AbsoluteMotion(0x04,0.00,0.00,P3.toFloat());//单轴Z
        else if(P1.toFloat()!=0&&P2.toFloat()!=0&&P3.toFloat()==0)
            MC_CMD_AbsoluteMotion(0x03,P1.toFloat(),P2.toFloat(),0.00);//XY
        else if(P1.toFloat()!=0&&P2.toFloat()==0&&P3.toFloat()!=0)
            MC_CMD_AbsoluteMotion(0x05,P1.toFloat(),0.00,P3.toFloat());//XZ
        else if(P1.toFloat()==0&&P2.toFloat()!=0&&P3.toFloat()!=0)
            MC_CMD_AbsoluteMotion(0x06,0.00,P2.toFloat(),P3.toFloat());//YZ
        else if(P1.toFloat()!=0&&P2.toFloat()!=0&&P3.toFloat()!=0)
            MC_CMD_AbsoluteMotion(0x07,P1.toFloat(),P2.toFloat(),P3.toFloat());//三轴XYZ
    }

    //独立插补运动
    else if((ISTR1==QObject::tr("独立插补运动"))&&(ISTR2==QObject::tr("设置独立运动速度")))
        MC_CMD_SetIndependentSpeed(P1.toInt(),P2.toFloat(),P3.toFloat());
    else if((ISTR1==QObject::tr("独立插补运动"))&&(ISTR2==QObject::tr("三轴独立相对插补")))
        MC_CMD_IndependentMotion(P1.toFloat(),P2.toFloat(),P3.toFloat());

    //DM寄存器
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM赋值")))
        MC_CMD_DM_Assignment(P1.toInt(),P2.toFloat());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM加常数")))
        MC_CMD_DM_AddNum(P1.toInt(),P2.toFloat());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM加DM")))
        MC_CMD_DM_AddDM(P1.toInt(),P2.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作延时")))
        MC_CMD_DM_Delay(P1.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作程序循环")))
        MC_CMD_DM_ProgramLoop(P1.toInt(),P2.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作回零")))
        MC_CMD_DM_SetAndStartHome(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作点位速度")))
        MC_CMD_DM_PMOV_Speed(P1.toInt(),P2.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作相对运动")))
        MC_CMD_DM_PMOV(P1.toInt(),P2.toInt(),P3.toInt());
    else if((ISTR1==QObject::tr("DM寄存器"))&&(ISTR2==QObject::tr("DM作绝对运动")))
    {
        if(P1.toInt()!=0&&P2.toInt()==0&&P3.toInt()==0)
            MC_CMD_DM_ABS_PMOV(0x01,P1.toInt(),0.00,0.00);//单轴X
        else if(P1.toInt()==0&&P2.toInt()!=0&&P3.toInt()==0)
            MC_CMD_DM_ABS_PMOV(0x02,0.00,P2.toInt(),0.00);//单轴Y
        else if(P1.toInt()==0&&P2.toInt()==0&&P3.toInt()!=0)
            MC_CMD_DM_ABS_PMOV(0x04,0.00,0.00,P3.toInt());//单轴Z
        else if(P1.toInt()!=0&&P2.toInt()!=0&&P3.toInt()==0)
            MC_CMD_DM_ABS_PMOV(0x03,P1.toInt(),P2.toInt(),0.00);//XY
        else if(P1.toInt()!=0&&P2.toInt()==0&&P3.toInt()!=0)
            MC_CMD_DM_ABS_PMOV(0x05,P1.toInt(),0.00,P3.toInt());//XZ
        else if(P1.toInt()==0&&P2.toInt()!=0&&P3.toInt()!=0)
            MC_CMD_DM_ABS_PMOV(0x06,0.00,P2.toInt(),P3.toInt());//YZ
        else if(P1.toInt()!=0&&P2.toInt()!=0&&P3.toInt()!=0)
            MC_CMD_DM_ABS_PMOV(0x07,P1.toInt(),P2.toInt(),P3.toInt());//三轴XYZ
    }
}

//新建程序
void newProgramEditor::on_Btn_NewProgram_clicked()
{
    QMessageBox megBox(QMessageBox::Question,"",QObject::tr("是否确定放弃当前程序编辑，新建程序？"));
    megBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
    megBox.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
    int ret= megBox.exec();//用于messagebox显示

    switch(ret)
    {
    case QMessageBox::AcceptRole:
        CreateAnEmptyFile();//新建一个空程序
    default:
        break;
    }
    return;
}

//新建一个空程序
void newProgramEditor::CreateAnEmptyFile()
{
    //转到输入新建程序的名字的界面
    newBuildFile*dialog_BF=new newBuildFile();
    dialog_BF->exec();

    if(!dialog_BF->File_Name.isEmpty())
    {
        QString FileName=currentDir+"/"+dialog_BF->File_Name +".txt";

        QFile file(FileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            QTextStream in(&file);
            if(ui->Btn_NewProgram->text()=="新建")
            {   QString str="指令集;指令;参数 1;参数 2;参数 3;备注信息";
                in<<str;
            }
            else if(ui->Btn_NewProgram->text()=="New")
            {   QString str="ISTR Sets;ISTR;PARM 1;PARM 2;PARM 3;Comments";
                in<<str;
            }
        }
        file.close();

        ListRefresh();//ComBox_SelectProgram的列表刷新
        ui->ComBox_SelectProgram->setCurrentText(dialog_BF->File_Name);
        ComboxToInitialPos();//Combox 移动到初始位置
        /* QStringList qsl;
            qsl<<tr("指令集")<<tr("指令")<<tr("参数 1")<<tr("参数 2")<<tr("参数 3")<<tr("备注信息");
            ui->tableWidget->setHorizontalHeaderLabels(qsl);*/
    }
    delete dialog_BF;
}

//保存程序
void newProgramEditor::on_Btn_SaveProgram_clicked()
{
    if(ui->ComBox_SelectProgram->currentText()!="")
    {
        QString FileName=currentDir+"/"+ui->ComBox_SelectProgram->currentText()+".txt";
        Current_FileName=ui->ComBox_SelectProgram->currentText();

        //转到程序保存的界面
        newSaveFile*dialog_SF=new newSaveFile(Current_FileName);//用Qt带自定义参数的构造函数，要修改newSaveFile类的构造函数
        // dialog_SF->set_file_name(Current_FileName);//方法二：单独写接口函数
        dialog_SF->exec();

        if(dialog_SF->new_file_name == Current_FileName)//判断是否有修改名字
        {
            WriteInTXT(FileName);//把表格数据写入原来名字的txt文件
        }
        else
        {
            QString new_FileName=currentDir+"/"+dialog_SF->new_file_name+".txt";
            WriteInTXT(new_FileName);//把表格数据写入修改后名字的txt文件

            QFile f;
            f.remove(FileName);//移除原来名字的txt文件和二进制文件
            f.remove(currentDir+"/"+Current_FileName + ".elo");//移除原来名字的elo文件

            ListRefresh();//ComBox_SelectProgram的列表刷新
            ui->ComBox_SelectProgram->setCurrentText(dialog_SF->new_file_name);
            ComboxToInitialPos();//Combox 移动到初始位置
        }
        delete dialog_SF;
    }

    //因为自动填缺省文件，没有使用
    //    else
    //    {
    //        switch(QMessageBox::question(this,"", QObject::tr("当前程序列表为空，请先新建一个程序。是否新建程序？"),
    //                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    //        {
    //        case QMessageBox::Ok:
    //            CreateAnEmptyFile();//新建一个空程序
    //            break;
    //        default:
    //            break;
    //        }
    //        return;
    //    }
}

//把表格数据写入txt文件
void newProgramEditor::WriteInTXT(QString TXT_Name)
{
    int ROW = ui->tableWidget->rowCount(); //获取表格总行数
    int COLUMN=ui->tableWidget->columnCount();//获取表格总列数

    if (!TXT_Name.isEmpty())
    {
        QFile file(TXT_Name);
        //以只写并且覆盖已有内容的形式操作文件，因为QIODevice::Truncate会直接将文件内容清空
        bool ret = file.open( QIODevice::Truncate | QIODevice::WriteOnly);
        if(!ret)
            return;
        QTextStream stream(&file);
        stream.setCodec("Unicode");

        QString conTents;

        QHeaderView * header = ui->tableWidget->horizontalHeader() ;
        if (header)
        {
            //添加表头的列标题
            for ( int i = 0; i < (header->count()-1); i++ )
            {
                QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(i);
                if (!item)
                {
                    continue;
                }
                conTents += (item->text() +";");
            }
            QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(header->count()-1);
            //windows下txt文档的换行符是由两个字符"\r\n"构成的，,而linux下的文档的换行符号是'\n'
            conTents += (item->text()+"\r\n");
        }

        //先按行，然后再在这一行中按列添加内容
        for ( int i = 0 ; i < ROW; i++ )
        {
            for ( int j = 0; j < COLUMN-1; j++ )
            {
                QTableWidgetItem* item = ui->tableWidget->item(i, j);
                //                if ( !item )
                //                    continue;
                QString str = item->text();
                conTents += (str+ ";");
            }
            QTableWidgetItem* item = ui->tableWidget->item(i,COLUMN-1);
            //            if ( !item )
            //                continue;
            QString str = item->text();
            conTents += (str+"\r\n");
        }
        stream << conTents;
        file.close();
    }
    //ListRefresh();//ComBox_SelectProgram的列表刷新
}

//ComBox_SelectProgram的列表刷新
void newProgramEditor::ListRefresh()
{
    ui->ComBox_SelectProgram->clear();

    QFileInfoList InfoList = QDir(currentDir).entryInfoList();//获取当前目录所有文件

    QStringList qssName;
    //遍历
    foreach(QFileInfo fileInfo,InfoList)
    {
        if(!fileInfo.isFile())
            continue;//不是文件则继续，只用于加速

        else if(fileInfo.suffix()=="txt")
        {
            QString string = fileInfo.fileName().left(fileInfo.fileName().length()-4);//去掉文件的后缀名“.txt”
            qssName<<string;
            qSort(qssName);//QStringList中的对象按字母表升序排序

//            if(string=="_点位运动")
//                InitialProgram[0]=1;
//            if(string=="_无限往复")
//                InitialProgram[1]=1;
//            if(string=="_步进运动")
//                InitialProgram[2]=1;
//            if(string=="_多次往复")
//                InitialProgram[3]=1;
            if(string=="_PT_MT")
                InitialProgram[0]=1;
            if(string=="_INF_RCP")
                InitialProgram[1]=1;
            if(string=="_SXS_MT")
                InitialProgram[2]=1;
            if(string=="_RPT_RCP")
                InitialProgram[3]=1;
        }
    }

    //读取配置文件，当前中英文状态
    QSettings *configIniRead = new QSettings("UserSettings.ini", QSettings::IniFormat);
    int cur_language = configIniRead->value("/LanguageSelect/CurrentSelect").toInt();
    delete configIniRead;

    for(int i=0;i<TotalProgram;i++)
    {
        if(InitialProgram[i]==0)
        {
            WriteInitialProgram(i);//往表格里写这个默认指令文件
//            if(cur_language==0)//当前是中文状态
//            {
//                if(i==0)
//                    WriteInTXT(currentDir+"/_点位运动.txt");//把表格的数据写入一个txt文件
//                else if(i==1)
//                    WriteInTXT(currentDir+"/_无限往复.txt");//把表格的数据写入一个txt文件
//                else if(i==2)
//                    WriteInTXT(currentDir+"/_步进运动.txt");//把表格的数据写入一个txt文件
//                else if(i==3)
//                    WriteInTXT(currentDir+"/_多次往复.txt");//把表格的数据写入一个txt文件
//            }
//            else//当前是英文状态
            {
                if(i==0)
                    WriteInTXT(currentDir+"/_PT_MT.txt");//把表格的数据写入一个txt文件
                else if(i==1)
                    WriteInTXT(currentDir+"/_INF_RCP.txt");//把表格的数据写入一个txt文件
                else if(i==2)
                    WriteInTXT(currentDir+"/_SXS_MT.txt");//把表格的数据写入一个txt文件
                else if(i==3)
                    WriteInTXT(currentDir+"/_RPT_RCP.txt");//把表格的数据写入一个txt文件
            }
        }
    }
    ui->ComBox_SelectProgram->addItems(qssName);

//    //当列表为空的情况下，加了上面的if else后，应该注释掉这种情况
//    if(qssName.isEmpty())
//    {
//        WriteDefault();//往表格里写一个初始的缺省指令
//        WriteInTXT(currentDir+"/default.txt");//把表格的数据写入一个txt文件
//        ISTR_Sets_RowColor();//设置不同指令集所在行的颜色

//        CenterContent();//表格内容居中
//        ListRefresh();//列表再刷新
//    }
//    else
//        ui->ComBox_SelectProgram->addItems(qssName);

    //打开上次关闭系统前的程序
    ReadUserSettingsCfgFile();
    if(qssName.count()<=CUR_PROG&&CUR_PROG!=0)
        ui->ComBox_SelectProgram->setCurrentIndex(CUR_PROG-1);
    else
        ui->ComBox_SelectProgram->setCurrentIndex(CUR_PROG);
}

void newProgramEditor::ReadUserSettingsCfgFile()
{
    QFile file("UserSettings.ini");
    if (file.exists())
    {
        QSettings *configIniRead = new QSettings("UserSettings.ini", QSettings::IniFormat);
        CUR_PROG = configIniRead->value("/ProgramSelect/CurrentProgram").toInt();
        delete configIniRead;
    }
    else
        CUR_PROG = 0;//如果没有配置文件，则设置初始值为0
}

void newProgramEditor::on_ComBox_SelectProgram_activated()
{
    CUR_PROG=ui->ComBox_SelectProgram->currentIndex();
    WriteUserSettingsCfgFile();
}

void newProgramEditor::WriteUserSettingsCfgFile()
{
    QFile file("UserSettings.ini");
    if (file.exists())
    {
        //Qt中使用QSettings类读写ini文件
        //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QSettings *configIniWrite = new QSettings("UserSettings.ini", QSettings::IniFormat);

        //向ini文件的节[ProgramSelect]写入内容,节下的第一个键值是CUR_PROG
        configIniWrite->setValue("/ProgramSelect/CurrentProgram",QString::number(CUR_PROG));
        delete configIniWrite; //写入完成后删除指针
    }
}

//表格内容居中
void newProgramEditor::CenterContent()
{
    int ROW = ui->tableWidget->rowCount(); //获取表格总行数
    int COLUMN=ui->tableWidget->columnCount();//获取表格总列数
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COLUMN;j++)
        {
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

//往表格里写对应的默认指令
void newProgramEditor::WriteInitialProgram(int ProgramCase)
{
    switch (ProgramCase) {
    case 0:
        ProgramCase0();
        break;
    case 1:
        ProgramCase1();
        break;
    case 2:
        ProgramCase2();
        break;
    case 3:
        ProgramCase3();
        break;
    default:
        break;
    }
}

//_点位运动
void newProgramEditor::ProgramCase0()
{
    ui->tableWidget->setRowCount(7);  //设置行数为6
    ui->tableWidget->setColumnCount(6); //设置列数为6
    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度

    ui->tableWidget->setItem(0,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem( QObject::tr("持续检测跳转")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(1,0,new QTableWidgetItem( QObject::tr("系统操作")));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem( QObject::tr("常等待")));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(2,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem( QObject::tr("关闭持续检测")));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(3,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,3,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,4,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(4,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem( QObject::tr("设置点位速度")));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(4,3,new QTableWidgetItem("200"));
    ui->tableWidget->setItem(4,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(5,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,3,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,4,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(6,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(6,1,new QTableWidgetItem( QObject::tr("程序行间跳转")));
    ui->tableWidget->setItem(6,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(6,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,5,new QTableWidgetItem(""));
}

//_往复运动
void newProgramEditor::ProgramCase1()
{
    ui->tableWidget->setRowCount(10);  //设置行数为10
    ui->tableWidget->setColumnCount(6); //设置列数为6
    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度

    ui->tableWidget->setItem(0,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem( QObject::tr("持续检测跳转")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(1,0,new QTableWidgetItem( QObject::tr("系统操作")));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem( QObject::tr("常等待")));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(2,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem( QObject::tr("关闭持续检测")));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(3,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,3,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,4,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(4,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem( QObject::tr("设置点位速度")));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(4,3,new QTableWidgetItem("200"));
    ui->tableWidget->setItem(4,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(5,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,3,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,4,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(6,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(6,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(6,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(6,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(7,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(7,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(7,2,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,3,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,4,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(8,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(8,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(8,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(8,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(9,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(9,1,new QTableWidgetItem( QObject::tr("程序行间跳转")));
    ui->tableWidget->setItem(9,2,new QTableWidgetItem("6"));
    ui->tableWidget->setItem(9,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(9,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(9,5,new QTableWidgetItem(""));
}

//_步进运动
void newProgramEditor::ProgramCase2()
{
    ui->tableWidget->setRowCount(9);  //设置行数为8
    ui->tableWidget->setColumnCount(6); //设置列数为6
    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度

    ui->tableWidget->setItem(0,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem( QObject::tr("持续检测跳转")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(1,0,new QTableWidgetItem( QObject::tr("系统操作")));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem( QObject::tr("常等待")));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(2,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem( QObject::tr("关闭持续检测")));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(3,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,3,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,4,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(4,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem( QObject::tr("设置点位速度")));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(4,3,new QTableWidgetItem("200"));
    ui->tableWidget->setItem(4,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(5,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem("40"));
    ui->tableWidget->setItem(5,3,new QTableWidgetItem("40"));
    ui->tableWidget->setItem(5,4,new QTableWidgetItem("40"));
    ui->tableWidget->setItem(5,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(6,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(6,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(6,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(6,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(7,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(7,1,new QTableWidgetItem( QObject::tr("程序循环")));
    ui->tableWidget->setItem(7,2,new QTableWidgetItem("6"));
    ui->tableWidget->setItem(7,3,new QTableWidgetItem("5"));
    ui->tableWidget->setItem(7,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(7,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(8,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(8,1,new QTableWidgetItem( QObject::tr("程序行间跳转")));
    ui->tableWidget->setItem(8,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(8,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,5,new QTableWidgetItem(""));
}

//_多次往复运动
void newProgramEditor::ProgramCase3()
{
    ui->tableWidget->setRowCount(11);  //设置行数为10
    ui->tableWidget->setColumnCount(6); //设置列数为6
    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度

    ui->tableWidget->setItem(0,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem( QObject::tr("持续检测跳转")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(1,0,new QTableWidgetItem( QObject::tr("系统操作")));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem( QObject::tr("常等待")));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(2,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem( QObject::tr("关闭持续检测")));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(3,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,3,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,4,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(3,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(4,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem( QObject::tr("设置点位速度")));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(4,3,new QTableWidgetItem("200"));
    ui->tableWidget->setItem(4,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(5,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,3,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,4,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(5,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(6,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(6,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(6,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(6,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(7,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(7,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(7,2,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,3,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,4,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(7,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(8,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(8,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(8,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(8,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(9,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(9,1,new QTableWidgetItem( QObject::tr("程序循环")));
    ui->tableWidget->setItem(9,2,new QTableWidgetItem("6"));
    ui->tableWidget->setItem(9,3,new QTableWidgetItem("5"));
    ui->tableWidget->setItem(9,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(9,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(10,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(10,1,new QTableWidgetItem( QObject::tr("程序行间跳转")));
    ui->tableWidget->setItem(10,2,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(10,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(10,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(10,5,new QTableWidgetItem(""));
}

//往表格里写一个初始的缺省指令
void newProgramEditor::WriteDefault()
{
    ui->tableWidget->setRowCount(8);  //设置行数为8
    ui->tableWidget->setColumnCount(6); //设置列数为6

    ui->tableWidget->setColumnWidth(0,110);
    ui->tableWidget->setColumnWidth(1,130);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//表格的最后一列自适应宽度
    ui->tableWidget->setItem(0,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem( QObject::tr("设置点位速度")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem("1000"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(1,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem("50"));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem("70"));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(2,0,new QTableWidgetItem( QObject::tr("回零运动")));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem( QObject::tr("设置回零速度")));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem("60"));
    ui->tableWidget->setItem(2,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(3,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem( QObject::tr("三轴绝对运动")));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem("80"));
    ui->tableWidget->setItem(3,3,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(3,4,new QTableWidgetItem("120"));
    ui->tableWidget->setItem(3,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(4,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem( QObject::tr("三轴绝对运动")));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,3,new QTableWidgetItem("100"));
    ui->tableWidget->setItem(4,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(5,0,new QTableWidgetItem( QObject::tr("直线点位运动")));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem( QObject::tr("三轴相对运动")));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem("-80"));
    ui->tableWidget->setItem(5,3,new QTableWidgetItem("-100"));
    ui->tableWidget->setItem(5,4,new QTableWidgetItem("-120"));
    ui->tableWidget->setItem(5,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(6,0,new QTableWidgetItem(QObject::tr("系统操作")));
    ui->tableWidget->setItem(6,1,new QTableWidgetItem(QObject::tr("延时等待")));
    ui->tableWidget->setItem(6,2,new QTableWidgetItem("2000"));
    ui->tableWidget->setItem(6,3,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,5,new QTableWidgetItem(""));

    ui->tableWidget->setItem(7,0,new QTableWidgetItem( QObject::tr("流程控制")));
    ui->tableWidget->setItem(7,1,new QTableWidgetItem( QObject::tr("程序循环")));
    ui->tableWidget->setItem(7,2,new QTableWidgetItem("2"));
    ui->tableWidget->setItem(7,3,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(7,4,new QTableWidgetItem(""));
    ui->tableWidget->setItem(7,5,new QTableWidgetItem(""));
}

//选择程序
void newProgramEditor::on_ComBox_SelectProgram_currentIndexChanged()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    QString program=ui->ComBox_SelectProgram->itemText(ui->ComBox_SelectProgram->currentIndex());
    QString FileName= (currentDir +"/"+program+".txt");

    ImportExcel(FileName);//导入txt内容到tableWidget中

    ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
    ComboxToInitialPos();//Combox 移动到初始位置

    //CUR_PROG=ui->ComBox_SelectProgram->currentIndex();
    //WriteLangCfgFile();
}

//导入txt内容到tableWidget中
void newProgramEditor::ImportExcel(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QFile file;
        file.setFileName(fileName);
        //打开文件
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //            QMessageBox msg;
            //            msg.setText("打开文件失败!");
            //            msg.exec();
            qDebug()<<"文件不在当前位置，打开文件失败";
        }
        else
        {
            if(!file.size())
            {
                //QMessageBox::warning(this,"", QObject::tr("文件内容为空！"),QMessageBox::Ok);
                qDebug()<<QObject::tr("文件内容为空！");
            }
            else
            {
                //将文件数据导入表格
                int r_count = 0;        //统计文件的行数
                QStringList textList;   //记录文件中每一行的数据
                QTextStream in(&file);

                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    textList.append(line);          //保存文件的数据
                    r_count++;                      //记录文件的行数 第一行为表头
                }
                file.close();       //关闭文件

                if(textList.isEmpty())
                {
                    QMessageBox mBox(QMessageBox::Information,"",QObject::tr("文件内容为空！"));
                    mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
                    mBox.exec();
                }
                else if(!textList.isEmpty())
                {
                    QStringList listRowHeader = textList.at(0).split(";");
                    int c_count = listRowHeader.count();
                    ui->tableWidget->clear();
                    ui->tableWidget->setRowCount(r_count-1);      //第一行是行列表头
                    ui->tableWidget->setColumnCount(c_count);   //最后一行是“\t"

                    //读取第一行表头的内容
                    ui->tableWidget->setHorizontalHeaderLabels(listRowHeader);

                    QTableWidgetItem *columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(0); //获得水平方向第一列表头的Item对象
                    columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
                    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
                    columnHeaderItem0->setTextColor(QColor(50,111,30)); //设置文字颜色

                    QTableWidgetItem *columnHeaderItem1 = ui->tableWidget->horizontalHeaderItem(1); //获得水平方向第二列表头的Item对象
                    columnHeaderItem1->setFont(QFont("Helvetica")); //设置字体
                    columnHeaderItem1->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
                    columnHeaderItem1->setTextColor(QColor(200,111,30)); //设置文字颜色

                    //读取第二行及以后表格的内容
                    for(int row = 1; row < r_count; row++)
                    {
                        QStringList tmpList;
                        tmpList = textList.at(row).split(";");

                        for(int col = 0; col < c_count; col++)
                        {
                            QTableWidgetItem *item = new QTableWidgetItem(tmpList.at(col));
                            ui->tableWidget->setItem(row-1, col, item);
                        }
                    }
                }
                CenterContent();//表格内容居中
            }
        }
        reWriteTable();
        ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
    }
}

//删除程序
void newProgramEditor::on_Btn_DeleteProgram_clicked()
{
    if(ui->ComBox_SelectProgram->currentText()!="")
    {
        QMessageBox megBox(QMessageBox::Question,"",QObject::tr("是否确定删除当前程序及其文件？"));
        megBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        megBox.addButton(QObject::tr("取消"),QMessageBox::RejectRole);
        int ret= megBox.exec();//用于messagebox显示

        switch(ret)
        {
        case QMessageBox::AcceptRole:
        {
            DeleteProgram();
        }
        default:
            break;
        }
        return;
    }

    //因为自动填缺省文件，没有使用
    //    else
    //    {
    //        switch(QMessageBox::question(this,"", QObject::tr("当前程序列表为空，请先新建一个程序。是否新建程序？"),
    //                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    //        {
    //        case QMessageBox::Ok:
    //            CreateAnEmptyFile();//新建一个空程序
    //            break;
    //        default:
    //            break;
    //        }
    //        return;
    //    }
}

void newProgramEditor::DeleteProgram()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    //动态语言翻译
    QStringList qsl;
    qsl<<tr("指令集")<<tr("指令")<<tr("参数 1")<<tr("参数 2")<<tr("参数 3")<<tr("备注信息");
    ui->tableWidget->setHorizontalHeaderLabels(qsl);

    QString program=ui->ComBox_SelectProgram->itemText(ui->ComBox_SelectProgram->currentIndex());

    QFile f;
    f.remove(currentDir+"/"+program + ".txt");
    f.remove(currentDir+"/"+program + ".elo");

    ListRefresh();//ComBox_SelectProgram的列表刷新
    CUR_PROG=ui->ComBox_SelectProgram->currentIndex();
    if(CUR_PROG!=-1)
        WriteUserSettingsCfgFile();
    ComboxToInitialPos();//Combox 移动到初始位置
}

//指定行上移
void newProgramEditor::on_Btn_MoveUpRow_clicked()
{
    ComboxToInitialPos();//Combox 移动到初始位置

    int columns = ui->tableWidget->columnCount();//获取表格列数
    int nCurrRow = ui->tableWidget->currentRow();;//获取选中的行
    if(nCurrRow < 0)    //没有被选中的就返回
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("请选中某一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if(nCurrRow == 0)    //不能选中第一行
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("不能选中第一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if(nCurrRow>0)
    {
        if((ui->tableWidget->item(nCurrRow,0)!=NULL)&&(ui->tableWidget->item(nCurrRow-1,0)!=NULL))//第一列的内容不能为空
        {
            int nNextRow =nCurrRow - 1;

            QVector<QTableWidgetItem*>m_CurrItemVector;
            QVector<QTableWidgetItem*>m_NextItemVector;

            QTableWidgetItem *CurrItem = new QTableWidgetItem;
            QTableWidgetItem *NextItem = new QTableWidgetItem;
            CurrItem = ui->tableWidget->item(nCurrRow, 0);
            NextItem = ui->tableWidget->item(nNextRow, 0);
            QString CurrText = CurrItem->text();
            QString NextText = NextItem->text();

            for (int i = 1; i < columns; i++)
            {
                m_CurrItemVector.push_back(ui->tableWidget->takeItem(nCurrRow, i));
            }
            for (int i = 1; i < columns; i++)
            {
                m_NextItemVector.push_back(ui->tableWidget->takeItem(nNextRow, i));
            }
            for (int i = 1; i < columns; i++)
            {
                ui->tableWidget->setItem(nNextRow, i, m_CurrItemVector[i - 1]);
            }
            for (int i = 1; i < columns; i++)
            {
                ui->tableWidget->setItem(nCurrRow, i, m_NextItemVector[i - 1]);
            }
            ui->tableWidget->setCurrentCell(nNextRow, 0);
            CurrItem->setText(NextText);
            NextItem->setText(CurrText);

            ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
        }
        else
        {
            //不起作用
            QMessageBox::warning(this,"",QObject::tr("请先选择第一列的指令集！"));
        }
    }
}

//指定行下移
void newProgramEditor::on_Btn_MoveDownRow_clicked()
{
    ComboxToInitialPos();//Combox 移动到初始位置

    int rows = ui->tableWidget->rowCount();//获取表格行数
    int columns = ui->tableWidget->columnCount();//获取表格列数
    int nCurrRow = ui->tableWidget->currentRow();;//获取选中的行

    if(nCurrRow < 0)    //没有被选中的就返回
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("请选中某一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if((nCurrRow>=0)&&(nCurrRow == rows-1))//不能选择最后一行
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("不能选中最后一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if((nCurrRow>=0)&&(nCurrRow != rows-1))
    {
        if((ui->tableWidget->item(nCurrRow,0)!=NULL)&&(ui->tableWidget->item(nCurrRow+1,0)!=NULL))//第一列的内容不能为空)
        {
            int nNextRow = nCurrRow + 1;
            QVector<QTableWidgetItem*>m_CurrItemVector;
            QVector<QTableWidgetItem*>m_NextItemVector;

            QTableWidgetItem *CurrItem = new QTableWidgetItem;
            QTableWidgetItem *NextItem = new QTableWidgetItem;
            CurrItem = ui->tableWidget->item(nCurrRow, 0);
            NextItem = ui->tableWidget->item(nNextRow, 0);
            QString CurrText = CurrItem->text();
            QString NextText = NextItem->text();

            for (int i = 1; i < columns; i++)
            {
                m_CurrItemVector.push_back(ui->tableWidget->takeItem(nCurrRow, i));
            }
            for (int i = 1; i < columns; i++)
            {
                m_NextItemVector.push_back(ui->tableWidget->takeItem(nNextRow, i));
            }
            for (int i = 1; i < columns; i++)
            {
                ui->tableWidget->setItem(nNextRow, i, m_CurrItemVector[i - 1]);
            }
            for (int i = 1; i < columns; i++)
            {
                ui->tableWidget->setItem(nCurrRow, i, m_NextItemVector[i - 1]);
            }
            ui->tableWidget->setCurrentCell(nNextRow, 0);

            CurrItem->setText(NextText);
            NextItem->setText(CurrText);

            ISTR_Sets_RowColor();//设置不同指令集所在行的颜色
        }
        else
        {
            //不起作用
            QMessageBox::warning(this,"",QObject::tr("请先选择第一列的指令集！"));
        }
    }
}

//插入代码行
void newProgramEditor::on_Btn_InsertRow_clicked()
{
    if(ui->ComBox_SelectProgram->currentText()!="")
    {
        int row = ui->tableWidget->currentRow();
        int i = ui->tableWidget->rowCount(); //获取表格行数
        if(row< 0)    //没有被选中,就在最后插入
        {
            int i = ui->tableWidget->rowCount(); //获取表格行数
            ui->tableWidget->setRowCount(i+1);  //表格加一行

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(""));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(""));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(""));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(""));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(""));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(""));

            ui->tableWidget->scrollToBottom();//滚动条滚动到最底部
        }
        else if(row >= 0)    //有选中,就在选中行之后插入
        {
            ui->tableWidget->insertRow(row+1);

            ui->tableWidget->setItem(row+1,0,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row+1,1,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row+1,2,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row+1,3,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row+1,4,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row+1,5,new QTableWidgetItem(""));

            if(row==i-1)
                ui->tableWidget->scrollToBottom();
            ui->tableWidget->verticalScrollBar()->setValue(row);
        }
    }

    //因为自动填缺省文件，没有使用
    //    else
    //    {
    //        switch(QMessageBox::question(this,"", QObject::tr("当前程序列表为空，请先新建一个程序。是否新建程序？"),
    //                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    //        {
    //        case QMessageBox::Ok:
    //            CreateAnEmptyFile();//新建一个空程序
    //            break;
    //        default:
    //            break;
    //        }
    //        return;
    //    }
}

//移除选中行
void newProgramEditor::on_Btn_RemoveRow_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row < 0)    //没有被选中的就返回
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("请选中某一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    ui->tableWidget->removeRow(row);

    ComboxToInitialPos();//combox 移动到初始位置
}

//复制选中行
void newProgramEditor::on_Btn_CopyRow_clicked()
{
    int row = ui->tableWidget->currentRow();;//获取选中的行
    if(row < 0)    //没有被选中的就返回
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("请选中某一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if(row >=0)
    {
        //取出该行的字符串
        if(ui->tableWidget->item( row,0)!=NULL)
            name1= ui->tableWidget->item(row,0)->text();
        if(ui->tableWidget->item( row,1)!=NULL)//不能用else if语句
            name2= ui->tableWidget->item(row,1)->text();
        if(ui->tableWidget->item( row,2)!=NULL)
            name3= ui->tableWidget->item(row,2)->text();
        if(ui->tableWidget->item( row,3)!=NULL)
            name4= ui->tableWidget->item(row,3)->text();
        if(ui->tableWidget->item( row,4)!=NULL)
            name5= ui->tableWidget->item(row,4)->text();
        if(ui->tableWidget->item( row,5)!=NULL)
            name6= ui->tableWidget->item(row,5)->text();
    }
    ComboxToInitialPos();//combox 移动到初始位置
}

//粘贴选中的内容
void newProgramEditor::on_Btn_PasteRow_clicked()
{
    int row = ui->tableWidget->currentRow();;//获取选中的行

    if(row < 0)    //没有被选中的就返回
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("请选中某一行！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
    }
    else if(row >=0)
    {
        ui->tableWidget->setItem(row,0 ,new QTableWidgetItem(name1));
        ui->tableWidget->setItem(row,1 ,new QTableWidgetItem(name2));
        ui->tableWidget->setItem(row,2 ,new QTableWidgetItem(name3));
        ui->tableWidget->setItem(row,3 ,new QTableWidgetItem(name4));
        ui->tableWidget->setItem(row,4 ,new QTableWidgetItem(name5));
        ui->tableWidget->setItem(row,5 ,new QTableWidgetItem(name6));

        ComboxToInitialPos();//combox 移动到初始位置

        CenterContent();//表格内容居中
    }
}

//设置不同指令集所在行的颜色
void newProgramEditor::ISTR_Sets_RowColor()
{
    QString ISTR_Sets;
    for (int i = 0;i < ui->tableWidget->rowCount();i++)
    {
        for (int j = 0;j < ui->tableWidget->columnCount();j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i,j);
            const QColor Color = QColor(255,255,255);
            item->setBackgroundColor(Color);//先全部设置成白色

            ISTR_Sets = ui->tableWidget->item(i,0)->text();
            if(ISTR_Sets ==  QObject::tr("系统操作"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(252,222,156);
                item->setBackgroundColor(color);
            }
            if(ISTR_Sets ==  QObject::tr("流程控制"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(187,255,255 );
                item->setBackgroundColor(color);
            }
            if(ISTR_Sets ==  QObject::tr("输出口操作"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(180,238,180 );
                item->setBackgroundColor(color);
            }
            if(ISTR_Sets ==  QObject::tr("回零运动"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(255,225,255  );
                item->setBackgroundColor(color);
            }
            if(ISTR_Sets ==  QObject::tr("直线点位运动"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(193,205,193  );
                item->setBackgroundColor(color);
            }
            if(ISTR_Sets ==  QObject::tr("独立插补运动"))
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                const QColor color = QColor(202,255,112 );
                item->setBackgroundColor(color);
            }
        }
    }
}

void newProgramEditor::reWriteTable()
{   QStringList qsl;
    qsl<<tr("指令集")<<tr("指令")<<tr("参数 1")<<tr("参数 2")<<tr("参数 3")<<tr("备注信息");
    ui->tableWidget->setHorizontalHeaderLabels(qsl);
    int ROW=ui->tableWidget->rowCount();
    int row,column;
    for(row=0;row<ROW;row++)
    {
        for(column=0;column<=1;column++)
        {
            QString command=ui->tableWidget->item(row,column)->text();

            if(command=="系统操作"||command=="SYS OPER")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("系统操作")));
            else if(command=="停止"||command=="Stop All")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("停止")));
            else if(command=="启动"||command=="Start")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("启动")));
            else if(command=="暂停"||command=="Pause")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("暂停")));
            else if(command=="恢复"||command=="Resume")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("恢复")));
            else if(command=="延时等待"||command=="Delay Time")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("延时等待")));
            else if(command=="等待电机完成"||command=="Wait Motor Done")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("等待电机完成")));
            else if(command=="停止电机运动"||command=="Stop The Motor")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("停止电机运动")));
            else if(command=="常等待"||command=="Waiting")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("常等待")));

            else if(command=="流程控制"||command=="PROC CTL")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("流程控制")));
            else if(command=="程序行间跳转"||command=="Program Jump")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("程序行间跳转")));
            else if(command=="程序循环"||command=="Program Loop")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("程序循环")));
            else if(command=="单次检测跳转"||command=="Input Jump")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("单次检测跳转")));
            else if(command=="持续检测跳转"||command=="Open Input INT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("持续检测跳转")));
            else if(command=="关闭持续检测"||command=="Close Input INT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("关闭持续检测")));
            //            else if(command=="子程序调用"||command=="SUB Call")
            //                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("子程序调用")));
            //            else if(command=="子程序返回"||command=="SUB Call RET")
            //                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("子程序返回")));
            //            else if(command=="开启定时中断"||command=="Open Timer INT")
            //                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("开启定时中断")));
            //            else if(command=="关闭定时中断"||command=="Close Timer INT")
            //                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("关闭定时中断")));

            else if(command=="输出口操作"||command=="Output OPER")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("输出口操作")));
            else if(command=="输出口设置"||command=="Set Output")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("输出口设置")));

            else if(command=="回零运动"||command=="Home MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("回零运动")));
            else if(command=="设置回零速度"||command=="Set Home SPD")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("设置回零速度")));
            else if(command=="启动回零"||command=="Start Home")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("启动回零")));

            else if(command=="直线点位运动"||command=="PT MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("直线点位运动")));
            else if(command=="设置点位速度"||command=="Set PT SPD")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("设置点位速度")));
            else if(command=="三轴相对运动"||command=="Start RELA MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("三轴相对运动")));
            else if(command=="单轴绝对运动"||command=="Alone Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("单轴绝对运动")));
            else if(command=="XY绝对运动"||command=="XY Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("XY绝对运动")));
            else if(command=="XZ绝对运动"||command=="XZ Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("XZ绝对运动")));
            else if(command=="YZ绝对运动"||command=="YZ Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("YZ绝对运动")));
            else if(command=="三轴绝对运动"||command=="All Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("三轴绝对运动")));

            else if(command=="独立插补运动"||command=="Alone Runing MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("独立插补运动")));
            else if(command=="设置独立运动速度"||command=="Set Alone SPD")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("设置独立运动速度")));
            else if(command=="三轴独立相对插补"||command=="Start Alone Runing")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("三轴独立相对插补")));

            else if(command=="DM寄存器"||command=="DM Register")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM寄存器")));
            else if(command=="DM赋值"||command=="DM Assignment")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM赋值")));
            else if(command=="DM加常数"||command=="DM Add NUM")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM加常数")));
            else if(command=="DM加DM"||command=="DM Add DM")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM加DM")));
            else if(command=="DM作延时"||command=="DM Delay Time")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作延时")));
            else if(command=="DM作程序循环"||command=="DM Program Loop")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作程序循环")));
            else if(command=="DM作回零"||command=="DM Home MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作回零")));
            else if(command=="DM作点位速度"||command=="DM Set PT SPD")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作点位速度")));
            else if(command=="DM作相对运动"||command=="DM Start RELA MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作相对运动")));
            else if(command=="DM作绝对运动"||command=="DM All Axis MT")
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(tr("DM作绝对运动")));

            ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void newProgramEditor::changeEvent(QEvent *e)    //重写的事件处理方法
{
    QDialog::changeEvent(e);    //让基类执行事件处理方法
    switch (e->type()) {        //根据事件类型判别
    case QEvent::LanguageChange:  //如果是语言改变事件
    {
        ui->retranslateUi(this);    //更新UI的语言（看方法字面的，用户自定义方法）
        ModifyOption();
        reWriteTable();
        ISTR_Sets_RowColor();
    }
        break;
    default:
        break;
    }
}

bool newProgramEditor::eventFilter(QObject *object, QEvent *event)
{   //事件发生在tablewidget上
    if (object == ui->tableWidget->viewport())
    {   //事件类型为鼠标双击
        if( event->type() == QEvent::MouseButtonDblClick)
        {   //获取鼠标坐标
            QMouseEvent *pevent=(QMouseEvent *)event;
            int y=pevent->y();
            //int x=pevent->x();
            //qDebug()<<y;
            //qDebug()<<x;
            int row=ui->tableWidget->rowCount();
            //qDebug()<<row;
            //鼠标点击在空白处
            if(y>row*30)
            {
                on_Btn_InsertRow_clicked();
                //delete pevent;
                return true;//事件已处理，子界面处理下一事件
            }
            else
                return false;//事件未处理，传回子界面处理
        }
    }
    return false;
}

//复制粘贴的快捷键
void newProgramEditor::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_C))
        on_Btn_CopyRow_clicked();
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_V))
        on_Btn_PasteRow_clicked();
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
        on_Btn_RemoveRow_clicked();
}
