/*
	文件名：Timer.cpp
	说明：基于select和多线程实现的定时器源文件
	作者：丁龙飞
	修改时间：2021-10-21
*/
#include "Timer.h"

/*
函数说明：构造函数
参数：
	timetype 定时器时间类型，0 秒，1 毫秒，2 微秒，默认是1
	timeval 时间间隔
	func 定时器函数
*/
Timer::Timer(unsigned long timeval,pTimerFunc func,int timetype)
{
	std::cout<<"Timer constructor"<<std::endl;
	Runflag = false;
	Timeval = timeval;
	Timefunc = func;
	Timetype = timetype;
}

/*
函数说明：析构函数
参数：
*/
Timer::~Timer()
{
	std::cout<<"Timer destructor"<<std::endl;
	Runflag = false;
}

/*
函数说明：线程运行函数
参数：
*/
void Timer::run()
{
	std::cout<<"enter run function."<<std::endl;
	
	struct timeval stuTime; 
	int ret = -1;
	if(Timefunc == NULL)
	{
		std::cout<<"Timefunc NULL,return."<<std::endl;
		return;
	}		
	while(Runflag)
	{
		memset(&stuTime, 0, sizeof(struct timeval));
		if(Timetype == 0)
		{	
			stuTime.tv_sec = Timeval;  
			stuTime.tv_usec = 0;  	
		}
		else if(Timetype == 1)
		{
			stuTime.tv_sec = Timeval/1000;  
			stuTime.tv_usec = Timeval%1000*1000;	
		}
		else if(Timetype == 2)
		{
			stuTime.tv_sec = 0;  
			stuTime.tv_usec = Timeval;  		
		}
		else
		{
			std::cout<<"Timetype error,return."<<std::endl;
			continue;
		}

		ret = select(0 ,NULL, NULL,NULL, &stuTime);  
		if(ret == 0)
		{
			//std::cout<<"set_timer_ms time come in"<<std::endl;
			//time_t currentTm = time(NULL);		
			//puts(asctime(localtime(&currentTm)));
			
			time_t currentTm = time(NULL);
			fputs(ctime(&currentTm), stdout);
			Timefunc();
		}		
	}
	std::cout<<"leave run function."<<std::endl;
}

/*
函数说明：启动定时器
参数：
*/
void Timer::timerstart()
{
	Runflag = true;
	m_thread = std::thread(&Timer::run,this);
	//设置线程分离状态
	m_thread.detach();
}

/*
函数说明：终止定时器
参数：
*/
void Timer::timerquit()
{
	Runflag = false;
	
}
