#include "main.h"
#include "hardware/PaintDevice.h"
#include "hardware/InputDevice.h"

#include "game/Pacman.h"
#include "game/Maze.h"
#include "game/GameStatus.h"

#include "gui/MainMenu.h"
#include "gui/HighScore.h"
#include "gui/PPMPixmap.h"

#include "gui/PacmanGraphic.h"

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

	Maze maze;
	Pacman pacman = Pacman(maze.start());
	PacmanGraphic pacmanGraphic(&pacman);

	while (!shouldExit)
	{
		auto start = std::chrono::steady_clock::now();
		int key = input.getKey();

		if(key)
		{
			printf("Pressed %d\n", key);
			if(!gameStatus.getPlayingStatus())
				menu.parseKey(key);
			else if(key == KEY_ESC)
				gameStatus.setPlaying(false);
		}

		pacman.setDirection(Pacman::keyToDirection(key));
		pacman.update();

		paintDevice.drawPixmap(a, 0, 0);
		pacmanGraphic.drawTo(paintDevice);

		auto end = std::chrono::steady_clock::now();

		paintDevice.drawText("FPS: "+ std::to_string(
				1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()), 0, 0);

		if(!gameStatus.getPlayingStatus())
			menu.drawTo(paintDevice);
		else
			paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);


		for (int i = 0; i < pacman.currentNode()->neigbours_len; ++i)
		{
			paintDevice.drawRect(pacman.currentNode()->ne[i]->x,
					pacman.currentNode()->ne[i]->y,
					8,8,0x0fff00);
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
