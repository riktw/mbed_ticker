# mbed_ticker
An MBED like ticker library for bare metal use

MBED has the ticker library, a quick way to make a function execute periodically. On a bare metal platform without any threads and such, this is quite a handy thing to have.
The downside is that this library is interwoven in MBED and not very portable to a non MBED platform.
The ticker library here is usable on any platform as you need to add the timer yourself.

The library is simple to use. Create a ticker object and add tasks to execute with the attach function. The time added to a task is how often it's executed. 500 means it will be executed every 500ths tick.
The attach function returns an ID or -1 if an error occured.
Tasks can be removed with the detach function.

The execute function of the ticker must be executed periodically, on a microcontroller the best way to do this is using a timer interrupt. In the added example it's done via a C++11 thread that calls the execute function every 1ms.
The current maximum is 20 tasks, trying to create more tasks will result in the attach function returning an error. The maximum can be changed by changing the MAXTASKS define in ticker.h. Increasing this number does mean more RAM usage.

The demo application creates 3 tasks, removes one after a while and adds another.
It can be compiled in Linux with the command "g++ -std=c++11 -pthread -Wall ticker.cpp main.cpp -o main" and then executed with ./main
