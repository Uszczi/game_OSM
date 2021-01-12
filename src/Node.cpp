/*
 * Node.cpp
 *
 *  Created on: 9 sty 2021
 *      Author: mateu
 */

#include "Node.h"

Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
	ne[0] = 0;
	ne[1] = 0;
	ne[2] = 0;
	ne[3] = 0;
}

Node::~Node() {

}

void Node::add(Node *n)
{
	ne[neigbours_len] = n;
	neigbours_len++;

	n->ne[n->neigbours_len] = this;
	n->neigbours_len++;
}



bool Node::check_move(int dx, int dy, int x, int y)
{
	for (int i = 0; i < neigbours_len; i++)
	{
		if ((dx > 0) && (x < ne[i]->x) && (y == ne[i]->y)) return true; // Right
		if ((dx < 0) && (x > ne[i]->x) && (y == ne[i]->y)) return true; // Left
		if ((dy > 0) && (y < ne[i]->y) && (x == ne[i]->x)) return true; // Bottom
		if ((dy < 0) && (y > ne[i]->y) && (x == ne[i]->x)) return true; // Upper
	}

	if ((dx > 0) && (x < this->x)) return true;
	if ((dx < 0) && (x > this->x)) return true;
	if ((dy > 0) && (y < this->y)) return true;
	if ((dy < 0) && (y > this->y)) return true;

	return false;
}


Node * Node::change_now(int x, int y)
{
	for (int i = 0; i < neigbours_len; i++)
	{
		if ((x == ne[i]->x) && (y == ne[i]->y)) return ne[i];
	}

	return this;
}



