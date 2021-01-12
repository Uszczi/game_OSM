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
	int off_x = -9, off_y = -8;
    int dx, dy;
    int next_dx, next_dy;
	Node * now;
private:
    int direction;
    int next_direction;
public:
	Pacman();

	void draw();
	void update();
    void setDirection(int key);

};

#endif /* PACMAN_H_ */
