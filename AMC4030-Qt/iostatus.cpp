#include "iostatus.h"
#include "ui_iostatus.h"
#include "amc4030.h"

IOStatus::IOStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IOStatus)
{
    ui->setupUi(this);

    this->setWindowTitle(QObject::tr("IO扩展设置"));

    this->setMaximumSize(870,480); //设置界面大小
    this->setMinimumSize(870,480);

    timer_IO = new QTimer(this);
    connect(timer_IO, SIGNAL(timeout()), this, SLOT(refreshStatus()));
    timer_IO->start(300);

    initScrollLayout();

    ui->treeWidget->setColumnCount(1); //设置列数
    ui->treeWidget->setHeaderLabel(QObject::tr("扩展节点")); //设置头的标题
    //ui->treeWidget->setHeaderHidden(true);//隐藏表头

    g_setCurSign=0;
    g_everyNodeOnline=0;
    g_everyNodeOnline_Last=0;
    g_everyNodeIsChecked=0;
    g_everyNodeIsChecked_Last=0;

    g_everyNodeOnline=0x1111;//16个节点的第1、5、9、13节点在线

    connect(ui->treeWidget,SIGNAL(itemChanged (QTreeWidgetItem *,int)),this,SLOT(treeItemChanged(QTreeWidgetItem *)));
    connect(ui->treeWidget,SIGNAL(itemClicked (QTreeWidgetItem *,int)),this,SLOT(treeItemClicked(QTreeWidgetItem *)));
}

IOStatus::~IOStatus()
{
    timer_IO->stop();
    delete ui;
}

void IOStatus::refreshStatus()
{
    //    if(AMC4030::pComTimerWork->ComThrConPara.LinkStatus)
    {
        //        qDebug()<<"进入IO状态更新";
        //        int i = 0;
        //        unsigned char status = AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.IO_Status.NodeId[18];
        //        //if(AMC4030::pComTimerWork->ComThrConPara.LinkStatus)
        //        //{
        //        //for(i = 0;i < 20;i++)
        //        //{
        //        qDebug()<<AMC4030::pComTimerWork->ComThrConPara.comMachineStatus.IO_Status.NodeId[18];
        //        //qDebug()<<status;
        //        //}

        //            g_everyNodeOnline=0x1111;//16个节点的第1、5、9、13节点在线
    }

    //g_everyNodeOnline_Last和g_everyNodeOnline是16位无符号整形数据，存放在线节点
    if(g_everyNodeOnline_Last!=g_everyNodeOnline)
    {
        g_everyNodeOnline_Last=g_everyNodeOnline;
        getOnlineNode();
    }
    if(g_everyNodeIsChecked_Last!=g_everyNodeIsChecked)
    {
        qDebug()<<"GroupBox节点："<<g_everyNodeIsChecked;
        for(int i=0;i<MAX_NODE_NUM;i++)
        {
            //现在和之前的状态不一样
            int tempCur=getbit(g_everyNodeIsChecked,i);
            //qDebug()<<"节点"<<i+1<<"的tempCur："<<tempCur;
            int tempLast=getbit(g_everyNodeIsChecked_Last,i);
            //qDebug()<<"节点"<<i+1<<"tempLast"<<tempLast;
            if(tempCur!=tempLast)
            {
                if(tempCur==1)
                    scrollAddGroupBox(i+1);
                else
                    scrollDelateGroupBox(i+1);
            }
        }
        g_everyNodeIsChecked_Last=g_everyNodeIsChecked;
    }

    //    int j=0;
    //    if(g_setCurSign)
    //    {
    //        if(tempLast)
    //        {
    //            scrollAddGroupBox(i+1);
    //            g_TreeGroupOnline->child(j)->setCheckState(0,Qt::Checked);//子节点被选中
    //            //ui->treeWidget->setCurrentItem(g_TreeGroupOnline->child(j));
    //            //会进入信号槽，添加一个g_everyNodeIsChecked改变
    //            j++;
    //        }
    //        if(i==MAX_NODE_NUM-1)
    //            g_setCurSign=0;
    //    }

}

void IOStatus::initScrollLayout()
{
    this->g_GroupBoxVLayout= new QVBoxLayout(this);//上下垂直布局
    this->g_GroupBoxVLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);

    QWidget *groupBoxWidget= new QWidget(this);
    groupBoxWidget->setMinimumSize(80,30);
    groupBoxWidget->setMaximumSize(80,30);

    groupBoxWidget->setLayout(this->g_GroupBoxVLayout);
    ui->scrollArea->setWidget(groupBoxWidget);
}

