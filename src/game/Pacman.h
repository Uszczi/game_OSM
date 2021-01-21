/*
 * Pacman.h
 *
 *  Created on: 4 sty 2021
 *      Author: Materusz
 */

#ifndef PACMAN_H
#define PACMAN_H

#include "Node.h"
#include <utility>

enum class PacmanDirection {
	NoMove,
	Up,
	Down,
	Left,
	Right
};

class Pacman {
private:
	Node *now;
	std::pair<Node*, Node*> tunnelNodes;
	int off_x = -9, off_y = -8;

	int x, y;
    int dx, dy;
    int next_dx;
    int	next_dy;

    int direction;
    int next_direction;
public:
	Pacman(Node *startNode, std::pair<Node*, Node*> tunnelNodes);
	static PacmanDirection keyToDirection(int key);

	Node *currentNode() const {
		return now;
	}

	void update();
    void setDirection(PacmanDirection direction);

    std::pair<int, int> getPos() const;
    std::pair<int, int> getSpeed() const;

private:
    bool isInTunnel() const;
    void teleportIfNeeded();
};

#endif /* PACMAN_H_ */
