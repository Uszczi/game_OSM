/*
 * Game.cpp
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#include "Game.h"
#include "../hardware/KeyMapping.h"

Game::Game() :
	mazePixmap(std::string("static/maze.ppm")),
	pacman(maze.start()),
	pacmanGraphic(&pacman)
{

}

void Game::processInput(int input)
{
	pacman.setDirection(Pacman::keyToDirection(input));

	if(input == KEY_ESC)
		is_playing = false;
}

void Game::update(double dt)
{
	pacman.update();
}

void Game::drawTo(PaintDevice &paintDevice) const
{
	paintDevice.drawPixmap(mazePixmap, 0, 0);

	if(isInDebugMode)
		drawDebug(paintDevice);

	pacmanGraphic.drawTo(paintDevice);
	paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);
}

void Game::drawDebug(PaintDevice &paintDevice) const
{
	for (int i = 0; i < pacman.currentNode()->neigbours_len; ++i)
	{
		paintDevice.drawRect(pacman.currentNode()->ne[i]->x,
				pacman.currentNode()->ne[i]->y,
				8, 8 ,0x0fff00);
	}
}
