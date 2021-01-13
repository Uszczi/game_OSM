/*
 * Maze.h
 *
 *  Created on: 9 sty 2021
 *      Author: mateu
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <vector>

class Node;

class Maze
{
	std::vector<Node*> nodes;

public:
	Maze();
	virtual ~Maze();

	Node* start() const;
};

#endif /* MAZE_H_ */