void IOStatus::treeWidgetUpdate(int curNode)
{
    QString nameStr= QString(QObject::tr("%1号节点"));

    QTreeWidgetItem *item=new QTreeWidgetItem(g_TreeGroupOnline);
    item->setText(0,nameStr.arg(curNode));
    item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    item->setCheckState(0,Qt::Unchecked);
    g_TreeGroupOnline->addChild(item);
}

void IOStatus::getOnlineNode()
{
    ui->treeWidget->clear();

    g_TreeGroupOnline=new QTreeWidgetItem(ui->treeWidget);
    g_TreeGroupOnline->setText(0,QObject::tr("在线节点"));
    g_TreeGroupOnline->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    g_TreeGroupOnline->setCheckState(0,Qt::Unchecked);

    for(int i=0;i<MAX_NODE_NUM;i++)
    {
        if(g_everyNodeOnline_Last&(1<<i))
        {
            treeWidgetUpdate(i+1);
        }
    }
    ui->treeWidget->expandAll(); //结点全部展开
    qDebug()<<"childCount:"<<g_TreeGroupOnline->childCount();

    g_TreeGroupOnline->child(0)->setCheckState(0,Qt::Checked);//第一个节点被勾选中
    ui->treeWidget->setCurrentItem(g_TreeGroupOnline->child(0));//第一个节点被选
    g_clickedNode=g_TreeGroupOnline->child(0)->text(0).left(1).toInt();
    ui->label_CurID->setText(QString::number(g_clickedNode));//int转string
    //ui->label_CurID->setText("null");
}

void IOStatus::treeItemClicked(QTreeWidgetItem *item)
{
    QString itemText=item->text(0);
    qDebug()<<"点击的itemText:"<<itemText;

    //点击的是父节点：”在线节点“
    if(item->parent()==0)
        return;

    if(itemText.length()>4)//10号节点及以上
        itemText=itemText.left(2);//取前面两位
    else
        itemText=itemText.left(1);//取前面一位
    ui->label_CurID->setText(itemText);
    g_clickedNode=itemText.toInt();
}

void IOStatus::treeItemChanged(QTreeWidgetItem *item)
{
    //选中时
    if(Qt::Checked==item->checkState(0))
    {
        //QTreeWidgetItem* parent=item->parent();
        int count=item->childCount();
        if(count>0)
        {
            for(int i=0;i<count;i++)
                item->child(i)->setCheckState(0,Qt::Checked);//子节点也被选中
        }
        else
            updateParentItem(item);//是子节点
    }
    else if(Qt::Unchecked==item->checkState(0))
    {
        int count=item->childCount();
        if(count>0)
        {
            for(int i=0;i<count;i++)
                item->child(i)->setCheckState(0,Qt::Unchecked);
        }
        else
            updateParentItem(item);
    }
}

void IOStatus::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem* parent=item->parent();
    if(parent==NULL)
        return;
    //选中的子节点个数
    int selectCount=0;
    int childCount=parent->childCount();
    for(int i=0;i<childCount;i++)
    {
        QTreeWidgetItem *childItem=parent->child(i);
        int curNodeNum;
        QString curNode=childItem->text(0);
        if(curNode.length()>4)//10号节点及以上
            curNodeNum=curNode.left(2).toInt();//取前面两位
        else
            curNodeNum=curNode.left(1).toInt();//取前面一位
        if(childItem->checkState(0)==Qt::Checked)
        {
            selectCount++;
            //qDebug()<<"选中子节点："<<curNodeNum;
            setbit(g_everyNodeIsChecked,curNodeNum-1);
        }
        else
        {
            //qDebug()<<"没有选中子节点："<<curNodeNum;
            clrbit(g_everyNodeIsChecked,curNodeNum-1);
        }
    }
    if(selectCount<=0)
        parent->setCheckState(0,Qt::Unchecked);//选中状态
    else if(selectCount>0 && selectCount<childCount)
        parent->setCheckState(0,Qt::PartiallyChecked);//部分选中状态
    else if(selectCount==childCount)
        parent->setCheckState(0,Qt::Checked);//未选中状态
}

