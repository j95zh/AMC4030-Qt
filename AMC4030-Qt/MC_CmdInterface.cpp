#include "newprogrameditor.h"
#include "MC_CmdInterface.h"
#include "CmdFile.h"

#include <QFile>
#include <QByteArray>
#include <iostream>
#include <QtCore/QCoreApplication>

MC_CALLBACK MC_CMD_WriteBegin(QString fileName, QString file)//指令开始
{
    bool bRtn;
    bRtn = g_tCmdFile.OpenFileForWrite(&fileName, &file);
    return bRtn;
}

MC_CALLBACK MC_CMD_End()//指令结束
{
    g_tCmdFile.CloseFile();
    return 0;
}

//////////////////////////// 系统操作 ////////////////////////////////
//停止
MC_CALLBACK MC_CMD_StopAll()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_STOP_ALL;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//启动
MC_CALLBACK MC_CMD_Start()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_START;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//暂停
MC_CALLBACK MC_CMD_Pause()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_PAUSE;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//恢复
MC_CALLBACK MC_CMD_Resume()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_RESUME;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//延时
MC_CALLBACK MC_CMD_DelayTime(int ms)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DELAY_TIME;
    dwCmd[1] = ms;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//等待电机完成
MC_CALLBACK MC_CMD_CheckMotorDone(int XAxis, int YAxis, int ZAxis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_CHECK_MOTOR_DONE;
    dwCmd[1] = XAxis;
    dwCmd[2] = YAxis;
    dwCmd[3] = ZAxis;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//停止电机运动
MC_CALLBACK MC_CMD_StopNamedMotor(int XAxis, int YAxis, int ZAxis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_STOP_NAMED_MOTOR;
    dwCmd[1] = XAxis;
    dwCmd[2] = YAxis;
    dwCmd[3] = ZAxis;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}
//长等待
MC_CALLBACK MC_CMD_Waiting()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_WAITING;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

////////////////////////   流程控制  ////////////////////////////
//程序行间跳转
MC_CALLBACK MC_CMD_ProgramJump(int Row)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_PROGRAM_JUMP;
    dwCmd[1] = Row;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//程序循环
MC_CALLBACK MC_CMD_ProgramLoop(int Row,int Times)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_PROGRAM_LOOP;
    dwCmd[1] = Row;
    dwCmd[2] = Times;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//输入跳转
MC_CALLBACK MC_CMD_InputJump(int Input,int Level,int Row)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_INPUT_JUMP;
    dwCmd[1] = Input;
    dwCmd[2] = Level>0?1:0;
    dwCmd[3] = Row;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//开启输入中断
MC_CALLBACK MC_CMD_OpenInputInterrupt(int Input,int Level,int Row)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_OPEN_INPUT_INT;
    dwCmd[1] = Input;
    dwCmd[2] = Level>0?1:0;
    dwCmd[3] = Row;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//关闭输入中断
MC_CALLBACK MC_CMD_CloseInputInterrupt(int Input,int Level)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_CLOSE_INPUT_INT;
    dwCmd[1] = Input;
    dwCmd[2] = Level>0?1:0;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

/*
//子程序调用
MC_CALLBACK MC_CMD_SubroutineCall(int Row)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SUB_CALL;
    dwCmd[1] = Row;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//子程序返回
MC_CALLBACK MC_CMD_SubroutineReturn()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SUB_CALL_RETURN;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//开启定时中断
MC_CALLBACK MC_CMD_OpenTimerInterrupt(int Timer,int ms,int Row)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_OPEN_TIMER_INT;
    dwCmd[1] = Timer;
    dwCmd[2] = ms;
    dwCmd[3] = Row;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//关闭定时中断
MC_CALLBACK MC_CMD_CloseTimerInterrupt()
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_CLOSE_TIMER_INT;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}
*/

////////////////////////  输出口操作 /////////////////////////////
//输出口设置
MC_CALLBACK MC_CMD_SetOutputBit(int Output,int Level)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SET_OUTPUT_BIT;
    dwCmd[1] = Output;
    dwCmd[2] = Level>0?1:0;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

////////////////////////// 回零运动  ////////////////////////////
//设置回零速度
MC_CALLBACK MC_CMD_SetHomeSpeed(float XSpeed, float YSpeed, float ZSpeed)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SET_HOME_SPEED;
    dwCmd[1] = *(LPDWORD)&XSpeed;//直接赋值会导致数据丢失，故取其内存模型
    dwCmd[2] = *(LPDWORD)&YSpeed;
    dwCmd[3] = *(LPDWORD)&ZSpeed;
//如果只设置了X轴的回零速度为150，则会向二进制文件写入4*sizeof(DWORD)=4*4=16字节
    //形式为04 01 00 03 00 00 16 43 00 00 00 00 00 00 00 00
    //其中00 00 16 43为X轴速度 小端模式转换前：0X43160000，该数为浮点数通过特有的规则转换成10进制为150
    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//启动回零
MC_CALLBACK MC_CMD_StartHome(int XAxis,int YAxis,int ZAxis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_START_HOME;
    dwCmd[1] = XAxis;
    dwCmd[2] = YAxis;
    dwCmd[3] = ZAxis;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//设置回零速度与启动回零合并
MC_CALLBACK MC_CMD_SetAndStartHome(float XSpeed, float YSpeed, float ZSpeed)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SET_AND_START_HOME;
    dwCmd[1] = *(LPDWORD)&XSpeed;//直接赋值会导致数据丢失，故取其内存模型
    dwCmd[2] = *(LPDWORD)&YSpeed;
    dwCmd[3] = *(LPDWORD)&ZSpeed;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//////////////////////// 直线点位运动 ////////////////////////////
//设置点位速度
MC_CALLBACK MC_CMD_SetPointSpeed(float Speed,float Acc)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SET_PMOV_SPEED;
    dwCmd[1] = *(PDWORD)&Speed;
    dwCmd[2] = *(PDWORD)&Acc;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//三轴相对运动
MC_CALLBACK MC_CMD_ThreeAxisRelativeMotion(float XDis,float YDis,float ZDis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_PMOV;
    dwCmd[1] = *(PDWORD)&XDis;
    dwCmd[2] = *(PDWORD)&YDis;
    dwCmd[3] = *(PDWORD)&ZDis;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//绝对运动
MC_CALLBACK MC_CMD_AbsoluteMotion(int nAxis,float XDis,float YDis,float ZDis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_ABS_PMOV;
    dwCmd[1] = nAxis;
    dwCmd[2] = *(PDWORD)&XDis;
    dwCmd[3] = *(PDWORD)&YDis;
    dwCmd[4] = *(PDWORD)&ZDis;
    //0x04000105&0xff000000==0000 0100 0000 0000 0000 0001 0000 0101 & 0xff000000==0x04000000
    //向右移24位，再加1，结果为5
    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//////////////////////// 独立插补运动 ///////////////////////////
//设置独立运动速度
MC_CALLBACK MC_CMD_SetIndependentSpeed(int nAxis,float Speed,float Acc)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_SET_ALONE_PMOV_SPEED;
    dwCmd[1] = nAxis;
    dwCmd[2] = *(PDWORD)&Speed;
    dwCmd[3] = *(PDWORD)&Acc;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//三轴独立相对插补
MC_CALLBACK MC_CMD_IndependentMotion(float XDis,float YDis,float ZDis)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_ALONE_PMOV;
    dwCmd[1] = *(PDWORD)&XDis;
    dwCmd[2] = *(PDWORD)&YDis;
    dwCmd[3] = *(PDWORD)&ZDis;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

/////////////////////////DM寄存器///////////////////////////////////
//DM赋值
MC_CALLBACK MC_CMD_DM_Assignment(int reg,float num)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_ASSIGNMENT;
    dwCmd[1] = reg;
    dwCmd[2] = *(PDWORD)&num;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM加常数
MC_CALLBACK MC_CMD_DM_AddNum(int reg,float num)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_ADD_NUM;
    dwCmd[1] = reg;
    dwCmd[2] = *(PDWORD)&num;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM加DM
MC_CALLBACK MC_CMD_DM_AddDM(int reg1,int reg2)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_ADD_DM;
    dwCmd[1] = reg1;
    dwCmd[2] = reg2;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM延时
MC_CALLBACK MC_CMD_DM_Delay(int reg)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_DELAY;
    dwCmd[1] = reg;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM作程序循环
MC_CALLBACK MC_CMD_DM_ProgramLoop(int num,int reg)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_PROGRAM_JUMP;
    dwCmd[1] = num;
    dwCmd[2] = reg;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM作回零
MC_CALLBACK MC_CMD_DM_SetAndStartHome(int regx,int regy,int regz)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_SET_AND_START_HOME;
    dwCmd[1] = regx;
    dwCmd[2] = regy;
    dwCmd[3] = regz;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM设置点位速度
MC_CALLBACK MC_CMD_DM_PMOV_Speed(int reg1,int reg2)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_PMOV_SPEED;
    dwCmd[1] = reg1;
    dwCmd[2] = reg2;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM作相对运动
MC_CALLBACK MC_CMD_DM_PMOV(int regx,int regy,int regz)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_PMOV;
    dwCmd[1] = regx;
    dwCmd[2] = regy;
    dwCmd[3] = regz;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}

//DM作独立运动
MC_CALLBACK MC_CMD_DM_ABS_PMOV(int nAxis,int regx,int regy,int regz)
{
    DWORD dwCmd[50]={0};
    dwCmd[0] = CMD_DM_ABS_PMOV;
    dwCmd[1] = nAxis;
    dwCmd[2] = regx;
    dwCmd[3] = regy;
    dwCmd[4] = regz;

    g_tCmdFile.WriteData(((dwCmd[0]&0xff000000)>>24)+1,dwCmd);
    return 0;
}
