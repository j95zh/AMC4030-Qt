#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "Commdefine.h"
#include "SystemParam.h"

#include <QTime>
#include <QtCore>

class Communication : public QObject
{
    Q_OBJECT

public:
    Communication();
    ~Communication();
    static struct _COMTHRCONPARA_
    {
        MACHINE_STATUS comMachineStatus;//保存机器状态
        FILESYSTEM     comFileInfo;//保存控制卡内文件名信息
        int autoRun;
        int loopNow;//循环标志位
        int LinkStatus;//连接标志
        int result_GMS;//通信标志
        int xHome;
        int yHome;
        int zHome;
        int stopAll;
        float manuDis;
        float manuSpeed;
        int xJogL;
        int xJogR;
        int xStop;
        int yJogL;
        int yJogR;
        int yStop;
        int zJogL;
        int zJogR;
        int zStop;

        int SetOutputBit;
        int SetOutNum;
        int SetOutStatus;

        //2019年2月26日增加
        int GetFileName;
        char filename[8];
        int DeleteFile;
        int NameSize;
        int isRunOnTime;

        //2019年4月15日增加，canopen从节点管理
        int NMTManager;
        int command;
        
    }ComThrConPara;



public slots:

    void readComDataSlot();

private:

};

#endif // COMMUNICATION_H
