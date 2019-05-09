#ifndef COMM_DEFINE_H_BY_TP_20170315
#define COMM_DEFINE_H_BY_TP_20170315

#define MAX_AXIS_NUM		3
#define AXIS_X				0
#define AXIS_Y				1
#define AXIS_Z				2
//////////////////////////////////////////////////
//通讯命令字。
#define COM_READ_FILE_DATA			0x0101//读文件数据
#define COM_WRITE_FILE_DATA			0x0102//写文件数据
#define COM_GET_MACHINE_STATUS		0x0103//读机器状态
#define COM_AXIS_JOG				0x0104//轴点动
#define COM_AXIS_HOME				0x0105//轴回零
#define COM_SET_OUTPUT_STATUS		0x0106//设置输出口状态。
#define COM_STOP_ALL				0x0107//停止所有。
#define COM_STOP_SP_AXIS		    0x0108//停止指定轴。
#define COM_GET_FILENAME            0x0112//获取控制卡内文件名及个数

//////////////////////////////////////////////////
//多作属性页定义。
#define FUNC_SEL_EVENT	0
#define FUNC_INPUT		1
#define FUNC_OUTPUT		2
#define FUNC_PMOV		3
#define FUNC_REPEAT_MOV	4
#define FUNC_SEC_MOV	5//分段运动
#define FUNC_DELAYTIME	6
#define FUNC_HOME		7
#define FUNC_FINISH		8

//输入口节点
#define INPUT_FUNC_START
#define INPUT_FUNC_STOP
typedef struct _INPUT_EVENT_
{
	int		nID;//输入口序号
	int		nActivLevel;//有效电平
	int		nFunction;//输入口功能。
}InputEvent,*PInputEvnet;
//输出口节点
typedef struct _OUTPUT_EVENT_
{
	int   nID;//输入口序号
	int   nLevel;//输出状态。
}OutputEvent,*POutputEvent;

//点位运动节点
typedef struct _PMOV_EVENT_
{
	int   nType;//相对运动//绝对运动
	int	  nAxisSet[MAX_AXIS_NUM];//哪个轴运动
	float   nMovDis[MAX_AXIS_NUM];//轴运动的位置或距离。
	float  fMovSpeed[MAX_AXIS_NUM];
	float  fMovAcc[MAX_AXIS_NUM];
}PMovEvent,*PPmovEvent;

//点位运动节点
typedef struct _REPEAT_PMOV_EVENT_
{
	int	  nAxisSet[MAX_AXIS_NUM];//哪个轴运动
	float   nMovDis;//运动的距离。
	int	  nTimes;//往复次数
	float fSpeed;//速度
	float fAcc;//加速度。
}RepeatPMovEvent,*PRepeatPmovEvent;

//分段运动。
typedef struct _SEC_PMOV_EVENT_
{//未定义???
	int	  nAxisSet[MAX_AXIS_NUM];//哪个轴运动
	int   nMovDis;//运动的距离。
	int	  nTimes;//往复次数
	float fSpeed;//速度
	float fAcc;//加速度。
}SecPMovEvent,*PSecPmovEvent;

//延时事件
typedef struct _DELAY_EVENT_
{
		int		ms;//延时时间。
}DelayEvent,*PDelayEvent;

//回零事件
typedef struct _HOME_EVENT_
{
	int	  nAxisSet[MAX_AXIS_NUM];//哪个轴运动

}HomeEvent,*PHomeEvent;

//IO扩展板IO口信息
typedef struct _IO_STUTAS_
{
    char NodeId[128];
    unsigned short int NodeIOStatus[128];
}IO_STATUS, *PIO_STATUS;

typedef struct _MACHINE_STATUS_
{
    IO_STATUS  IO_Status;
    unsigned int	dwWorkStatus;//D0:暂停中；D1：加工；D2：点动中；D3：回零中。D4:有报警。
    char	dwHomeDone;//是否正确回零。D0:X轴正确回过零；D1:Y轴正确回过零；D2:Z轴正确回过零；
    char	nID;//机器逻辑编号。预留多卡共用识别标示。
    unsigned short int	FirmVer;		//固件版本。
    int		nPos[3];//轴的当前位置，此值放大了100000倍，以解决浮点传输问题。
    unsigned int		RealSpeed[3];//轴的当前速度。此值放大100000倍，以解决浮点传输问题。
    unsigned int	nAlmCode;//报警编码
    unsigned short int	dwInputStatus;//输入口状态D0-IN1; D1-IN2; D3-IN3; D4-IN4; D5-ORG1; D6-ORG2; D7-ORG3;
    unsigned short int 	dwOutputStatus;//输出口状态。
    unsigned int	Rsv[40];
}MACHINE_STATUS,*PMACHINE_STATUS;

typedef struct _FILE_INFO_
{
    char filename[11][10];
    int file_total;
}FILESYSTEM,*PFILESYSTEM;

#endif
