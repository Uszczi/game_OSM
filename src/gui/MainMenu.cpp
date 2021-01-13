/*
 * MainMenu.cpp
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#include "MainMenu.h"
#include "../hardware/KeyMapping.h"

#include <string>
#include <vector>

constexpr unsigned MENU_WIDTH = 280;
constexpr unsigned MENU_HEIGHT = 400;

constexpr unsigned Y_TEXT_OFFSET = CHAR_SIZE_Y + 10;
constexpr unsigned X_TEXT_OFFSET = 20;

constexpr unsigned COLOR_BACKGROUND = 0x181818;
constexpr unsigned COLOR_HIGHTLIGHT = 0x696969;

MainMenu::MainMenu(const HighScore &highscores) :
	highScores(highscores),
	currentAction(MenuAction::Continue)
{

}

void MainMenu::drawTo(PaintDevice &outputDevice) const
{
	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = (outputDevice.getHeight() - MENU_HEIGHT)/2;

	outputDevice.drawRect(x0, y0, MENU_WIDTH, MENU_HEIGHT, COLOR_BACKGROUND); // Background

	if(isWatchingHighScores) {
		drawHighScores(outputDevice);
	} else {
		drawMainMenu(outputDevice);
	}
}

void MainMenu::drawMainMenu(PaintDevice &outputDevice) const
{
	static const std::vector<std::string> options = {
			"Continue", "New Game", "High Scores", "Exit"
	};

	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = (outputDevice.getHeight() - MENU_HEIGHT)/2;

	// Highlight selection
	outputDevice.drawRect(x0 + X_TEXT_OFFSET,
			y0 + ((int)currentAction + 1)*Y_TEXT_OFFSET,
			MENU_WIDTH - 2*X_TEXT_OFFSET,
			CHAR_SIZE_Y, COLOR_HIGHTLIGHT);

	int offset = 1;
	for(const auto& option: options)
	{
		outputDevice.drawText(option, x0 + X_TEXT_OFFSET, y0 + offset*Y_TEXT_OFFSET);
		++offset;
	}
}

void MainMenu::drawHighScores(PaintDevice &outputDevice) const
{
	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = (outputDevice.getHeight() - MENU_HEIGHT)/2;

	outputDevice.drawText("Score", x0 + X_TEXT_OFFSET, y0 + Y_TEXT_OFFSET);
	outputDevice.drawText("Date", x0 + 8*X_TEXT_OFFSET, y0 + Y_TEXT_OFFSET);

	unsigned offset = 2;
	for(const auto &score: highScores.readScores())
	{
		char timeString[12];
		std::strftime(timeString, sizeof(timeString), "%d-%m-%Y", std::localtime(&score.datetime));

		outputDevice.drawText(std::to_string(score.points), x0 + X_TEXT_OFFSET, y0 + offset*Y_TEXT_OFFSET);
		outputDevice.drawText(timeString, x0 + 8*X_TEXT_OFFSET, y0 + offset*Y_TEXT_OFFSET);
		++offset;
	}

	outputDevice.drawRect(x0 + X_TEXT_OFFSET,
			MENU_HEIGHT,
			MENU_WIDTH - 2*X_TEXT_OFFSET,
			CHAR_SIZE_Y, COLOR_HIGHTLIGHT);

	outputDevice.drawText("Return", x0 + X_TEXT_OFFSET, MENU_HEIGHT);
}


void MainMenu::processInput(int key)
{
	constexpr int ACTION_COUNT = 4;
	int actionIdx = (int)currentAction;

	switch(key)
	{
	case KEY_ENTER:
		if(isWatchingHighScores) {
			isWatchingHighScores = false;
		} else {
			invokeSelectedAction();
		}
		break;
	case ARROW_DOWN:
		currentAction = (MenuAction)((actionIdx + 1) % ACTION_COUNT);
		break;
	case ARROW_UP:
		if(actionIdx == 0)
			currentAction = (MenuAction)(ACTION_COUNT - 1);
		else
			currentAction = (MenuAction)(actionIdx - 1);
		break;
	default:
		break;
	}
}

void MainMenu::invokeSelectedAction()
{
	if(currentAction == MenuAction::Continue) {
		if(continueCallback) continueCallback();
	}
	else if(currentAction == MenuAction::NewGame) {
		if(newGameCallback) newGameCallback();
	}
	else if(currentAction == MenuAction::Exit) {
		if(exitCallback) exitCallback();
	}
	else if(currentAction == MenuAction::HighScores) {
		isWatchingHighScores = true;
	}
}
