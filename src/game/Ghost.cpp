/*
 * Ghost.cpp
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#include "Ghost.h"

Ghost::Ghost(Node *startNode) : now(startNode)
{
	this->x = now->x;
	this->y = now->y;
	this->next = now;
	this->prev = now;
	dx = 0;
	dy = 0;
}

Ghost::~Ghost()
{
}

void Ghost::update(int x, int y)
{
	if (next == now->change_now(this->x, this->y))
	{

		int type = rand() % 8;
		if (type == 0 || type == 1)
		{
			setToPac(type, x, y);
		}
		else
		{

			while (true)
			{
				int nextN = rand() % next->neigbours_len;
				if (next->ne[nextN] != now)
				{
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
	}

	move();
}

std::pair<int, int> Ghost::getPos() const
{
	return std::make_pair(x + off_x, y + off_y);
}

void Ghost::move()
{
	if (now->check_move(dx, dy, x, y))
	{
		x += dx;
		y += dy;
	}
}

bool Ghost::setToPac(int type, int Px, int Py)
{
	if (type == 0)
	{
		float next_dx = (this->x - Px > 0.1) ? -1 : (this->x - Px < -0.1 ? 1 : 0);
		if (next_dx > 0)
		{
			for (int i = 0; i < next->neigbours_len; ++i)
			{
				if (next->ne[i]->x > x && next->ne[i]->y == next->y)
				{
					Node *a = next->ne[i];
					now = next;
					next = a;
					dx = next_dx;
					dy = 0;
					return false;
				}
			}
		}
		else if (next_dx < 0)
		{
			for (int i = 0; i < next->neigbours_len; ++i)
			{
				if (next->ne[i]->x < x && next->ne[i]->y == next->y)
				{
					Node *a = next->ne[i];
					now = next;
					next = a;
					dx = next_dx;
					dy = 0;
					return false;
				}
			}
		}
	}

	else if (type == 1)
	{
		float next_dy = (this->y - Py > 0.1) ? -1 : (this->y - Py < -0.1 ? 1 : 0);

		if (next_dy > 0)
		{
			for (int i = 0; i < next->neigbours_len; ++i)
			{
				if (next->ne[i]->y > y && next->ne[i]->x == next->x)
				{
					Node *a = next->ne[i];
					now = next;
					next = a;
					dy = next_dy;
					dx = 0;
					return false;
				}
			}
		}
		else if (next_dy < 0)
		{
			for (int i = 0; i < next->neigbours_len; ++i)
			{
				if (next->ne[i]->y < y && next->ne[i]->x == next->x)
				{
					Node *a = next->ne[i];
					now = next;
					next = a;
					dy = next_dy;
					dx = 0;
					return false;
				}
			}
		}
	}
	return true;
}
