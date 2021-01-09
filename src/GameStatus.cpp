/*
 * GameStatus.cpp
 *
 *  Created on: 9 sty 2021
 *      Author: Adam
 */

#include "GameStatus.h"

#include <fstream>

GameStatus::GameStatus(int playerLife) :
	lifeCount(playerLife)
{

}

bool GameStatus::saveToFile(const std::string &filename) const
{
	std::ofstream save(filename);

	if(save.bad())
		return false;

	save << lifeCount << " "
			<< points << " "
			<< level;

	return true;
}

bool GameStatus::restoreFromFile(const std::string &filename)
{
	std::ifstream save(filename);

	if(save.bad())
		return false;

	save >> lifeCount;
	save >> points;
	save >> level;

	return true;
}
