/*
 * Game.cpp
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#include "Game.h"
#include "../hardware/KeyMapping.h"

std::vector<std::pair<int, int>> pointsPos = {
		{124, 20}, {153, 20}, {182, 20}, {211, 20}, {240, 20}, {269, 20},
		{124, 49}, {204, 49}, {296, 49}, {124, 78}, {153, 78}, {182, 78},
		{211, 78}, {240, 78}, {269, 78}, {124, 107}, {204, 107}, {250, 107},
		{124, 136}, {153, 136}, {182, 136}, {250, 136}, {279, 136}, {204, 165},
		{296, 165}, {204, 194}, {204, 223}, {204, 252}, {204, 281}, {124, 310},
		{153, 310}, {182, 310}, {211, 310}, {240, 310}, {269, 310}
};

Game::Game() :
	mazePixmap(std::string("static/maze.ppm")),
	pacman(maze.start()),
	pacmanGraphic(&pacman)
{
	for(const auto& pos : pointsPos)
		points.push_back(ScorePoint(pos.first, pos.second));
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

	auto iter = points.begin();
	while(iter != points.end())
	{
		if (pacmanGraphic.collidesWith(*iter)) {
			iter = points.erase(iter);
			gameStatus.addPoints(1);
		}
		else {
			++iter;
		}
	}
}

void Game::drawTo(PaintDevice &paintDevice) const
{
	paintDevice.drawPixmap(mazePixmap, 0, 0);

	if(isInDebugMode)
		drawDebug(paintDevice);

	for(const auto& scorePoint : points)
		scorePoint.drawTo(paintDevice);

	pacmanGraphic.drawTo(paintDevice);

	paintDevice.drawText("HP: " + std::to_string(gameStatus.getLifeCount()), 0, paintDevice.getHeight() - 50);
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
