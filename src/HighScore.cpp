/*
 * HighScore.cpp
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#include "HighScore.h"
#include <fstream>
#include <sstream>

#include <algorithm>

HighScore::HighScore(const std::string &highScoreFile) :
	outputFilename(highScoreFile)
{
	std::ifstream savedScores(highScoreFile);
	unsigned readScores = 0;

	while(!savedScores.eof() && readScores++ < MAX_SAVED_SCORES)
	{
		std::string score;
		std::getline(savedScores, score);
		std::stringstream scoreStream(score);

		HighScoreEntry entry;
		scoreStream >> entry.points;
		scoreStream >> entry.datetime;

		if(entry.points > 0)
			highScores.push_back(std::move(entry));
	}

	sortScores();
}

void HighScore::sortScores()
{
	// Sort from highest to lowest points
	highScores.sort();
	highScores.reverse();
}

void HighScore::save() const
{
	std::ofstream savedScores(outputFilename);

	for(const auto& score : highScores)
	{
		savedScores << score.points << " "
					<< score.datetime << "\n";
	}
}

void HighScore::addEntry(int points)
{
	if(highScores.size() >= MAX_SAVED_SCORES)
		highScores.pop_back();

	HighScoreEntry entry;
	entry.points = points;
	entry.datetime = std::time(nullptr);

	highScores.push_back(std::move(entry));
	sortScores();
}


