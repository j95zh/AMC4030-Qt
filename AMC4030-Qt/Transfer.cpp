#include "Transfer.h"


CTransfer g_tTranfer;
CTransfer::CTransfer()
{
	m_dwLastError = 0;
}
CTransfer::~CTransfer()
{
}

//编码
int CTransfer::DataEncode(int nlen,char* pchDataIn,int nMode,int nCmd)
{

    char * buf = (char *)m_nOutBuffer;
	if(nlen > (TRANSFER_DATA_MAX_LEN-10))
	{
		return -2;
	}
	memset(m_nOutBuffer,0,TRANSFER_DATA_MAX_LEN);

	buf[0] = ((nlen+5)>>8)  & 0xff;//整个指令的长度。
	buf[1] = (nlen+5)     & 0xff;

	buf[2] = (nCmd>>8) & 0xff;
	buf[3] = nCmd      & 0xff;
	
	if(nlen > 0)
	{
		memcpy(&buf[4],pchDataIn,nlen);
	}
	nlen += 4;

	char Sum;
    Sum = CheckSum(nlen,(char *)m_nOutBuffer);
	
	buf[nlen] = Sum;
	m_nSendByteNum = nlen+1;
	return 1;
}


int CTransfer::UniversalDataEncode(int nlen,char* pchDataIn)
{

    char * buf = (char *)m_nOutBuffer;
	if((nlen > (TRANSFER_DATA_MAX_LEN-10))||(nlen==0))
	{
		return -2;
	}
	memset(m_nOutBuffer,0,TRANSFER_DATA_MAX_LEN);

	buf[0] = (nlen+3)     & 0xff;
	buf[1] = ((nlen+3)>>8)  & 0xff;//整个指令的长度。

	
	if(nlen > 0)
	{
		memcpy(&buf[2],pchDataIn,nlen);
	}
	nlen += 2;

	char Sum;
    Sum = CheckSum(nlen,(char *)m_nOutBuffer);
	
	buf[nlen] = Sum;
	m_nSendByteNum = nlen+1;
	return 1;
}


char CTransfer::CheckSum(int nlen,char* pchInData)
{
    unsigned char  CheckSum = 0;
	int i;

	for(i=0; i<nlen; i++)
	{
		CheckSum += pchInData[i];
	}

	CheckSum = (~CheckSum) + 1;
	
	return CheckSum;
}

/////////////////////////////////////////////////////////////////////////////
//功能描述：向客户端发送一帧数据
//输入参数：
//		int dwLen			-	发送缓冲的字节数
//		char* pchDataIn		-	发送的内容(命令头+参数）
//		char* pchDataOut	-	读回的内容
//返回值：1：正确；
//			-2；命令执行失败
//			-4：通讯超时。
/////////////////////////////////////////////////////////////////////////////
int CTransfer::SendUniversalData(int dwLen, char* pchData)
{
	int nRtn;
	if((dwLen > (TRANSFER_DATA_MAX_LEN-10))||(dwLen==0))
	{
		return -2;
	}
	UniversalDataEncode(dwLen,pchData);

	nRtn = SendData();
	
	if(nRtn == 0)
	{
		m_dwLastError = m_cTransferProto.GetLastErrorCode();
		if(m_dwLastError)
		{
			return -1;
		}
		return 1;
	}
	return -4;
}
/////////////////////////////////////////////////////////////////////////////
//功能描述：从客户端读取一帧数据
//输入参数：
//		int dwLen			-	发送缓冲的字节数
//		char* pchDataIn		-	发送的内容
//		char* pchDataOut	-	读回的内容
//返回值：0：正确；-1；通讯失败
/////////////////////////////////////////////////////////////////////////////
int CTransfer::ReadUniversalData(int dwLen, char* pchDataIn,char* pchDataOut)
{
	int nRtn;
	if(dwLen > TRANSFER_DATA_MAX_LEN)
	{
		dwLen = TRANSFER_DATA_MAX_LEN;
	}

	UniversalDataEncode(dwLen,pchDataIn);

	nRtn = SendData();
	
	if(nRtn == 0)
	{
		m_dwLastError = m_cTransferProto.GetLastErrorCode();
		if(m_dwLastError)
		{
			
			return -1;
		}
		//将数据拷贝到输出缓冲区中。
		char* pbuf;
		int RcvLen;
		pbuf = m_cTransferProto.GetOutputBuffer();
		RcvLen = (pbuf[0]&0xff)|((pbuf[1]<<8)&0xff00);
		RcvLen -=5;//去掉指令头。
		memcpy(pchDataOut,&pbuf[5],RcvLen);

		return 1;
	}
	//拷贝数据到outbuffer
	return -4;

	return 0;
}

//将编码后的数据发送到控制器。
//返回值:
//-4：通讯超时。
//1:发送成功。
//-1：还没建立连接
//-3:控制器接收数据校验错误。
//-5：PC接收数据校验错误。
int CTransfer::SendData()
{
	return m_cTransferProto.SendOneFrame(m_nSendByteNum,(char*)m_nOutBuffer,(char*)m_nInBuffer);
}

//得到通讯是否连接到
int CTransfer::GetCommStatus()
{
	return m_cTransferProto.GetCommStatus();
}
//通讯状态就绪准备。准备好以后就可以发送数据了。
//返回值：0 -- 准备好了；
//        -1 --没准备好。
int CTransfer::TransferStandby(int nID, int nBound,const QString &name)
{
	int nRtn = 1;
	//如果通讯协议没准备好。
	if(m_cTransferProto.GetCommStatus() == ERROR_COMM_TIME_OUT)
	{
        nRtn = m_cTransferProto.OpenLink(nBound,nID,name);

	}
	else
	{//是否考虑发送一帧通讯测试数。
		;
	}
	if(nRtn)return 0;
	else
		return -1;
}
int CTransfer::SetCommType(int nType)
{
	m_cTransferProto.SetLinkType(nType);
	return 0;
}
