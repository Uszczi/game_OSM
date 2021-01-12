/*
 * Node.h
 *
 *  Created on: 9 sty 2021
 *      Author: mateu
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>


class Node {
public:
	int x, y;
	Node(int x , int  y);
	int neigbours_len=0;
	Node * ne[4];
	virtual ~Node();
	void add(Node *);
	bool check_move(int, int, int, int);
	Node *  change_now(int, int);
};

#endif /* NODE_H_ */
