#include "newsavefile.h"
#include "ui_newsavefile.h"

#include "amc4030.h"
#include "newprogrameditor.h"
#include "newmodifyname.h"

#include <QDebug>
#include <QMessageBox>
#include <QDir>

extern AMC4030 w;

newSaveFile::newSaveFile(QString name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newSaveFile)
{
    ui->setupUi(this);
    ui->label_3->setStyleSheet("color:Green;""font:20pt;");

    ui->label_2->setText(name + ".txt");
    //new_file_name=ui->label_2->text().left(ui->label_2->text().length()-4);//去掉ui->label_2->text()的后缀名“.txt”
    new_file_name= name;
}

newSaveFile::~newSaveFile()
{
    delete ui;
}

void newSaveFile::set_file_name(QString name)
{
    ui->label_2->setText(name);
}

void newSaveFile::on_pushButton_clicked()
{
    this->close();
}

void newSaveFile::on_Btn_ModifyName_clicked()
{
    //转到修改名字的界面
    newModifyName*dialog_MN=new newModifyName();
    dialog_MN->exec();

    if(!dialog_MN->New_FileName.isEmpty())
    {
        ui->label_2->setText(dialog_MN->New_FileName+".txt");
        new_file_name=dialog_MN->New_FileName;//把新的文件名传给共有变量，方便在newProgramEditor中调用

        delete dialog_MN;
    }
}

void newSaveFile::changeEvent(QEvent *e)    //重写的事件处理方法
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
