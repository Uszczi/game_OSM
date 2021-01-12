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
//	SystemInit();

	PPMPixmap a = PPMPixmap("static/maze.ppm");
	PPMPixmap p_right = PPMPixmap("static/pacman_right.ppm");
	PPMPixmap p_left = PPMPixmap("static/pacman_left.ppm");
	PPMPixmap p_up = PPMPixmap("static/pacman_up.ppm");
	PPMPixmap p_bot = PPMPixmap("static/pacman_down.ppm");
	Pacman pacman = Pacman();



	Node * n1 = new Node(320, 270); // Center
	Node * n2 = new Node(250, 270);
	Node * n3 = new Node(390, 270);


	n1->add(n2);
	n1->add(n3);

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

		if (pacman.dx < 0){
			paintDevice.drawPixmap(p_left, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else if (pacman.dy > 0){
			paintDevice.drawPixmap(p_bot, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else if (pacman.dy < 0){
			paintDevice.drawPixmap(p_up, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else {
			paintDevice.drawPixmap(p_right, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		}
		paintDevice.swapBuffers();
		paintDevice.clear();
//		usleep(1);
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
