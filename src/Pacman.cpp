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


Pacman::Pacman()
{
	x = 320;
	y = 270;
	direction = 0;
	next_direction = 0;
	dx = 0;
	dy = 0;
	now = 0;
}

void Pacman::draw()
{
	return;

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

void Pacman::setDirection(int key)
{
	switch(key)
	{
	case 106:
		if (now->check_move(1, 0, x, y))
		{
			dx = 1;
			dy = 0;
		}
		break;

	case 105:
		if (now->check_move(-1, 0, x, y))
		{
			dx = -1;
			dy = 0;
		}
		break;
	case 103:
		if (now->check_move(0, -1, x, y))
		{
			dx = 0;
			dy = -1;
		}
		break;

	case 108:
		if (now->check_move(0, 1, x, y))
		{
			dx = 0;
			dy = 1;
		}
		break;
	}
}


