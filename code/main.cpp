#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <windows.h>
#include "multi_timer.h"
#define CCT (+8)//¥xÆW

//https://github.com/0x1abin/MultiTimer

using namespace std;

struct Timer timer1;
struct Timer timer2;

void getTime(char *chrDateTimeBuf)
{
    time_t rawtime;
    struct tm *tm_time;
    rawtime = time(NULL);
    tm_time = gmtime(&rawtime);

    rawtime = time(NULL);
    tm_time = gmtime(&rawtime);
    sprintf(chrDateTimeBuf,"%d/%02d/%02d %02d:%02d:%02d",1900+tm_time->tm_year,tm_time->tm_mon+1,tm_time->tm_mday,(tm_time->tm_hour+CCT), tm_time->tm_min,tm_time->tm_sec);
}
void timer1_callback()
{
    char chrDateTimeBuf[80];
    getTime(chrDateTimeBuf);
    printf("timer1 timeout ~ %s \r\n",chrDateTimeBuf);
}

void timer2_callback()
{
    char chrDateTimeBuf[80];
    getTime(chrDateTimeBuf);
    printf("timer2 timeout ~ %s \r\n",chrDateTimeBuf);
}

void HAL_SYSTICK_Callback(void)
{
    Sleep(1);
    timer_ticks(); //1ms ticks
}
int main()
{
    char chrDateTimeBuf[80];
    getTime(chrDateTimeBuf);
    cout << "Hello world!\t" << chrDateTimeBuf << endl;
	timer_init(&timer2, timer2_callback, 00, 0);
	timer_start(&timer2);

	timer_init(&timer1, timer1_callback, 0, 70); //1s loop
	timer_start(&timer1);



	while(1) {
	    timer_loop();
	    HAL_SYSTICK_Callback();
	}
    return 0;
}
