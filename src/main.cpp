#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"
#include "PPMPixmap.h"

volatile long globalTimer_ms = 0;
long startTime_ms;
pthread_t tID;

int main(int argc, char *argv[]) {
	PaintDevice paintDevice("static/font.ppm");
	InputDevice input;
	SystemInit();

	PPMPixmap a = PPMPixmap("static/maze.ppm");
	PPMPixmap p1 = PPMPixmap("static/pacman_right.ppm");
	PPMPixmap p2 = PPMPixmap("static/pacman_left.ppm");
	PPMPixmap p3 = PPMPixmap("static/pacman_down.ppm");
	PPMPixmap p4 = PPMPixmap("static/pacman_up.ppm");
	PPMPixmap clyde = PPMPixmap("static/clyde.ppm");

	while (1)
	{
		int key = input.getKey();
		if(key)
		{
			printf("Pressed %d\n", key);
		}

		paintDevice.drawPixmap(a, 0, 0);
		paintDevice.drawPixmap(p1, 319, 261);
		paintDevice.drawPixmap(p2, 219, 261);
		paintDevice.drawPixmap(p3, 119, 261);
		paintDevice.drawPixmap(p4, 19, 261);
		paintDevice.drawPixmap(clyde, 300, 200);

		paintDevice.drawText("Elo to jest test!\nTo chyba ma szanse dzialac\n12 + 6 = 18 :0", 0, 0);

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
