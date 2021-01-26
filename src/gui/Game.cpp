/*
 * Game.cpp
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#include "Game.h"
#include "../hardware/KeyMapping.h"

static const std::vector<int> ghostNodes = {
		11, 32, 1, 48
};

Game::Game() :
	mazePixmap(std::string("static/maze.ppm")),
	pacman(maze.start(), maze.tunnelNodes()),
	pacmanGraphic(&pacman)
{
	for(const auto& node : ghostNodes) {
		ghosts.emplace_back(maze.getNode(node));
		ghostsGraphics.emplace_back(&ghosts.back(), "static/clyde.ppm");
	}

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

	for(auto& ghost: ghosts) {
		ghost.update(pacman.x, pacman.y);
	}

	for(auto& ghostGraphic: ghostsGraphics)
	{
		if(ghostGraphic.collidesWith(pacmanGraphic)) {
			gameStatus.takeLife();
			pacman.teleport(maze.tunnelNodes().first, 115);
		}
	}

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

	for(const auto& ghost: ghostsGraphics) {
		ghost.drawTo(paintDevice);
	}

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
