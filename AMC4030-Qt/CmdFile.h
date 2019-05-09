
#ifndef CMD_FILE_H_BY_TP_20170328
#define CMD_FILE_H_BY_TP_20170328

#include "windows.h"
#include "QFile"
#include "QDir"
#include <QComboBox>

#define SN_WORK_FILE_VER		0x01010101

/////////////////////////////////////////////////////////////////////////////////
//当前是否打开文件以及打开方式
#define		CMDFILE_CLOSED				0
///#define		CMDFILE_OPEN_READ			1
#define		CMDFILE_OPEN_WRITE			2
#define CMDFILE_HEAD_LEN_DWORDS			16
//以下为文件头中各信息在文件头中的偏移量，以DWORD为单位
//#define		CMDFILE_HEAD_LEN_DWORDS		128		//指令数据文件头长度
//#define		CMDFILE_HEAD_LEN_BYTES		(CMDFILE_HEAD_LEN_DWORDS*4)		//指令数据文件头长度
//#define		CMDFILE_PAGE_LEN_BYTES		512		//每页字节数
#define		CMDFILE_HEAD_FILE_START		  0			//文件头起始标记地址。
#define		CMDFILE_HEAD_FILE_LEN		1		//文件头信息长度
#define		CMDFILE_HEAD_CMD_LEN		2		//指令字节长度。
#define		CMDFILE_HEAD_VER			3		//版本信息在文件头中的偏移量
//#define		CMDFILE_HEAD_WORK_TIMES		3		//加工次数信息在文件头中的偏移量
//#define		CMDFILE_HEAD_MOTION_CMD_NUM	4		//运动指令数目信息在文件头中的偏移量
//#define		CMDFILE_HEAD_FILETYPE		5		//文件类型以及加工模式--立即或者绝对坐标

class CCmdFile  
{
public:
    CCmdFile();
    virtual ~CCmdFile();

private:
    ///int m_MCmdCnt;									//解析过程运动指令计数
    ///int m_nMainCmdCounter;							//加工文件运动指令总计数
    ///int m_nCmdFileFlag;								//写文件标记，1-写状态
    int m_nFileOpenFlag;							/*/当前文件打开状态*/
    ///DWORD m_dwCurWritePageNum;						/*/当前写入位置*/
    QFile m_cFile;									/*/用于对文件进行操作的文件类对象*/
    QString m_cFileName;							/*/保存文件名*/
    QString FileName;							    /*/不含地址的文件名*/
    DWORD m_dwFileHead[CMDFILE_HEAD_LEN_DWORDS];	/*/保存文件头信息*/

    int DataLen=0;         //保存指令的长度，按512个字节分段

public:	
    ///int WriteFile(int num, DWORD *data);

    //	void SetWorkMode(int Mode);
    ///void SetFileType(int Type);
    //	int SetMainPointer(DWORD dwStartPageNum);
    ///int FillToNextPage();
    //	DWORD GetCurPageNum();
    ///	int SetFileName(CString& cFileName);
    //	int SetWorkTimes(DWORD nTimes);
    //	int SetFileLenBytes(DWORD dwFileLenBytes);
    //	int SetMotionCmdNum(DWORD dwCmdNum);
    //	int SetCmdNum(DWORD dwCmdNum);
    //	int SetSubPointer(int nSubID, DWORD dwStartPageNum);
    //预计加工时间
    //	int SetPreWorkFile(double PreWirkTime);
    //	int SwitchFileName(CString csFileNameSrc, PBYTE pchFileName);		/*/将文件名转换成FLASH中存放的11个字节的格式*/
    //	CString GetFileName();							/*/获得文件名*/
    //	DWORD GetRunTimes();							/*/取得加工次数*/
    //	DWORD GetVer();									/*/取得版本号*/
    //	DWORD GetCmdNum();								/*/取得指令数目*/
    //	DWORD GetFileLenBytes();						/*/取得文件长度*/
    //	DWORD GetMotionCmdNum();						/*/运动指令数目*/
    ///int GetFileOpenStatus();						/*/取得文件打开状态*/

    bool OpenFileForWrite(QString* pcFileName, QString *File);		/*/打开文件用于写*/
    ///bool OpenFileForRead(QString* pcFilename);		/*/打开文件用于读*/
    ///bool OpenFileForRead();							/*/打开文件用于读*/
    ///int ReadHead();									/*/读取文件头*/
    ///int ReadData(PBYTE pchData);					/*/读文件数据段数据*/
    ///int GetFileLen();
    ///int ReadFile(PBYTE pchData,int nSize);					//读取所有文件内容。
    void CloseFile();								/*/关闭文件*/
    void Init();									/*/初始化类*/
    int WriteHead();								/*/写文件头*/
    int WriteData(DWORD dwDataLen, PDWORD pdwData);	/*/写数据区*/

    void FillZero(int num);////保存指令的长度，未达到512个字节则填0

};
extern CCmdFile g_tCmdFile;

#endif
