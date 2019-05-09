#ifndef TRANSFERPROTOCOL_H_BY_TP_20170323
#define TRANSFERPROTOCOL_H_BY_TP_20170323
#include "QserialPort.h"

#define ERROR_COMM_TIME_OUT			0xFFAA	//通讯超时
#define COMM_LAN						0
#define COMM_USB						1
#define COMM_UART						2

//通讯异常定义
#define COM_ERR_BUF_OUT				-10//接收到操过数据缓冲长度的数据
#define COM_ERR_PC_CHECK_SUM	    -11//PC端数据校验错误
#define COM_ERR_CARD_CHECK_SUM		-12//控制器端数据校验错误。
#define COM_CMD_ERR_NOT_CMD			0x01//控制卡端没找到命令。
#define	COM_CMD_ERR_CMD_IGNORE		0x02//控制卡端命令被忽略，达不到执行条件。


//传输协议类（福誉内部通讯协议）
class CTransferProtocol
{
private:
	int m_nTransferSetp;//
	int m_nTransferType;//传输类型。0：网络传输；1：USB传输，2:串口传输；
	char* m_pchInBuffer;
	int m_nRcvByteCnt;	//接收字节计数。
	char* m_pchOutBuffer;
	int m_nRevDone;
	int m_nSendByteNum;
	int m_nCommStatus;//通讯状态
	char  m_nErrorCode;//错误指令代码
	int m_nLogicId;//当前打开通讯的ID号。用于掉线自动重连。

public:
	CTransferProtocol();
	~CTransferProtocol();
    QSerialPort		m_cUart;
	int SendData();//发送数据协议
	int RecvData();//接收数据协议
    int InputData();//查询接收数据
	int Output();
	int Output(char chByte);
	int SendOneFrame(int nLen,char* pchInData,char* pchOutData);
	int DirectSendFrame(int nLen,char* pchInData);
	int DirectRcvFrame(int nLen,char* pchInData);
	int GetLastErrorCode();
	int GetCommStatus();//获取通讯状态。
	char*  GetOutputBuffer();
public:	
	int ReSet();
    int OpenLink(int nBunds,int nID,const QString &name);
	int CloseLink(int nID=0);
	int SetLinkType(int nType);//设置链接的硬件方式。
	int GetCurLinkStatus(int nType,int* num,int* nInfo);
	int GetClientInfo(int nTyep,int* nSn,int* nLogicID);

};

#endif
