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
	this->next = now;
	this->prev = now;
	dx = 0;
	dy = 0;


}

Ghost::~Ghost() {

}


void Ghost::update(int x, int y)
{
	if (next == now->change_now(this->x, this->y)){
//		now = now->change_now(this->x, this->y);

		while(true){
		int nextN = rand() % next->neigbours_len;
		if (next->ne[nextN] != now){
			now = next;
			next = next->ne[nextN];
			}


		float next_dx = (this->x - next->x > 0.1) ? -1 : (this->x - next->x < -0.1 ? 1 : 0);
		float next_dy = (this->y - next->y > 0.1) ? -1 : (this->y - next->y < -0.1 ? 1 : 0);


		if (now->check_move(next_dx, next_dy, this->x, this->y))
		{
			dx = next_dx;
			dy = next_dy;
		break;
		}
		}

	}


	if (now->check_move(dx, dy, this->x, this->y))
	{
		this->x += dx;
		this->y += dy;
	}
}
