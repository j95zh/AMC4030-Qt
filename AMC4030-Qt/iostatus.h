#ifndef IOSTATUS_H
#define IOSTATUS_H

#include <QDialog>

#include <QTimer>
#include <QCloseEvent>
#include <QDebug>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

#define MAX_NODE_NUM 16

//指定的某一位数置1
#define setbit(x,y)  (x)|=(1<<(y))
//指定的某一位数置0
#define clrbit(x,y)  (x)&=~(1<<(y))
//指定的某一位数取反
#define reversebit(x,y)  (x)^=(1<<(y))
//获取的某一位的值
#define getbit(x,y)   ((x) >> (y)&1)

namespace Ui {
class IOStatus;
}

class IOStatus : public QDialog
{
    Q_OBJECT

public:
    explicit IOStatus(QWidget *parent = 0);
    ~IOStatus();
    QTreeWidgetItem* g_TreeGroupOnline;
private slots:
    void refreshStatus();
    void treeItemChanged(QTreeWidgetItem *item);
    void treeItemClicked(QTreeWidgetItem *);

    void on_pb_SetCur_clicked();

    void on_pb_StartCur_clicked();

    void on_pb_StopCur_clicked();

    void on_pb_ResetCur_clicked();

    void on_pb_StartAll_clicked();

    void on_pb_StopAll_clicked();

    void on_pb_ResetAll_clicked();

    void on_pushButton_clicked();

private:
    Ui::IOStatus *ui;

    QTimer *timer_IO;

    QVBoxLayout* g_GroupBoxVLayout;
    int g_setCurSign;//修改节点号的标志
    unsigned short int g_everyNodeOnline_Last;//16位，某一位为1则表示该节点在线
    unsigned short int g_everyNodeOnline;//16位，某一位为1则表示该节点在线
    unsigned short int g_everyNodeIsChecked_Last;//16位，某一位为1则表示该节点被选中
    unsigned short int g_everyNodeIsChecked;//16位，某一位为1则表示该节点被选中
    int g_clickedNode;
    struct{
        QGroupBox *newBox;
        int nodeOnlineStatus;
    }groupBox[MAX_NODE_NUM];
    void updateParentItem(QTreeWidgetItem *item);
    void scrollAddGroupBox(int numIO);
    void scrollDelateGroupBox(int numIO);
    void treeWidgetUpdate(int curNode);
    void initScrollLayout();
    void getOnlineNode();

signals:
    deleteIO_Dialog();
};

#endif // IOSTATUS_H
