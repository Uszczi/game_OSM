#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"

volatile long globalTimer_ms = 0;
long startTime_ms;
pthread_t tID;

int main(int argc, char *argv[]) {
	PaintDevice paintDevice;
	InputDevice input;
	SystemInit();

	while (1)
	{
		int key = input.getKey();
		if(key)
		{
			printf("Pressed %d\n", key);
		}

		paintDevice.drawBitmap();
		paintDevice.swapBuffers();
		paintDevice.clear();

		usleep(10000);
	}
}

void* TimerThread(void* arguments)
{
	struct timespec destTime;
	clock_gettime(CLOCK_MONOTONIC,&destTime);
	while(1)
	{
		destTime.tv_nsec+=1000000;
		if(destTime.tv_nsec>=1E9)
		{
			destTime.tv_nsec-=1E9;
			destTime.tv_sec++;
		}
		globalTimer_ms++;
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &destTime, NULL);
	}
	return NULL;
}

void SystemInit()
{
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	startTime_ms=tTime.tv_sec*1000+tTime.tv_usec/1000;
}
