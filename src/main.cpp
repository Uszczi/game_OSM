#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"
#include "PPMPixmap.h"
#include "Pacman.h"

volatile long globalTimer_ms = 0;
long startTime_ms;
pthread_t tID;

int main(int argc, char *argv[]) {
	PaintDevice paintDevice;
	InputDevice input;
	SystemInit();

	PPMPixmap a = PPMPixmap("static/maze.ppm");
	PPMPixmap p1 = PPMPixmap("static/pacman_right.ppm");
	Pacman pacman = Pacman();


	Node * n1 = new Node(311, 262);
	Node * n2 = new Node(241, 262);
//	Node * n3 = new Node(381, 262);

	n1->add(n2);
//	n2->add(n1);

//	n1.add(n3);
//	n3.add(n1);


	pacman.now = n1;

	while (1)
	{
		int key = input.getKey();
		if(key)
		{
			printf("Pressed %d\n", key);
		}

		pacman.setDirection(key);
		pacman.update();

		paintDevice.drawPixmap(a, 0, 0);
		paintDevice.drawPixmap(p1, pacman.x, pacman.y);
		paintDevice.swapBuffers();
		paintDevice.clear();
		usleep(1000);
		printf("x = %i y = %i\n",pacman.x, pacman.y);
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
