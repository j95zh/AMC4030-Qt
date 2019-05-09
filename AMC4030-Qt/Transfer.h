#ifndef TRANSFER_H_BY_TP_20170323
#define TRANSFER_H_BY_TP_20170323
#include "TransferProtocol.h"
#define TRANSFER_DATA_MAX_LEN			532

class CTransfer
{
private:
	int				m_nOutBuffer[TRANSFER_DATA_MAX_LEN/4];//输出
	int				m_nInBuffer[TRANSFER_DATA_MAX_LEN/4];//输出buffer
	int				m_nSendByteNum;
public:
//	CModbusProtocol	   m_cModbus;传输协议类
	 CTransferProtocol m_cTransferProto;
     int          m_dwLastError;
	//通用读写命令。
	int SendUniversalData(int dwLen, char* pchData);
	int ReadUniversalData(int dwLen, char* pchDataIn,char* pchDataOut);
	int SendData();
	char* GetInBuffer();
//	int ClearFileCheckSum();
//	int GetFileCheckSum();
//	int SendByModebus(int dwLen, char* pchData);

	//文件操作命令。
public:
	CTransfer();
	~CTransfer();
	int SetCommType(int nType);//通讯类型。
	int UniversalDataEncode(int nlen,char* pchDataIn);//上层已经形成了命令+参数格式
	int DataEncode(int nlen,char* pchDataIn,int nMode,int nCmd);
	int DataEncode(int nlen,char* pchDataIn);
    char CheckSum(int nlen,char * pchInData);
	int GetCommStatus();//获取通讯状态。
    int TransferStandby(int nID, int nBound, const QString &name);//通讯状态就绪准备。准备好以后就可以发送数据了。
};
extern CTransfer g_tTranfer;

#endif
