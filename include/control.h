#pragma once
#include<ctime>
#include<Windows.h>

//计时器
class timer
{
public:

	timer();

    //设置偏移时间
	bool SetOffset(int iOffset);
	//清除时间
    bool Clean();
	//是否计时中
    bool GetIsRunning();
	//开始计时
    bool Start();
	//结束计时
    bool Stop();
	//重新计时
    void Reset();
	//读取时间
	//停止时返回记录时间的负数
    clock_t Read();

	//确保timer为开启状态，否则返回-1 一般情况返回时差
	clock_t SleepTill(clock_t ctSleepTime);

private:

	//开始时间
    clock_t ctStartTime;
	//暂停时间
    clock_t ctStopgapTime;

	//是否计时中
    bool blIsRunning;

};

struct keycheck
{
	DWORD vKey;
	//状态 0松开 1按下 2持续按下 3长时间按下(由LongPress设置)
	int stat;
	//点击次数
	unsigned int PressCount;
	//长按锁定 防止进入下一界面为长按时导致的错误 默认开
	bool clock;

	//gvKey 检测按键的虚拟键位码
	keycheck(DWORD gvKey);
	//默认初始化，以255（不存在）为检测键
	keycheck();

	//获取状态 0松开 1按下 2持续按下 3长时间按下(由LongPress设置)
	int getstat();
	//gvKey 检测按键的虚拟键位码
	void reset(DWORD gvKey);

	static unsigned int iLongPress;
	//设置longpress
	static unsigned int SetLongPress(unsigned int newarg);
};