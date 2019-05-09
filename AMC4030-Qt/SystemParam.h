#ifndef SYSTEMPARAM_H_BY_TP_20170323
#define SYSTEMPARAM_H_BY_TP_20170323

#include "Commdefine.h"
/////////////////////////////////////////////////////////////
////////////////////////////系统参数结构体////////////////////
//参数模块:机器参数结构定
typedef struct _SYS_MACHINE_PARAM_SET
{
    float fTimerPeriod;                 //插补周期
    float fWorkPrecision;               //轨迹精度
    float fArcCheckPrecision;           //圆弧起终点检测精度
    float fMinLen;                      //小线段功能允许的最小长度
    float fMaxFeedSpeed;                //最大进给速度

    unsigned short int   nAccelType;    //加减速控制方式 0:T--1:S
    unsigned short int   nHomePowerOn;  //开机回零标志 //第 0 位  --1--开机自动回，0:不回

    float fMaxAccelSpeed;               //最大系统加速度,圆弧的向心加速、拐弯加速度。
    float fAccelSpeed;                  //加工加速度
    float fFastAccelSpeed;              //空程加速度
    float fJAccelSpeed;                 //加加（减）速度

    unsigned int nRsv[20];

} SYS_MACHINE_PARAM,*PSYS_MACHINE_PARAM;

//参数模块:轴参数设置结构定义
typedef struct _AXIS_PARAM_SET
{
    float   nPulseFactorUp;             //电子齿轮分子
    float   nPulseFactorDown;           //电子齿轮分母
    int	    nPulseLogic;                //脉冲逻辑，1:下降沿有效，0 上升沿有效。

    float fMaxSpeed;                    //最大速度
    float fMaxPos;                      //软限位最大位置

    int   nEnableBackLash;              //允许间隙补偿
    float fBackLashLen;                 //反向间隙
    float fBackLashSpeed;               //间隙补偿速度；mm/Min

    int   nHomeDir;                     //机床回零方向  1正；-1负
    float fHomeSpeed;                   //回零速度，第一次回原点的速度
    float fHomeCheckDis;                //回零检测长度,（一般电机转1圈以内的位移量）
    float fHomeZeroSpeed;               //粗定位速度，第一次回原点后，脱离原点信号的速度
    float fHomeOrgSpeed;                //零点检测速度，第二次回原点的速度
    float fHomePosOffset;               //零点位置偏移（反方向移动量）

    unsigned int nRsv[20];
} AXIS_PARAM,*PAXIS_PARAM;

typedef struct _SYS_PARAM_
{
    SYS_MACHINE_PARAM       MachineParam;
    AXIS_PARAM              tAxisParam[MAX_AXIS_NUM];
    unsigned int            dwRsv[100];//保留空间
}SYS_PARAM,*PSYS_PARAM;


extern SYS_PARAM		g_tSysParam;
#endif
