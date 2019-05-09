#ifndef C_AMC4030DLL_H
#define C_AMC4030DLL_H

//dll函数接口定义
typedef int (*Fun_SetComType)(int);//定义设置通讯类型的函数指针
typedef int (*Fun_OpenLink)(int,int);//定义打开连接的函数指针
typedef int (*Fun_GetMachineStatus)(unsigned char*);//定义获取机器状态字的函数指针

typedef int (*Fun_ReadFileData)(int,int,int,unsigned char*);
typedef int (*Fun_WriteFileData)(int,int,int,unsigned char*);

typedef int (*Fun_Jog)(int,float,float);//定义轴点动的函数指针
typedef int (*Fun_Home)(int,int,int);//定义回零运动的函数指针
typedef int (*Fun_StopAxis)(int,int,int);//定义某一轴停止的函数指针
typedef int (*Fun_StopAll)();//定义所有轴停止的函数指针
typedef int (*Fun_SetOutputBit)(int,int);//定义输出口状态选择的函数指针

typedef int (*Fun_GetLastError)(unsigned int*);//
typedef int (*Fun_DowloadSystemCfg)(char*);//
typedef int (*Fun_UploadSystemCfg)(char*);//
typedef int (*Fun_DownloadFile)(char* ,int,int);//定义把程序的二进制文件下载到卡里的函数指针、定义固件升级的函数指针
typedef int (*Fun_SendData)(int,unsigned char*);
typedef int (*Fun_ReadData)(int,unsigned char*,unsigned char*);

typedef int (*Fun_StartAutoRun)(int,int,char*,int,int);//定义启动自动控制的函数指针

typedef int (*Fun_GetFileName)(unsigned char*);//定义获取控制卡内文件名的函数指针
typedef int (*Fun_DeleteFile)(char*, int);//定义删除卡内文件名函数指针
typedef int (*Fun_NMT_Manager_Node)(int);//NMT从节点管理

class C_AMC4030DLL
{
public:
    C_AMC4030DLL();
    ~C_AMC4030DLL();

    Fun_SetComType p_SetComType;
    Fun_OpenLink p_OpenLink;
    Fun_GetMachineStatus p_GetMachineStatus;

    Fun_ReadFileData p_ReadFileData;
    Fun_WriteFileData p_WriteFileData;

    Fun_Jog p_Jog;
    Fun_Home p_Home;
    Fun_StopAxis p_StopAxis;
    Fun_StopAll p_StopAll;
    Fun_SetOutputBit p_SetOutputBit;
    Fun_GetLastError p_GetLastError;
    Fun_DowloadSystemCfg p_DownloadSystemCfg;
    Fun_UploadSystemCfg p_UploadSystemCfg;
    Fun_DownloadFile p_DownloadFile;
    Fun_SendData p_SendData;
    Fun_ReadData p_ReadData;

    Fun_StartAutoRun p_StartAutoRun;

    Fun_GetFileName p_GetFileName;
    Fun_DeleteFile p_DeleteFile;
    Fun_NMT_Manager_Node p_NMTManager;

    int	Q_SetComType(int nType);//设置通讯类型
    int	Q_OpenLink(int nID,int nBound);//打开连接。
    int	Q_GetMachineStatus(unsigned char* unStatus);//获取机器状态字。

    int	Q_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput);
    int	Q_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput);

    int	Q_Jog(int nAxis,float fDis,float Speed);
    int	Q_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet);
    int	Q_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet);
    int	Q_StopAll();
    int	Q_SetOutputBit(int OutputID,int nStatus);
    int	Q_GetLastError(unsigned int* dwErr);//没有使用
    int	Q_DownloadSystemCfg(char* iniPath);
    int	Q_UploadSystemCfg(char* iniPath);
    int Q_DownloadFile(char* szPath,int nType,int ShowProcess);

    int	Q_SendData(int nLen,unsigned char* pData);
    int	Q_ReadData(int nLen,unsigned char* pInput,unsigned char* pOutput);//没有使用

    int Q_StartAutoRun(int nType, int nID, char *FileName, int Len, int isRunOnTime);//2019年2月27日增加FileName和Len两个参数，匹配DLL中的根据文件名开启自动控制功能

    int Q_GetFileName(unsigned char* fileinfo);//获取控制卡内程序文件名
    int Q_DeleteFile(char *filename, int Len);//删除卡内程序
    int Q_NMTManager(int command);//nmt从节点管理

};
extern C_AMC4030DLL  AMC4030_DLL;

#endif // C_AMC4030DLL_H
