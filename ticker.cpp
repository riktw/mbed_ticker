#include "ticker.h"

ticker::ticker()
{
} 

ticker::~ticker()
{

}

int ticker::attach(std::function<void(void)> Func, uint32_t Time)
{
	int RetVal = 0;
	if(this->FuncCounter < MAXTASKS)
	{
		for(uint32_t i = 0; i < MAXTASKS; i++)
		{
			if(this->Tasks[i].InUse == 0)
			{
				this->Tasks[i].InUse = 1;
				this->Tasks[i].Func = Func;
				this->Tasks[i].Time = Time;
				RetVal = i;
				break;
			}
		}
		++this->FuncCounter;
	}
	else
	{
		RetVal = -1;		//Full
	}
	return RetVal;
}

void ticker::detach(uint32_t TaskID)
{
	this->Tasks[TaskID].InUse = 0;
	--this->FuncCounter;
}

void ticker::execute(void)
{
	static uint32_t localtime;
	++localtime;
	for(uint32_t i; i < MAXTASKS; i++)
	{
		if(this->Tasks[i].InUse == 1)
		{
			if(this->Tasks[i].LastRun < (localtime/Tasks[i].Time))
			{
				this->Tasks[i].LastRun = (localtime/Tasks[i].Time);
				this->Tasks[i].Func();
			}
		}
	}
}