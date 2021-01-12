#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"
#include "PPMPixmap.h"
#include "Pacman.h"
#include "Maze.h"

#include "HighScore.h"
#include "GameStatus.h"
#include "MainMenu.h"

#include <chrono>

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
	PPMPixmap p_right = PPMPixmap("static/pacman_right.ppm");
	PPMPixmap p_left = PPMPixmap("static/pacman_left.ppm");
	PPMPixmap p_up = PPMPixmap("static/pacman_up.ppm");
	PPMPixmap p_bot = PPMPixmap("static/pacman_down.ppm");
	Pacman pacman = Pacman();
	Maze maze;

	pacman.now = maze.start();

	unsigned sizeInc = 0;
	while (!shouldExit)
	{
		auto start = std::chrono::steady_clock::now();
		int key = input.getKey();

		if(key)
		{
			++sizeInc;
			printf("Pressed %d\n", key);
			if(!gameStatus.getPlayingStatus())
				menu.parseKey(key);
			else if(key == KEY_ESC)
				gameStatus.setPlaying(false);
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

		printf("x = %i y = %i\n",pacman.x, pacman.y);

	//	paintDevice.drawPixmap(clyde, 300, 200);
		auto end = std::chrono::steady_clock::now();

		paintDevice.drawText("FPS: "+ std::to_string(
				1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()), 0, 0);

		if(!gameStatus.getPlayingStatus())
			menu.drawTo(paintDevice);
		else
			paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);


		for (int i = 0; i < pacman.now->neigbours_len; ++i)
		{
			paintDevice.drawRect(pacman.now->ne[i]->x,pacman.now->ne[i]->y ,8,8,0x0fff00);
		}

		paintDevice.swapBuffers();
		paintDevice.clear();
	}

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
