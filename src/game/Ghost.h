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
#include <utility>

class Ghost {
private:
	void move();
	bool setToPac(int, int, int);
	int step=0;
public:
	float x, y, dx, dy;
	int off_x = -6, off_y = -8;
	Node *now;
	Node *next = nullptr;
	Node *prev = nullptr;
	Ghost(Node*);
	virtual ~Ghost();
	void update(int x, int y);
    std::pair<int, int> getPos() const;
};

#endif /* GAME_GHOST_H_ */
