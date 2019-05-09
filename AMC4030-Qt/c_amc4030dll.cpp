#include "c_amc4030dll.h"

#include <QLibrary>
#include <QMessageBox>
#include <QDebug>

C_AMC4030DLL AMC4030_DLL;//类实例化一个对象

C_AMC4030DLL::C_AMC4030DLL()
{
    QLibrary mylib("AMC4030.dll");   //声明所用到的dll文件
    mylib.load();
    if(mylib.load())//如果dll正确加载
    {   //援引接口函数
        p_SetComType = (Fun_SetComType)mylib.resolve("COM_API_SetComType");
        p_OpenLink = (Fun_OpenLink)mylib.resolve("COM_API_OpenLink");
        p_GetMachineStatus = (Fun_GetMachineStatus)mylib.resolve("COM_API_GetMachineStatus");

        p_ReadFileData = (Fun_ReadFileData)mylib.resolve("COM_API_ReadFileData");//不使用
        p_WriteFileData = (Fun_WriteFileData)mylib.resolve("COM_API_WriteFileData");//不使用

        p_Jog = (Fun_Jog)mylib.resolve("COM_API_Jog");
        p_Home = (Fun_Home)mylib.resolve("COM_API_Home");
        p_StopAxis = (Fun_StopAxis)mylib.resolve("COM_API_StopAxis");
        p_StopAll = (Fun_StopAll)mylib.resolve("COM_API_StopAll");
        p_SetOutputBit = (Fun_SetOutputBit)mylib.resolve("COM_API_SetOutputBit");
        p_GetLastError = (Fun_GetLastError)mylib.resolve("COM_API_GetLastError");//不使用
        p_DownloadSystemCfg = (Fun_DowloadSystemCfg)mylib.resolve("COM_API_DowloadSystemCfg");
        p_UploadSystemCfg = (Fun_UploadSystemCfg)mylib.resolve("COM_API_UploadSystemCfg");

        p_DownloadFile = (Fun_DownloadFile)mylib.resolve("COM_API_DowloadFile");//没公开
        p_SendData = (Fun_SendData)mylib.resolve("COM_API_SendData");
        p_ReadData = (Fun_ReadData)mylib.resolve("COM_API_ReadData");//不使用

        p_StartAutoRun = (Fun_StartAutoRun)mylib.resolve("COM_API_StartAutoRun");//没公开

        p_GetFileName = (Fun_GetFileName)mylib.resolve("COM_API_GetFileName");//获取卡内程序文件名
        p_DeleteFile = (Fun_DeleteFile)mylib.resolve("COM_API_DeleteFile");//删除卡内文件
        p_NMTManager = (Fun_NMT_Manager_Node)mylib.resolve("COM_API_NMT_Manager_Node");
    }
    else
        QMessageBox::warning(NULL,"", QObject::tr("DLL 文件没有找到！"));
}

C_AMC4030DLL::~C_AMC4030DLL()
{

}

int C_AMC4030DLL::Q_SetComType(int nType)
{
    if(p_SetComType)
        return p_SetComType(nType);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_OpenLink(int nID,int nBound)
{
    if(p_OpenLink)
        return p_OpenLink(nID,nBound);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_GetMachineStatus(unsigned char* unStatus)
{
    if(p_GetMachineStatus)
        return p_GetMachineStatus(unStatus);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput)
{
    if(p_ReadFileData)
        return p_ReadFileData(nSrc,StartAdd,len,pOutput);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput)
{
    if(p_WriteFileData)
        return p_WriteFileData(nSrc,StartAdd,len,pInput);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_Jog(int nAxis,float fDis,float Speed)
{
    if(p_Jog)
        return p_Jog(nAxis,fDis,Speed);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
    if(p_Home)
        return p_Home(nXAxisSet,nYAxisSet,nZAxisSet);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
    if(p_StopAxis)
        return p_StopAxis(nXAxisSet,nYAxisSet,nZAxisSet);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_StopAll()
{
    if(p_StopAll)
        return p_StopAll();
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_SetOutputBit(int OutputID,int nStatus)
{
    if(p_SetOutputBit)
        return p_SetOutputBit(OutputID,nStatus);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_GetLastError(unsigned int* dwErr)
{
    if(p_GetLastError)
        return p_GetLastError(dwErr);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_DownloadSystemCfg(char* iniPath)
{
    if(p_DownloadSystemCfg)
        return p_DownloadSystemCfg(iniPath);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_UploadSystemCfg(char* iniPath)
{
    if(p_UploadSystemCfg)
        return p_UploadSystemCfg(iniPath);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_DownloadFile(char* szPath,int nType,int ShowProcess)
{
    if(p_DownloadFile)
        return p_DownloadFile(szPath,nType,ShowProcess);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_SendData(int nLen,unsigned char* pData)
{
    if(p_SendData)
        return p_SendData(nLen,pData);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_ReadData(int nLen,unsigned char* pInput,unsigned char* pOutput)
{
    if(p_ReadData)
        return p_ReadData(nLen,pInput,pOutput);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_StartAutoRun(int nType,int nID,char* FileName,int Len,int isRunOnTime)
{
    if(p_StartAutoRun)
        return p_StartAutoRun(nType,nID,FileName,Len,isRunOnTime);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_GetFileName(unsigned char* fileinfo)
{
    if(p_GetFileName)
        return p_GetFileName(fileinfo);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_DeleteFile(char* filename, int Len)
{
    if(p_DeleteFile)
        return p_DeleteFile(filename, Len);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}

int C_AMC4030DLL::Q_NMTManager(int command)
{
    if(p_NMTManager)
        return p_NMTManager(command);
    else
    {
        qDebug()<<"新建dll类里的该函数没有正确调用";
        QMessageBox::warning(NULL,"","新建dll类里的该函数没有正确调用");
    }
    return -10;
}


