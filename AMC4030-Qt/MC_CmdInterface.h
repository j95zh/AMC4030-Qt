#ifndef MC_CMD_INTERFACE_H_BY_TP_20170324
#define MC_CMD_INTERFACE_H_BY_TP_20170324

#include "QString"
#define MC_CALLBACK			int

MC_CALLBACK MC_CMD_WriteBegin(QString fileName, QString file);//指令开始

MC_CALLBACK MC_CMD_End();//指令结束

//////////////////运动命令指令定义////////////////////////
//系统操作
#define CMD_STOP_ALL                        0x00000101
#define CMD_START                           0x00000201
#define CMD_PAUSE                           0x00000301
#define CMD_RESUME                          0x00000401
#define CMD_DELAY_TIME                      0x01000501
#define CMD_CHECK_MOTOR_DONE	            0x03000601
#define CMD_STOP_NAMED_MOTOR                0x03000701//停止电机运动
#define CMD_WAITING                         0x00000701//常等待

//流程控制
#define CMD_PROGRAM_JUMP                    0x01000102
#define CMD_PROGRAM_LOOP                    0x02000102
#define CMD_INPUT_JUMP                      0x03000102
#define CMD_OPEN_INPUT_INT                  0x03000202
#define CMD_CLOSE_INPUT_INT                 0x02000202
//#define CMD_SUB_CALL 		                0x01000302
//#define CMD_SUB_CALL_RETURN		        0x00000102
//#define CMD_OPEN_TIMER_INT                0x03000302
//#define CMD_CLOSE_TIMER_INT               0x00000202

//输出口操作
#define CMD_SET_OUTPUT_BIT                  0x02000103

//回零运动
#define CMD_SET_HOME_SPEED                  0x03000104
#define CMD_START_HOME                      0x03000204
#define CMD_SET_AND_START_HOME              0x03000304//设置回零速度与启动回零合并

//直线点位运动
#define CMD_SET_PMOV_SPEED                  0x02000105//设置点位速度
#define CMD_PMOV						    0x03000105//三轴相对运动
#define CMD_ABS_PMOV		                0x04000105//绝对运动（单轴、XY、XZ、YZ、三轴）

//独立插补运动
#define CMD_SET_ALONE_PMOV_SPEED            0x03000106
#define CMD_ALONE_PMOV					    0x03000206

//DM寄存器
#define CMD_DM_ASSIGNMENT					0x02000107//DM赋值
#define CMD_DM_ADD_NUM						0x02000207//DM加常数
#define CMD_DM_ADD_DM						0x02000307//DM加DM
#define CMD_DM_DELAY						0x01000307//DM作延时
#define CMD_DM_PROGRAM_JUMP				    0x02000407//DM作程序循环
#define CMD_DM_SET_AND_START_HOME			0x03000407//DM作回零
#define CMD_DM_PMOV_SPEED		  		    0x02000507//DM作点位速度
#define CMD_DM_PMOV							0x03000507//DM作相对运动
#define CMD_DM_ABS_PMOV						0x04000507//DM作绝对运动

////////////////////////   系统操作  ////////////////////////////
//停止
MC_CALLBACK MC_CMD_StopAll();
//启动
MC_CALLBACK MC_CMD_Start();
//暂停
MC_CALLBACK MC_CMD_Pause();
//恢复
MC_CALLBACK MC_CMD_Resume();
//延时
MC_CALLBACK MC_CMD_DelayTime(int ms);
//等待电机完成
MC_CALLBACK MC_CMD_CheckMotorDone(int XAxis,int YAxis,int ZAxis);
//停止电机运动
MC_CALLBACK MC_CMD_StopNamedMotor(int XAxis,int YAxis,int ZAxis);
//常等待
MC_CALLBACK MC_CMD_Waiting();

////////////////////////   流程控制  ////////////////////////////
//程序行间跳转
MC_CALLBACK MC_CMD_ProgramJump(int Row);
//程序循环
MC_CALLBACK MC_CMD_ProgramLoop(int Row,int Times);
//输入跳转
MC_CALLBACK MC_CMD_InputJump(int Input,int Level,int Row);
//开启输入中断
MC_CALLBACK MC_CMD_OpenInputInterrupt(int Input,int Level,int Row);
//关闭输入中断
MC_CALLBACK MC_CMD_CloseInputInterrupt(int Input,int Level);
/*
//子程序调用
MC_CALLBACK MC_CMD_SubroutineCall(int Row);
//子程序返回
MC_CALLBACK MC_CMD_SubroutineReturn();
//开启定时中断
MC_CALLBACK MC_CMD_OpenTimerInterrupt(int Timer,int ms,int Row);
//关闭定时中断
MC_CALLBACK MC_CMD_CloseTimerInterrupt();
*/

////////////////////////  输出口操作 /////////////////////////////
//输出口设置
MC_CALLBACK MC_CMD_SetOutputBit(int Output,int Level);

////////////////////////   回零运动  ////////////////////////////
//设置回零速度
MC_CALLBACK MC_CMD_SetHomeSpeed(float XSpeed,float YSpeed,float ZSpeed);
//启动回零
MC_CALLBACK MC_CMD_StartHome(int XAxis,int YAxis,int ZAxis);
//设置回零速度与启动回零合并，只写某个轴的回零速度就启动回零
MC_CALLBACK MC_CMD_SetAndStartHome(float XSpeed,float YSpeed,float ZSpeed);

//////////////////////// 直线点位运动 ////////////////////////////
//设置点位速度
MC_CALLBACK MC_CMD_SetPointSpeed(float Speed,float Acc);
//三轴相对运动
MC_CALLBACK MC_CMD_ThreeAxisRelativeMotion(float XDis,float YDis,float ZDis);
//绝对运动
MC_CALLBACK MC_CMD_AbsoluteMotion(int nAxis,float XDis,float YDis,float ZDis);

//////////////////////// 独立插补运动 ///////////////////////////
//设置独立运动速度
MC_CALLBACK MC_CMD_SetIndependentSpeed(int nAxis,float Speed,float Acc);
//三轴独立相对插补
MC_CALLBACK MC_CMD_IndependentMotion(float XDis,float YDis,float ZDis);

//////////////////////// DM寄存器 ///////////////////////////
//DM赋值
MC_CALLBACK MC_CMD_DM_Assignment(int reg,float num);
//DM加常数
MC_CALLBACK MC_CMD_DM_AddNum(int reg,float num);
//DM加DM
MC_CALLBACK MC_CMD_DM_AddDM(int reg1,int reg2);
//DM延时
MC_CALLBACK MC_CMD_DM_Delay(int reg);
//DM作程序循环
MC_CALLBACK MC_CMD_DM_ProgramLoop(int num,int reg);
//DM作回零
MC_CALLBACK MC_CMD_DM_SetAndStartHome(int regx,int regy,int regz);
//DM设置点位速度
MC_CALLBACK MC_CMD_DM_PMOV_Speed(int reg1,int reg2);
//DM作相对运动
MC_CALLBACK MC_CMD_DM_PMOV(int regx,int regy,int regz);
//DM作独立运动
MC_CALLBACK MC_CMD_DM_ABS_PMOV(int nAxis,int regx,int regy,int regz);

#endif
