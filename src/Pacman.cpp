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
    x = 311;
    y = 262;
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
	if (now->check_move(dx, dy))
	{
		x += dx;
		y += dx;
	}

}

void Pacman::setDirection(int key)
{
	 switch(key)
	 {
	 case 106:
	 	dx++;
	 	dy = 0;
	 	break;

	 case 105:
	 	dx--;
	 	dy = 0;
	 	break;
	 case 103:
		 dx = 0;
	 	dy--;
	 	break;

	 case 108:
		dx = 0;
	 	dy++;
	 	break;
	 }
}


