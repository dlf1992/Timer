/*
	文件名：Timer.h
	说明：基于select和多线程实现的定时器头文件
	作者：丁龙飞
	修改时间：2021-10-21
*/
#ifndef _TIMER_H_
#define _TIMER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

using namespace std;

//定时器函数指针
typedef  void (*pTimerFunc)();

class Timer
{
public:
	Timer(){}
	Timer(unsigned long timeval,pTimerFunc func,int timetype = 1);
	~Timer();
	void run();
	void timerstart();
	void timerquit();
private:
	std::thread m_thread; //c++11 thread类
	bool Runflag;	//运行标志
	int  Timetype;	//定时器时间类型
	unsigned long Timeval;	//时间间隔
	pTimerFunc Timefunc;	//定时器函数
};

#endif