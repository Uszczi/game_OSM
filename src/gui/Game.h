/*
 * Game.h
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#ifndef GUI_GAME_H_
#define GUI_GAME_H_

#include "../hardware/PaintDevice.h"
#include "../game/GameStatus.h"

#include "../game/Maze.h"
#include "../game/Pacman.h"
#include "../game/Ghost.h"

#include "PacmanGraphic.h"
#include "GhostGraphic.h"


#include "ScorePoint.h"

#include <list>

class Game
{
	GameStatus gameStatus;

	Maze maze;
	PPMPixmap mazePixmap;

	Pacman pacman;
	PacmanGraphic pacmanGraphic;

	Ghost clyde;
	GhostGraphic clydeGraphic;

	Ghost clyde2;
	GhostGraphic clydeGraphic2;

	Ghost clyde3;
	GhostGraphic clydeGraphic3;


	Ghost clyde4;
	GhostGraphic clydeGraphic4;

	std::list<ScorePoint> points;

	bool isInDebugMode = false;
	bool is_playing = false;

public:
	Game();

	void processInput(int input);
	void update(double dt);
	void drawTo(PaintDevice &paintDevice) const;

	void setDebugMode(bool debug) {
		isInDebugMode = debug;
	}

	bool isPlaying() const {
		return is_playing;
	}

	void setPlaying(bool playing) {
		is_playing = playing;
	}

	int getPoints() const {
		return gameStatus.getPoints();
	}

private:
	void drawDebug(PaintDevice &paintDevice) const;
};

#endif /* GUI_GAME_H_ */
