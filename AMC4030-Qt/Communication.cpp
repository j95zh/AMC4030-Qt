#include "Communication.h"

#include "c_amc4030dll.h"
#include <QDebug>
#include <synchapi.h> //用于Sleep()

struct Communication::_COMTHRCONPARA_ Communication::ComThrConPara;

Communication::Communication()
{
    ComThrConPara.loopNow=1;//循环标志位
    ComThrConPara.autoRun=0;
    ComThrConPara.xHome=0;
    ComThrConPara.yHome=0;
    ComThrConPara.zHome=0;
    ComThrConPara.stopAll=0;
    ComThrConPara.xJogL=0;
    ComThrConPara.xJogR=0;
    ComThrConPara.xStop=0;
    ComThrConPara.yJogL=0;
    ComThrConPara.yJogR=0;
    ComThrConPara.yStop=0;
    ComThrConPara.zJogL=0;
    ComThrConPara.zJogR=0;
    ComThrConPara.zStop=0;
    ComThrConPara.SetOutputBit=0;
}

Communication::~Communication()
{
}
void Communication::readComDataSlot()
{
    while(ComThrConPara.loopNow){
        Sleep(5);//必须加sleep(),不然直接放在while里面一直死循环，cpu使用率很高
        ComThrConPara.LinkStatus=AMC4030_DLL.Q_OpenLink(5, 115200);
        if(ComThrConPara.LinkStatus)
        {
            ComThrConPara.result_GMS = AMC4030_DLL.Q_GetMachineStatus((unsigned char *)&ComThrConPara.comMachineStatus);
            if(ComThrConPara.autoRun){
                AMC4030_DLL.Q_StartAutoRun(2, 1, ComThrConPara.filename, ComThrConPara.NameSize, ComThrConPara.isRunOnTime);
                ComThrConPara.autoRun=0;
            }
            //回零
            if(ComThrConPara.xHome){
                AMC4030_DLL.Q_Home(1, 0, 0);
                ComThrConPara.xHome=0;
            }
            if(ComThrConPara.yHome){
                AMC4030_DLL.Q_Home(0, 1, 0);
                ComThrConPara.yHome=0;
            }
            if(ComThrConPara.zHome){
                AMC4030_DLL.Q_Home(0, 0, 1);
                ComThrConPara.zHome=0;
            }
            //停止所有轴
            if(ComThrConPara.stopAll){
                AMC4030_DLL.Q_StopAll();
                ComThrConPara.stopAll=0;
            }
            //点动
            if(ComThrConPara.xJogL){
                AMC4030_DLL.Q_Jog(0, -1*ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.xJogL=0;
            }
            if(ComThrConPara.xJogR){
                AMC4030_DLL.Q_Jog(0, ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.xJogR=0;
            }
            if(ComThrConPara.xStop){
                AMC4030_DLL.Q_StopAxis(1, 0, 0);
                ComThrConPara.xStop=0;
            }
            if(ComThrConPara.yJogL){
                AMC4030_DLL.Q_Jog(1, -1*ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.yJogL=0;
            }
            if(ComThrConPara.yJogR){
                AMC4030_DLL.Q_Jog(1, ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.yJogR=0;
            }
            if(ComThrConPara.yStop){
                AMC4030_DLL.Q_StopAxis(0, 1, 0);
                ComThrConPara.yStop=0;
            }
            if(ComThrConPara.zJogL){
                AMC4030_DLL.Q_Jog(2, -1*ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.zJogL=0;
            }
            if(ComThrConPara.zJogR){
                AMC4030_DLL.Q_Jog(2, ComThrConPara.manuDis, ComThrConPara.manuSpeed);
                ComThrConPara.zJogR=0;
            }
            if(ComThrConPara.zStop){
                AMC4030_DLL.Q_StopAxis(0, 0, 1);
                ComThrConPara.zStop=0;
            }
            //设置IO口
            if(ComThrConPara.SetOutputBit){
                AMC4030_DLL.Q_SetOutputBit(ComThrConPara.SetOutNum,ComThrConPara.SetOutStatus);
                ComThrConPara.SetOutputBit=0;
            }//获取控制卡内文件名
            if(ComThrConPara.GetFileName){
                AMC4030_DLL.Q_GetFileName((unsigned char *)&ComThrConPara.comFileInfo);
                ComThrConPara.GetFileName = 0;
            }//删除控制卡内文件
            if(ComThrConPara.DeleteFile){
               AMC4030_DLL.Q_DeleteFile(ComThrConPara.filename, ComThrConPara.NameSize);
               ComThrConPara.DeleteFile = 0;
            }//nmt从节点管理
            if(ComThrConPara.NMTManager){
               AMC4030_DLL.Q_NMTManager(ComThrConPara.command);
               qDebug()<<ComThrConPara.command;
               ComThrConPara.NMTManager = 0;
            }
        }
    }
}
