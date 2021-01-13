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

#include "PacmanGraphic.h"

class Game
{
	GameStatus gameStatus;

	Maze maze;
	PPMPixmap mazePixmap;

	Pacman *pacman;
	PacmanGraphic pacmanGraphic;

	bool isInDebugMode = false;
	bool is_playing = false;

public:
	Game();
	virtual ~Game();

	void processInput(int input);
	void update(double dt);
	void drawTo(PaintDevice &paintDevice) const;

	void reset();

	void setDebugMode(bool debug) {
		isInDebugMode = debug;
	}

	bool isPlaying() const {
		return is_playing;
	}

	void setPlaying(bool playing) {
		is_playing = playing;
	}

private:
	void drawDebug(PaintDevice &paintDevice) const;
};

#endif /* GUI_GAME_H_ */
