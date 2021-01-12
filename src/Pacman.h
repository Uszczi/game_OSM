/*
 * Pacman.h
 *
 *  Created on: 4 sty 2021
 *      Author: Materusz
 */

#ifndef PACMAN_H
#define PACMAN_H
#include "Node.h"
#include <stdio.h>
class Pacman {
public:
	int x, y;
	Node * now;
private:
    int direction;
    int next_direction;
    int dx, dy;
public:
	Pacman();

	void draw();
	void update();
    void setDirection(int key);

};

#endif /* PACMAN_H_ */
