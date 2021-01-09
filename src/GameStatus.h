/*
 * GameStatus.h
 *
 *  Created on: 9 sty 2021
 *      Author: Adam
 */

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include <string>

class GameStatus
{
	int lifeCount;
	int points = 0;
	int level = 1;

public:
	GameStatus(int playerLife = 3);

	bool saveToFile(const std::string &filename) const;
	bool restoreFromFile(const std::string &filename);

	int getPoints() const {
		return points;
	}

	void addPoints(int pointCount) {
		points += pointCount;
	}

	int getLifeCount() const {
		return lifeCount;
	}

	void addLife() {
		++lifeCount;
	}

	void takeLife() {
		--lifeCount;
	}

	int getLevel() const {
		return level;
	}

	void increaseLevel() {
		++level;
	}

};

#endif /* GAMESTATUS_H_ */
