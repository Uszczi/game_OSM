#include "hardware/PaintDevice.h"
#include "hardware/InputDevice.h"
#include "hardware/KeyMapping.h"

#include "game/Pacman.h"
#include "game/Maze.h"
#include "game/GameStatus.h"

#include "gui/PPMPixmap.h"
#include "gui/MainMenu.h"
#include "gui/HighScore.h"
#include "gui/PacmanGraphic.h"

#include "misc/DataInfo.h"

#include <chrono>

static const char* HIGH_SCORE_FILE = "highscore.txt";

int main(int argc, char *argv[])
{
	bool shouldExit = false;
	bool showDebug = false;

	DataInfo fpsInfo(128);

	PaintDevice paintDevice("static/font.ppm");
	InputDevice input;

	HighScore highscores(HIGH_SCORE_FILE);
	MainMenu menu(highscores);
	GameStatus gameStatus;

	menu.setExitCallback([&](){shouldExit = true;});
	menu.setPlayCallback([&](){gameStatus.setPlaying(true);});

	PPMPixmap mazePixmap = PPMPixmap("static/maze.ppm");

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
			else if(key == KEY_SPACE)
				showDebug = !showDebug;
		}

		pacman.setDirection(Pacman::keyToDirection(key));
		pacman.update();

		paintDevice.drawPixmap(mazePixmap, 0, 0);

		if(showDebug)
		{
			for (int i = 0; i < pacman.currentNode()->neigbours_len; ++i)
			{
				paintDevice.drawRect(pacman.currentNode()->ne[i]->x,
						pacman.currentNode()->ne[i]->y,
						8, 8 ,0x0fff00);
			}
		}

		pacmanGraphic.drawTo(paintDevice);

		if(!gameStatus.getPlayingStatus())
			menu.drawTo(paintDevice);
		else
			paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);

		paintDevice.drawText("FPS: "+ std::to_string((unsigned)fpsInfo.averange()), 0, 0);

		auto end = std::chrono::steady_clock::now();
		fpsInfo.add(1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

		paintDevice.swapBuffers();
		paintDevice.clear();
	}

	return 0;
}
