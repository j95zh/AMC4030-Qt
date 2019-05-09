#include "TransferProtocol.h"
#define USE_TIME_OUT
#define COMM_TIME_OUT_SHORT			2
#include "qcoreapplication.h"
#include   "qdatetime.h"
#include "qthread.h"
#include "amc4030.h"


CTransferProtocol::CTransferProtocol()
{
    m_nTransferType = 0;
    m_nRevDone = 0;
    m_nSendByteNum = 0;
    m_nCommStatus = ERROR_COMM_TIME_OUT;
    m_nRcvByteCnt = 0;
}
CTransferProtocol::~CTransferProtocol()
{

}

int CTransferProtocol::SendOneFrame(int nLen,char* pchInData,char* pchOutData)
{
    QTime time;

    int nRtn = 0;
    int nBreakFlag = 0;

    m_nSendByteNum = nLen;
    m_pchOutBuffer = pchInData;
    m_pchInBuffer = pchOutData;

    if(m_nCommStatus == ERROR_COMM_TIME_OUT)//通讯还没有建立。
    {
        return -1;
    }
    ////发送数据协议。
    //简化	cTimeBegin = cTimeBegin.GetCurrentTime();
    //简化	do{
    nRtn = SendData();
    //step1:通讯超时判断

    //step2:通讯失败判断。
    if(nRtn !=0)
    {//发送失败。
        m_nCommStatus = ERROR_COMM_TIME_OUT;
        ReSet();
        return -1;
    }
    //简化	}while(nRtn != 0);

    //////接收数据协议/////
    time.start();
    do
    {
#ifdef USE_TIME_OUT
        //if(cTimeDiff.GetTotalSeconds() > (nRtn==1?COMM_TIME_OUT_SHORT:COMM_TIME_OUT_LONG))
        if(time.elapsed() > (COMM_TIME_OUT_SHORT*1000))
        {
            nBreakFlag = 1;
            break;
        }
        QThread::msleep(10);

#endif
        //接收控制卡返回的帧。
        nRtn = RecvData();
        QCoreApplication::processEvents();
        //}while(nRtn != 0);
    }while(nRtn >0);

    m_nRcvByteCnt = 0;
    if(nBreakFlag)
    {
        m_nCommStatus = ERROR_COMM_TIME_OUT;
        ReSet();
        return -1;
    }
    return 0;
}

//直接调用发送接口，没有握手协议。
//返回值。0：成果，1失败。
int CTransferProtocol::SendData()
{
    int nRtn = 0;
    switch(m_nTransferType)
    {
    case COMM_LAN:
        break;
    case COMM_USB:
        break;
    case COMM_UART:
        nRtn = m_cUart.write(m_pchOutBuffer,m_nSendByteNum);
        nRtn =nRtn?0:1;
        break;
    default:
        break;
    }
    return nRtn ;
}

//接收控制返回的数据
int CTransferProtocol::RecvData()
{
    int nRtn;
    nRtn = InputData();
    char error[]="error";
    if(nRtn>0)//有数据返回
    {
        //接收到客户端反馈回的数据帧，下面为处理数据帧
        //未完成，考虑如何减少数据拷贝次数

        //memcpy(&RcvLen,m_pchInBuffer,4);//获取字节数。
        if(memcmp(m_pchInBuffer,error,4)==0)
        {
            m_nRcvByteCnt = 0;
            m_nErrorCode = COM_ERR_CARD_CHECK_SUM;
            return COM_ERR_CARD_CHECK_SUM;
        }
        if(m_nRcvByteCnt>700)//异常情况。
        {
            m_nRcvByteCnt = 0;
            m_nErrorCode = COM_ERR_BUF_OUT;
            return COM_ERR_BUF_OUT;
        }
        char  checksum = 0;
        int i;
        for(i=0; i<m_nRcvByteCnt;i++)
        {
            checksum += (char )m_pchInBuffer[i];
        }
        //	checksum =~checksum +1;

        if(checksum)//校验错误。
        {
            m_nErrorCode = COM_ERR_PC_CHECK_SUM;
            return COM_ERR_PC_CHECK_SUM;//PC接收校验错误。
        }
        m_nErrorCode = m_pchInBuffer[4];//错误码。
        if(m_nErrorCode)//命令执行错误则不拷贝有效数据。
            return 0;
        //拷贝有效数据
        /*for(i=0;i<(m_nRcvByteCnt;i++)//直接拷贝有效数据。
        {
        m_pchInBuffer[i] = m_pchInBuffer[5+i];
        }*/
        return 0;
    }
    return 1;
}
int CTransferProtocol::InputData()
{
    int nRtn = 0;
    switch(m_nTransferType)
    {
    case COMM_LAN:
        break;
    case COMM_USB:
        break;
    case COMM_UART:
        nRtn = m_cUart.read((char*)&m_pchInBuffer[m_nRcvByteCnt],(512-m_nRcvByteCnt));
        break;
    default:
        break;
    }
    if(nRtn > 0)
    {//有数据产生，
        m_nRcvByteCnt += nRtn;
        int len = (m_pchInBuffer[0]&0xff)|((m_pchInBuffer[1]<<8)&0xff00);
        if(m_nRcvByteCnt == len)
        {
            m_nRevDone = 1;
            return 1;
        }
    }
    return 0 ;
}
int CTransferProtocol::ReSet()
{
    m_nSendByteNum = 0;
    m_nCommStatus = ERROR_COMM_TIME_OUT;
    m_nTransferSetp = 0;
    m_nRevDone = 0;
    m_nRcvByteCnt = 0;
    return 0;
}
//返回值：1：成功，-1失败。
int CTransferProtocol::OpenLink(int nBunds,int nID,const QString & name)
{
    int nRtn = -1;
    switch(m_nTransferType)
    {
    case COMM_LAN:
    case COMM_USB:
        break;
    case COMM_UART:
        m_cUart.setPortName(name);    //设置端口号
        m_cUart.setBaudRate(nBunds);    	//设置波特率
        m_cUart.setDataBits(QSerialPort::Data8);   //设置数据位
        m_cUart.setParity(QSerialPort::NoParity); //设置奇偶校验位
        m_cUart.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
        m_cUart.setStopBits(QSerialPort::OneStop);//设置停止位
        nRtn = m_cUart.open(QIODevice::ReadWrite); ///串口打开，可以读写

        break;
    }
    if(nRtn == 1)
    {
        m_nCommStatus = 0;
        m_nLogicId = nID;//保存控制器的逻辑号。
    }
    else
        m_nCommStatus = ERROR_COMM_TIME_OUT;
    return nRtn;
}
////返回值：1：正确，-1：失败。
int CTransferProtocol::CloseLink(int nID)
{
    int nRtn = -1;
    switch(m_nTransferType)
    {
    case COMM_LAN:
        break;
    case COMM_USB:
        break;
    case COMM_UART:
        m_cUart.close();
        break;
    default:
        break;
    }
    m_nCommStatus = ERROR_COMM_TIME_OUT;
    m_nLogicId = 0;
    return nRtn;
}
int CTransferProtocol::GetLastErrorCode()
{
    int nRtn = m_nErrorCode;
    m_nErrorCode = 0;
    return nRtn;
}
int CTransferProtocol::GetCommStatus()
{
    return m_nCommStatus;
}
int CTransferProtocol::SetLinkType(int nType)
{
    m_nTransferType = nType;
    return 0;
}
char* CTransferProtocol::GetOutputBuffer()
{
    return m_pchInBuffer;
}
