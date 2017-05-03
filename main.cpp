#include <iostream>
#include <thread>
#include <chrono>

#include "ticker.h"

ticker taskstodo(1);

void printhello(void)
{
	std::cout << "Hello world" << std::endl;
}

void printhey(void)
{
	std::cout << "Hey world" << std::endl;
}

void printahoy(void)
{
	std::cout << "Yarrrr" << std::endl;
}

void printmeow(void)
{
	std::cout << "Meow!" << std::endl;
}

void doEveryMs(void)
{
	while(1)
	{
		taskstodo.execute();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	//Need to execute the execute function of Ticker every X time. Quickest way to do this in Linux is this.
	std::thread t1(doEveryMs);

	//Create a few tasks to amuse Ticker.
	int ID1 = taskstodo.attach(printhello, 500);
	int ID2 = taskstodo.attach(printhey, 1500);
	int ID3 = taskstodo.attach(printahoy, 1000);

	//Ids are 0, 1 and 2 as the tasks array is empty at start.
	std::cout << "ID1 is: " << ID1 << ", ID2 is: " << ID2 << ", ID3 is: " << ID3 << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	taskstodo.detach(ID2);
	int ID4 = taskstodo.attach(printmeow, 1000);

	//Task ID2 has been removed, a new task has been added. ID4 will have the same ID as task ID2 had.
	std::cout << "ID1 is: " << ID1 << ", ID2 is: " << ID2 << ", ID3 is: " << ID3 << ", ID4 is: " << ID4 << std::endl;
	t1.join();
	return 0;
}
