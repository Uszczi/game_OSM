/*
 * MainMenu.cpp
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#include "MainMenu.h"
#include "KeyMapping.h"

#include <string>
#include <iostream>

constexpr unsigned MENU_WIDTH = 280;
constexpr unsigned MENU_HEIGHT = 400;

constexpr unsigned Y_TEXT_OFFSET = CHAR_SIZE_Y + 10;
constexpr unsigned X_TEXT_OFFSET = 20;

constexpr unsigned COLOR_BACKGROUND = 0x181818;
constexpr unsigned COLOR_HIGHTLIGHT = 0x696969;

MainMenu::MainMenu() :
	currentAction(MenuAction::Play)
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
	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = (outputDevice.getHeight() - MENU_HEIGHT)/2;

	// Highlight selection
	outputDevice.drawRect(x0 + X_TEXT_OFFSET,
			y0 + ((int)currentAction + 1)*Y_TEXT_OFFSET,
			MENU_WIDTH - 2*X_TEXT_OFFSET,
			CHAR_SIZE_Y, COLOR_HIGHTLIGHT);

	outputDevice.drawText("Play", x0 + X_TEXT_OFFSET, y0 + Y_TEXT_OFFSET);
	outputDevice.drawText("High Scores", x0 + X_TEXT_OFFSET, y0 + 2*Y_TEXT_OFFSET);
	outputDevice.drawText("Exit", x0 + X_TEXT_OFFSET, y0 + 3*Y_TEXT_OFFSET);
}

void MainMenu::drawHighScores(PaintDevice &outputDevice) const
{
	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = MENU_HEIGHT;

	// Highlight selection
	outputDevice.drawRect(x0 + X_TEXT_OFFSET,
			y0,
			MENU_WIDTH - 2*X_TEXT_OFFSET,
			CHAR_SIZE_Y, COLOR_HIGHTLIGHT);

	outputDevice.drawText("Return", x0 + X_TEXT_OFFSET, y0);
}


void MainMenu::parseKey(int key)
{
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
		currentAction = (MenuAction)((actionIdx + 1) % 3);
		break;
	case ARROW_UP:
		if(actionIdx == 0)
			currentAction = (MenuAction)(2);
		else
			currentAction = (MenuAction)(actionIdx - 1);
		break;
	default:
		break;
	}
}

void MainMenu::invokeSelectedAction()
{
	if(currentAction == MenuAction::Play) {
		if(playCallback) playCallback();
	}
	else if(currentAction == MenuAction::Exit) {
		if(exitCallback) exitCallback();
	}
	else if(currentAction == MenuAction::HighScores) {
		isWatchingHighScores = true;
	}
}
