/*
 * Pacman.cpp
 *
 *  Created on: 4 sty 2021
 *      Author: Mateusz
 */

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

Pacman::Pacman(Node *startNode, std::pair<Node*, Node*> tunnelNodes) :
	now(startNode),
	tunnelNodes(tunnelNodes)
{
	x = startNode->x;
	y = startNode->y;

	dx = 0;
	dy = 0;

	next_dx = 0;
	next_dy = 0;

	direction = 0;
	next_direction = 0;
}

void Pacman::update(double dt)
{
	int iter = boostTime <= 1 ? 1 : boostTime;
	boostTime -= dt;

	for(int i = 0; i < iter; ++i) {
		now = now->change_now(x, y);

		if (now->check_move(next_dx, next_dy, x, y))
		{
			dx = next_dx;
			dy = next_dy;
		}
		else if(isInTunnel())
		{
			dx = (next_dx != 0) ? next_dx : dx;
			dy = 0;
		}

		if (now->check_move(dx, dy, x, y))
		{
			x += dx;
			y += dy;
		}
		else if(isInTunnel())
		{
			teleportIfNeeded();
			x += dx;
		}
	}
}

void Pacman::setDirection(PacmanDirection direction)
{
	switch(direction)
	{
	case PacmanDirection::Right:
		next_dx = 1;
		next_dy = 0;
		break;

	case PacmanDirection::Left:
		next_dx = -1;
		next_dy = 0;
		break;

	case PacmanDirection::Up:
		next_dx = 0;
		next_dy = -1;
		break;

	case PacmanDirection::Down:
		next_dx = 0;
		next_dy = 1;
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

bool Pacman::isInTunnel() const
{
	const int tunnelY = tunnelNodes.first->y;
	return (y == tunnelY && x <= tunnelNodes.first->x) ||
			(y == tunnelY && x >= tunnelNodes.second->x);
}

void Pacman::teleportIfNeeded()
{
	if(x < 115)
	{
		x = 528;
		dx = -dx;

		now = tunnelNodes.second;
	}
	else if (x > 528)
	{
		x = 115;
		dx = -dx;

		now = tunnelNodes.first;
	}
}

void Pacman::teleport(Node* node, int newX, int newY)
{
	dx = dy = 0;
	next_dx = next_dy = 0;

	x = newX > 0 ? newX : node->x;
	y = newY > 0 ? newY : node->y;

	now = node;
}
