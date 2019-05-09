//#include "stdafx.h"
#include "CmdFile.h"
#include "QDebug"
CCmdFile g_tCmdFile;//类实例化一个对象

CCmdFile::CCmdFile()
{

}
CCmdFile:: ~CCmdFile()
{

}
void CCmdFile::Init()
{
    int i;
    for(i=0; i<CMDFILE_HEAD_LEN_DWORDS; i++)
    {
        m_dwFileHead[i] = 0;
    }
    m_cFileName = "";
    m_nFileOpenFlag = CMDFILE_CLOSED;
    m_dwFileHead[CMDFILE_HEAD_FILE_START] = 0x00010305;
    m_dwFileHead[CMDFILE_HEAD_FILE_LEN] = CMDFILE_HEAD_LEN_DWORDS*sizeof(DWORD);//文件头大小
    m_dwFileHead[CMDFILE_HEAD_CMD_LEN] = 0;
    m_dwFileHead[CMDFILE_HEAD_VER] = SN_WORK_FILE_VER;
    //sizeof(DWORD)为4字节，共64个字节；UE打开二进制文件 前面三行是文件头；05 03 01 00 这个为4个字节，小端模式，把0x00010305倒过来
}
///////////////////////////////////////////////////////////////
//函数功能：创建并打开文件进行写数据
//参数：	
//		CString* pcFileName		--	文件名称
//返回值：	BOOL	--	
bool CCmdFile::OpenFileForWrite(QString *pcFileName, QString * File)
{
    bool bRtn;

    Init();

    m_cFileName = *pcFileName;
    FileName = * File;
    m_cFile.setFileName(m_cFileName);
    bRtn =  m_cFile.open(QIODevice::Truncate|QIODevice::WriteOnly);
    if(!bRtn)return bRtn;

    m_nFileOpenFlag = CMDFILE_OPEN_WRITE;
    return bRtn;
}

///////////////////////////////////////////////////////////////
//函数功能：写文件头
//参数：
//返回值：	int		--	
int CCmdFile::WriteHead()
{
    m_cFile.seek(0);//将当前写文件指针移动到文件开始,(减去16是为了给文件名留出空间/2019年2月20日增加)
    m_cFile.write((char*)(m_dwFileHead),sizeof(m_dwFileHead)-16);
    int i = 0;
    int size;

    //2019年2月20日增加：将文件名加入二进制文件中，传输到控制卡内
    QByteArray name;
    name.resize(16);
    name= FileName.toLatin1();
    size = name.size();
    if(name.size() <= 8)
    {
        for(i = 0;i < (16 - size);i++)
            name[size+i] = 0;
    }
    else
    {
        for(i = 0;i < 8;i++)
            name[8+i] = 0;
    }
    m_cFile.write(name, 16);
    return 0;
}


//////////////////////////////////////////////////////////////
//函数功能：
//参数：
//返回值：	int		--	
int CCmdFile::WriteData(DWORD dwDataLen, PDWORD pdwData)
//typedef DWORD near *PDWORD,PDWORD表示指向DWORD的短指针类型
{
    if(m_nFileOpenFlag != CMDFILE_OPEN_WRITE) return -1;

    FillZero(dwDataLen * sizeof(DWORD));


    m_dwFileHead[CMDFILE_HEAD_CMD_LEN] += dwDataLen * sizeof(DWORD);

    //当前写操作的Page计数
    m_cFile.seek(m_cFile.size());//将当前写文件指针移动到文件末尾
    m_cFile.write( (char*)pdwData, dwDataLen * sizeof(DWORD) );

    return 0;
}

void CCmdFile::FillZero(int num)
{
    int Space=512-m_dwFileHead[CMDFILE_HEAD_CMD_LEN]%512;
    if( Space < num )
    {
        char buf[512] ={0};

        //当前写操作的Page计数
        m_cFile.seek(m_cFile.size());//将当前写文件指针移动到文件末尾
        m_cFile.write( (char*)buf, Space );

        m_dwFileHead[CMDFILE_HEAD_CMD_LEN] += Space;
    }
}

///////////////////////////////////////////////////////////////
//函数功能：关闭文件，结束操作
//参数：	
//返回值：	int		--	
void CCmdFile::CloseFile()
{
    if(m_nFileOpenFlag == CMDFILE_OPEN_WRITE)
    {
        WriteHead();
    }
    m_cFile.close();
}
