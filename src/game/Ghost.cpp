/*
 * Ghost.cpp
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#include "Ghost.h"

Ghost::Ghost(Node *startNode) :
	now(startNode)
{
	this->x = now->x;
	this->y = now->y;

	dx = 0;
	dy = 0;
}

Ghost::~Ghost() {

}


//void Ghost::update(Node * pacmanNow){
//	for(int i = 0; i < 1000; i++){
//
//	}
//}

void Ghost::update(int x, int y)
{
	now = now->change_now(x, y);
	int next_dx = 0;
	int next_dy = 0;



		if (x > this->x) {
			next_dx = 1;
		} else next_dx = 0;
		if (y > this->y) {
			next_dy = 1;
		} else next_dy = 0;


		if (now->check_move(next_dx, next_dy, this->x, this->y))
		{
			dx = next_dx;
			dy = next_dy;
		}

		if (now->check_move(dx, dy, this->x, this->y))
		{
			this->x += dx;
			this->y += dy;

		}

}
