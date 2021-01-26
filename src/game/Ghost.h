/*
 * Ghost.h
 *
 *  Created on: 19 sty 2021
 *      Author: mateu
 */

#ifndef GAME_GHOST_H_
#define GAME_GHOST_H_
#include "Node.h"
#include <stdlib.h>

class Ghost {
public:
	float x, y, dx, dy;
	Node *now;
	Node *next = nullptr;
	Node *prev = nullptr;
	Ghost(Node*);
	virtual ~Ghost();
	void update(int x, int y);
};

#endif /* GAME_GHOST_H_ */
