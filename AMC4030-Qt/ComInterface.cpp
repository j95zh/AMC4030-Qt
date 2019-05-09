#include "ComInterface.h"
#include "Commdefine.h"
#include "Transfer.h"
//设置通讯类型
CALLBACK_DEF	COM_API_SetComType(int nType)
{
	return	g_tTranfer.SetCommType(nType);
}
//打开连接。可重复调用
//返回值：0 -- 成功；
//        -1 --失败。
CALLBACK_DEF	COM_API_OpenLink(int nID,int nBound,const QString &name)
{
    return g_tTranfer.TransferStandby(nID,nBound,name);
}
//获取机器状态字。
CALLBACK_DEF	COM_API_GetMachineStatus(unsigned char* unStatus)
{
	int nRtn;
	unsigned short cmd = COM_GET_MACHINE_STATUS;
	unsigned char buf[50] = {0};
	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	nRtn = g_tTranfer.ReadUniversalData(2,(char*)buf,(char*)unStatus);
	return nRtn;
}
//读文件数据
CALLBACK_DEF	COM_API_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput)
{
	int nRtn;
	unsigned short cmd = COM_READ_FILE_DATA;
	unsigned char buf[50] = {0};
	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = nSrc;
	buf[3] = StartAdd & 0xff;
	buf[4] = (StartAdd>>8)&0xff;

	buf[5] = len & 0xff;
	buf[6] = (len>>8)&0xff;

	nRtn = g_tTranfer.ReadUniversalData(7,(char*)buf,(char*)pOutput);
	return nRtn;

}
//写文件数据
//最大传输字节500；
CALLBACK_DEF	COM_API_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput)
{
	int nRtn;
	unsigned short cmd = COM_WRITE_FILE_DATA;
	unsigned char buf[1300] = {0};
	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = nSrc;
	buf[3] = StartAdd & 0xff;
	buf[4] = (StartAdd>>8)&0xff;

	buf[5] = len & 0xff;
	buf[6] = (len>>8)&0xff;
	memcpy(&buf[7],pInput,len);
	nRtn = g_tTranfer.SendUniversalData(7+len,(char*)buf);
	return nRtn;
}
//轴点动
CALLBACK_DEF	COM_API_Jog(int nAxis,float fDis,float Speed)
{
	int nRtn;
	unsigned short cmd = COM_AXIS_JOG;
	unsigned char buf[50] = {0};

	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = nAxis;
	memcpy(&buf[3],&fDis,4);
	memcpy(&buf[7],&Speed,4);
	nRtn = g_tTranfer.SendUniversalData(11,(char*)buf);
	return nRtn;

}
CALLBACK_DEF	COM_API_StopAll()
{
	int nRtn;
	unsigned short cmd = COM_STOP_ALL;
	unsigned char buf[50] = {0};

	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	nRtn = g_tTranfer.SendUniversalData(2,(char*)buf);
	return nRtn;
}
CALLBACK_DEF	COM_API_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
	int nRtn;
	unsigned char nSet = 0;
	if(nXAxisSet>0)nSet |= 0x01;

	if(nYAxisSet>0)nSet |= 0x02;

	if(nZAxisSet>0)nSet |= 0x04;

	unsigned short cmd = COM_STOP_SP_AXIS;
	unsigned char buf[50] = {0};

	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = nSet;
	nRtn = g_tTranfer.SendUniversalData(3,(char*)buf);
	return nRtn;
}
//轴复位
//nXAxisSet -- 1:X轴复位；0：X轴不复位
//nYAxisSet -- 1:Y轴复位；0：Y轴不复位
//nZAxisSet -- 1:Z轴复位；0：Z轴不复位
CALLBACK_DEF	COM_API_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
	int nRtn;
	unsigned char nSet = 0;
	if(nXAxisSet>0)nSet |= 0x01;

	if(nYAxisSet>0)nSet |= 0x02;

	if(nZAxisSet>0)nSet |= 0x04;

	unsigned short cmd = COM_AXIS_HOME;
	unsigned char buf[50] = {0};

	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = nSet;
	nRtn = g_tTranfer.SendUniversalData(3,(char*)buf);
	return nRtn;
}
//设置输出口状态。
CALLBACK_DEF	COM_API_SetOutputBit(int OutputID,int nStatus)
{
	int nRtn;
	unsigned short cmd = COM_SET_OUTPUT_STATUS;
	unsigned char buf[50] = {0};

	buf[0] = cmd & 0xff;
	buf[1] = (cmd>>8) & 0xff;

	buf[2] = OutputID;
	buf[3] = nStatus>0?1:0;

	nRtn = g_tTranfer.SendUniversalData(4,(char*)buf);
	return nRtn;
}

CALLBACK_DEF	COM_API_GetLastError(unsigned int* dwErr)
{
	return g_tTranfer.m_dwLastError;
}


