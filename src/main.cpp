#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"
#include "PPMPixmap.h"

#include "HighScore.h"
#include "GameStatus.h"
#include "MainMenu.h"

static const char* HIGH_SCORE_FILE = "highscore.txt";

volatile long globalTimer_ms = 0;
long startTime_ms;
pthread_t tID;

int main(int argc, char *argv[])
{
	SystemInit();
	bool shouldExit = false;

	PaintDevice paintDevice("static/font.ppm");
	InputDevice input;

	HighScore highscores(HIGH_SCORE_FILE);
	MainMenu menu(highscores);
	GameStatus gameStatus;

	menu.setExitCallback([&](){shouldExit = true;});
	menu.setPlayCallback([&](){gameStatus.setPlaying(true);});

	PPMPixmap a = PPMPixmap("static/maze.ppm");
	PPMPixmap p1 = PPMPixmap("static/pacman_right.ppm");
	PPMPixmap p2 = PPMPixmap("static/pacman_left.ppm");
	PPMPixmap p3 = PPMPixmap("static/pacman_down.ppm");
	PPMPixmap p4 = PPMPixmap("static/pacman_up.ppm");
	PPMPixmap clyde = PPMPixmap("static/clyde.ppm");

	while (!shouldExit)
	{
		int key = input.getKey();
		if(key)
		{
			printf("Pressed %d\n", key);
			if(!gameStatus.getPlayingStatus())
				menu.parseKey(key);
			else if(key == KEY_ESC)
				gameStatus.setPlaying(false);
		}

		paintDevice.drawPixmap(a, 0, 0);
		paintDevice.drawPixmap(p1, 319, 261);
		paintDevice.drawPixmap(p2, 219, 261);
		paintDevice.drawPixmap(p3, 119, 261);
		paintDevice.drawPixmap(p4, 19, 261);
		paintDevice.drawPixmap(clyde, 300, 200);

		if(!gameStatus.getPlayingStatus())
			menu.drawTo(paintDevice);
		else
			paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);

		paintDevice.swapBuffers();
		paintDevice.clear();

		usleep(10000);
	}

	gameStatus.addPoints(8000);
	highscores.addEntry(gameStatus.getPoints());
	highscores.save();

	return 0;
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
