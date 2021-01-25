/*
 * Maze.h
 *
 *  Created on: 9 sty 2021
 *      Author: mateu
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <utility>

class Node;

class Maze
{
	std::vector<Node*> nodes;

public:
	Maze();
	virtual ~Maze();

	Node* start() const;
	Node* getNode(int) const;

	const std::vector<std::pair<int, int>> &getAdditionalPoints() const;
	const std::vector<std::pair<int, int>> &getNodePoints() const;
};

#endif /* MAZE_H_ */
