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

#include "gui/Game.h"

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

	Game game;

	menu.setExitCallback([&](){shouldExit = true;});
	menu.setPlayCallback([&](){game.setPlaying(true);});

	auto prev = std::chrono::steady_clock::now();
	while (!shouldExit)
	{
		auto current = std::chrono::steady_clock::now();
		const auto dt_us = std::chrono::duration_cast<std::chrono::microseconds>(current - prev);
		prev = current;

		int key = input.getKey();

		if(key)
		{
			printf("Pressed %d\n", key);

			if(!game.isPlaying())
				menu.processInput(key);
			else
				game.processInput(key);

			if(key == KEY_SPACE) {
				showDebug = !showDebug;
				game.setDebugMode(showDebug);
			}
		}

		const double dt_s = dt_us.count()/1000000.0;
		if(game.isPlaying())
			game.update(dt_s);

		fpsInfo.add(1.0/dt_s);

		game.drawTo(paintDevice);

		if(!game.isPlaying())
			menu.drawTo(paintDevice);

<<<<<<< HEAD

//		for (int i = 0; i < pacman.now->neigbours_len; ++i)
//		{
//			paintDevice.drawRect(pacman.now->ne[i]->x,pacman.now->ne[i]->y ,8,8,0x0fff00);
//		}
=======
		paintDevice.drawText("FPS: "+ std::to_string((unsigned)fpsInfo.averange()), 0, 0);
>>>>>>> maze/refactorization

		paintDevice.swapBuffers();
		paintDevice.clear();
	}

	return 0;
}
