/*
 * HighScore.h
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <chrono>

#include <utility>
#include <list>
#include <string>

constexpr unsigned MAX_SAVED_SCORES = 8;

struct HighScoreEntry
{
	int points = 0;
	std::time_t datetime = 0;

	bool operator<(const HighScoreEntry &other) const {
		return points < other.points;
	}
};

class HighScore
{
	std::string outputFilename;
	std::list<HighScoreEntry> highScores;

public:
	HighScore(const std::string &highScoreFile);

	const std::list<HighScoreEntry> &readScores() const {
		return highScores;
	}

	void addEntry(int points);
	void save() const;

private:
	void sortScores();
};

#endif /* HIGHSCORE_H_ */
