#include "Timer.h"

static int I = 0;
void testtimer()
{	
	cout<<"I = "<<I<<endl;
	I++;
}

static int J = 0;
void testtimer1()
{	
	cout<<"J = "<<J<<endl;
	J++;
} 
int main()
{
	Timer *ptimer = NULL;
	ptimer = new Timer(1,testtimer,0);
	if(ptimer != NULL)
	{
		ptimer->timerstart();
	}
	else
	{
		cout<<"ptimer==NULL"<<endl;
		//return -1;
	}
	
	Timer *ptimer1 = NULL;
	ptimer1 = new Timer(800,testtimer1);
	if(ptimer1 != NULL)
	{
		ptimer1->timerstart();
	}
	else
	{
		cout<<"ptimer1==NULL"<<endl;
		//return -1;
	}
	
	static int count = 20;
	while(count>0)
	{
		sleep(5);
		count--;
		if(count==10)
		{
			ptimer->timerquit();
		}
	}
	if(ptimer != NULL)
	{
		delete ptimer;
		ptimer = NULL;
	}
	if(ptimer1 != NULL)
	{
		delete ptimer1;
		ptimer1 = NULL;
	}	
	return 0;
}