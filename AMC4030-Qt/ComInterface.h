#ifndef COM_INTERFACE_H_BY_TP_20170313
#define COM_INTERFACE_H_BY_TP_20170313
#include "qstring.h"
#define CALLBACK_DEF			int

CALLBACK_DEF	COM_API_SetComType(int nType);//设置通讯类型
CALLBACK_DEF	COM_API_OpenLink(int nID,int nBound,const QString &name);//打开连接。
CALLBACK_DEF	COM_API_GetMachineStatus(unsigned char* unStatus);//获取机器状态字。

CALLBACK_DEF	COM_API_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput);
CALLBACK_DEF	COM_API_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput);

CALLBACK_DEF	COM_API_Jog(int nAxis,float fDis,float Speed);
CALLBACK_DEF	COM_API_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet);
CALLBACK_DEF	COM_API_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet);
CALLBACK_DEF	COM_API_StopAll();	
CALLBACK_DEF	COM_API_SetOutputBit(int OutputID,int nStatus);
CALLBACK_DEF	COM_API_GetLastError(unsigned int* dwErr);

CALLBACK_DEF    COM_API_GetFileName(unsigned char* fileinfo);//获取控制卡内程序文件名
CALLBACK_DEF    COM_API_DeleteFile(unsigned char* filename, int Len);//删除控制卡内程序文件

#endif
