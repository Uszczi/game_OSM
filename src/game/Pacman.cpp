/*
 * Pacman.cpp
 *
 *  Created on: 4 sty 2021
 *      Author: Mateusz
 */

// direction = RIGHT = 0
// direction = LEFT = 1
// direction = TOP = 2
// direction = DOWN = 3

#include "Pacman.h"
#include "../hardware/KeyMapping.h"

PacmanDirection Pacman::keyToDirection(int key)
{
	switch(key)
	{
	case ARROW_UP:
		return PacmanDirection::Up;
	case ARROW_DOWN:
		return PacmanDirection::Down;
	case ARROW_LEFT:
		return PacmanDirection::Left;
	case ARROW_RIGHT:
		return PacmanDirection::Right;
	}

	return PacmanDirection::NoMove;
}

Pacman::Pacman(Node *startNode) :
	now(startNode)
{
	x = startNode->x;
	y = startNode->y;

	dx = 0;
	dy = 0;

	direction = 0;
	next_direction = 0;
}

void Pacman::update()
{
	now = now->change_now(x, y);

	if (now->check_move(dx, dy, x, y))
	{
		x += dx;
		y += dy;
	}
}

void Pacman::setDirection(PacmanDirection direction)
{
	switch(direction)
	{
	case PacmanDirection::Right:
		if (now->check_move(1, 0, x, y))
		{
			dx = 1;
			dy = 0;
		}
		break;

	case PacmanDirection::Left:
		if (now->check_move(-1, 0, x, y))
		{
			dx = -1;
			dy = 0;
		}
		break;
	case PacmanDirection::Up:
		if (now->check_move(0, -1, x, y))
		{
			dx = 0;
			dy = -1;
		}
		break;

	case PacmanDirection::Down:
		if (now->check_move(0, 1, x, y))
		{
			dx = 0;
			dy = 1;
		}
		break;
	default:
		break;
	}
}

std::pair<int, int> Pacman::getPos() const
{
	return std::make_pair(x + off_x, y + off_y);
}

std::pair<int, int> Pacman::getSpeed() const
{
	return std::make_pair(dx, dy);
}
