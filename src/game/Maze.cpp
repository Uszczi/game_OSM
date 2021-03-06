/*
 * Maze.cpp
 *
 *  Created on: 9 sty 2021
 *      Author: mateu
 */

#include "Maze.h"
#include "Node.h"

static const std::vector<std::pair<int, int>> nodePoints = {
		{124, 22}, {204, 22}, {296, 22}, {124, 84},
		{204, 84}, {250, 84}, {296, 84}, {124, 132}, {204, 132},
		{250, 132}, {296, 132}, {250, 170}, {296, 170}, {204, 220},
		{250, 220}, {250, 270}, {124, 316}, {204, 316}, {250, 316},
		{296, 316}, {124, 362}, {158, 362}, {204, 362}, {250, 362},
		{296, 362}, {124, 412}, {158, 412}, {204, 412}, {250, 412},
		{296, 412}, {124, 458}, {296, 458}, {516, 22}, {436, 22},
		{344, 22}, {516, 84}, {436, 84}, {390, 84}, {344, 84},
		{516, 132}, {436, 132}, {390, 132}, {344, 132}, {390, 170},
		{344, 170}, {436, 220}, {390, 220}, {390, 270}, {516, 316},
		{436, 316}, {390, 316}, {344, 316}, {516, 362}, {482, 362},
		{436, 362}, {390, 362}, {344, 362}, {516, 412}, {482, 412},
		{436, 412}, {390, 412}, {344, 412}, {516, 458}, {344, 458},
		{320, 270}
};

static const std::vector<std::pair<int, int>> additionalPoints = {
		{144, 22}, {496, 22}, {164, 22}, {476, 22}, {184, 22}, {456, 22},
		{124, 42}, {516, 42}, {124, 62}, {516, 62}, {224, 22}, {416, 22},
		{244, 22}, {396, 22}, {264, 22}, {376, 22}, {204, 42}, {436, 42},
		{204, 62}, {436, 62}, {296, 42}, {344, 42}, {296, 62}, {344, 62},
		{144, 84}, {496, 84}, {164, 84}, {476, 84}, {184, 84}, {456, 84},
		{124, 104}, {516, 104}, {224, 84}, {416, 84}, {204, 104}, {436, 104},
		{270, 84}, {370, 84}, {250, 104}, {390, 104}, {144, 132}, {496, 132},
		{164, 132}, {476, 132}, {184, 132}, {456, 132}, {204, 152}, {436, 152},
		{204, 172}, {436, 172}, {204, 192}, {436, 192}, {270, 132}, {370, 132},
		{270, 170}, {370, 170}, {250, 190}, {390, 190}, {224, 220}, {416, 220},
		{204, 240}, {436, 240}, {204, 260}, {436, 260}, {204, 280}, {436, 280},
		{250, 240}, {390, 240}, {250, 290}, {390, 290}, {144, 316}, {496, 316},
		{164, 316}, {476, 316}, {184, 316}, {456, 316}, {124, 336}, {516, 336},
		{224, 316}, {416, 316}, {204, 336}, {436, 336}, {270, 316}, {370, 316},
		{296, 336}, {344, 336}, {158, 382}, {482, 382}, {224, 362}, {416, 362},
		{204, 382}, {436, 382}, {270, 362}, {370, 362}, {250, 382}, {390, 382},
		{124, 432}, {516, 432}, {178, 412}, {462, 412}, {270, 412}, {370, 412},
		{296, 432}, {344, 432}, {144, 458}, {496, 458}, {164, 458}, {476, 458},
		{184, 458}, {456, 458}, {204, 458}, {436, 458}, {224, 458}, {416, 458},
		{244, 458}, {396, 458}, {264, 458}, {376, 458}
};

static const std::vector<std::vector<int>> connections = {
		{1, 3}, {2, 4}, {6}, {4, 7}, {5, 8}, {6, 9},
		{38}, {8}, {13}, {10}, {12}, {12, 14}, {44},
		{14, 17}, {15}, {18}, {17, 20}, {18, 22}, {19},
		{24}, {21}, {26}, {23, 27}, {24, 28}, {56},
		{26, 30}, {27}, {}, {29}, {31}, {31}, {63},
		{33, 35}, {34, 36}, {38}, {36, 39}, {37, 40},
		{38, 41}, {}, {40}, {45}, {42}, {44}, {44, 46},
		{}, {46, 49}, {47}, {50}, {49, 52}, {50, 54},
		{51}, {56}, {53}, {58}, {55, 59}, {56, 60},
		{}, {58, 62}, {59}, {}, {61}, {63}, {63}, {},
		{15, 47}
};

Maze::Maze()
{
	nodes.reserve(nodePoints.size());

	for(const auto& coord: nodePoints) {
		nodes.push_back(new Node(coord.first, coord.second));
	}

	int index = 0;
	for(const auto& neighbours : connections)
	{
		for(const auto& neighbour : neighbours)
			nodes[index]->add(nodes[neighbour]);
		++index;
	}
}

Maze::~Maze()
{
	for(auto &node: nodes)
		delete node;
}

Node* Maze::start() const
{
	return nodes.back();
}

const std::vector<std::pair<int, int> >& Maze::getAdditionalPoints() const
{
	return additionalPoints;
}

const std::vector<std::pair<int, int> >& Maze::getNodePoints() const
{
	return nodePoints;
}

Node* Maze::getNode(int i) const
{
	return nodes[i];
}

std::pair<Node*, Node*> Maze::tunnelNodes() const
{
	return std::make_pair(nodes[13], nodes[45]);
}
