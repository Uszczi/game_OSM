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
pacman(maze.start(), maze.tunnelNodes()),
pacmanGraphic(&pacman),
clyde(maze.getNode(11)),
clydeGraphic(&clyde, "static/clyde.ppm"),
clyde2(maze.getNode(32)),
clydeGraphic2(&clyde2, "static/clyde.ppm"),
clyde3(maze.getNode(1)),
clydeGraphic3(&clyde3, "static/clyde.ppm"),
clyde4(maze.getNode(48)),
clydeGraphic4(&clyde4, "static/clyde.ppm")

{
	for(const auto& pos : maze.getNodePoints())
		points.push_back(ScorePoint(pos.first, pos.second));

	for(const auto& pos : maze.getAdditionalPoints())
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
	clyde.update(pacman.x, pacman.y);
	clyde2.update(pacman.x, pacman.y);
	clyde3.update(pacman.x, pacman.y);
	clyde4.update(pacman.x, pacman.y);

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
	clydeGraphic.drawTo(paintDevice);
	clydeGraphic2.drawTo(paintDevice);
	clydeGraphic3.drawTo(paintDevice);
	clydeGraphic4.drawTo(paintDevice);

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