void IOStatus::scrollAddGroupBox(int numIO)
{
    QString groupBoxNameStr = QString(QObject::tr("%1号节点"));
    groupBox[numIO-1].newBox=new QGroupBox(groupBoxNameStr.arg(numIO));

    QWidget* checkBoxWidget = new QWidget(this);
    checkBoxWidget->setMinimumSize(80,30);
    checkBoxWidget->setMaximumSize(80,30);
    QVBoxLayout *checkBoxVLayout= new QVBoxLayout(this);//垂直布局
    checkBoxVLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    QCheckBox *checkBox;
    QString nameStr;
    QHBoxLayout *checkBoxHLayout;//水平布局
    checkBoxHLayout = new QHBoxLayout(this);
    checkBoxHLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);
    nameStr= QString("IN%1");
    for (int i=1; i<=8; ++i)
    {
        checkBox= new QCheckBox(nameStr.arg(i));
        checkBox->setObjectName(nameStr.arg(i));
        checkBox->setEnabled(0);
        checkBoxHLayout->addWidget(checkBox);
    }
    checkBoxVLayout->addLayout(checkBoxHLayout);//增加第一行输入口
    checkBoxHLayout = new QHBoxLayout(this);
    checkBoxHLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);
    nameStr= QString("OUT%1");
    for (int i=1; i<=8; ++i)
    {
        checkBox= new QCheckBox(nameStr.arg(i));
        checkBox->setObjectName(nameStr.arg(i));
        checkBoxHLayout->addWidget(checkBox);
    }
    checkBoxVLayout->addLayout(checkBoxHLayout);//增加第二行输出口
    checkBoxWidget->setLayout(checkBoxVLayout);
    checkBoxVLayout->addWidget(checkBoxWidget);
    groupBox[numIO-1].newBox->setLayout(checkBoxVLayout);

    this->g_GroupBoxVLayout->addWidget(groupBox[numIO-1].newBox);//垂直布局
}

void IOStatus::scrollDelateGroupBox(int numIO)
{
    this->g_GroupBoxVLayout->removeWidget(groupBox[numIO-1].newBox);//垂直布局
    delete groupBox[numIO-1].newBox;
}

void IOStatus::on_pb_SetCur_clicked()
{
    QString tempStr=ui->lineEdit->text();
    for(int i=0;i<tempStr.length();i++)
    {
        if(!(tempStr[i]>='0' && tempStr[i]<='9'))
        {
            QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("命名不规范，只能是1~16的整数！"));
            mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
            mBox.exec();
            ui->lineEdit->setText("");
            return;
        }
    }
    int tempInt=tempStr.toInt();
    if(tempInt>16||tempInt<1)
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("命名不规范，只能是1~16的整数！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
        ui->lineEdit->setText("");
        return;
    }
    if(g_everyNodeOnline&(1<<(tempInt-1)))
    {
        QMessageBox mBox(QMessageBox::Warning,"",QObject::tr("已存在同名节点，请重新修改！"));
        mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
        mBox.exec();
        ui->lineEdit->setText("");
        return;//有重复
    }

    clrbit(g_everyNodeOnline,g_clickedNode-1);//原来的位置0
    setbit(g_everyNodeOnline,tempInt-1);//新位置1

    scrollDelateGroupBox(g_clickedNode);

    //    g_setCurSign=1;
    //    clrbit(g_everyNodeIsChecked_Last,g_clickedNode-1);//原来的位置0
    //    setbit(g_everyNodeIsChecked_Last,temp-1);//新位置1
    QMessageBox mBox(QMessageBox::Information,"",QObject::tr("修改成功，请重启该扩展卡！"));
    mBox.addButton(QObject::tr("确定"),QMessageBox::AcceptRole);
    mBox.exec();

    ui->lineEdit->setText("");
}

void IOStatus::on_pb_StartCur_clicked()
{

}

void IOStatus::on_pb_StopCur_clicked()
{

}

void IOStatus::on_pb_ResetCur_clicked()
{

}

void IOStatus::on_pb_StartAll_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.command = 1;
    AMC4030::pComTimerWork->ComThrConPara.NMTManager = 1;
    //    if(!timer_IO->isActive())
    //        timer_IO->start(1000);
}

void IOStatus::on_pb_StopAll_clicked()
{
    AMC4030::pComTimerWork->ComThrConPara.command = 2;
    AMC4030::pComTimerWork->ComThrConPara.NMTManager = 1;
    //timer_IO->stop();
}

void IOStatus::on_pb_ResetAll_clicked()
{

}

//测试使用，修改在线节点
void IOStatus::on_pushButton_clicked()
{
    g_everyNodeOnline=ui->lineEdit_2->text().toInt();
}
