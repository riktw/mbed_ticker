#ifndef _TICKER_H_
#define _TICKER_H_

#include <string>
#include <functional>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <stdint.h>

class ticker
{

	

public:
	ticker();
	~ticker();
	int attach(std::function<void(void)> Func, uint32_t Time);
	void detach(uint32_t TaskID);
	void execute(void);
private:

	typedef struct 
	{
		uint32_t ID;
		uint32_t InUse = 0;
		uint32_t Time;
		uint32_t LastRun = 0;
		std::function<void(void)> Func;
	}Task;

	#define MAXTASKS	20
	std::array<Task, MAXTASKS> Tasks;
	uint32_t FuncCounter = 0;
	uint32_t Timebase;
};

#endif

