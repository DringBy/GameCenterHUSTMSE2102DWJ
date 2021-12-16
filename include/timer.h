#pragma once
#include<ctime>

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

private:

	//开始时间
    clock_t ctStartTime;
	//暂停时间
    clock_t ctStopgapTime;

	//是否计时中
    bool blIsRunning;

};