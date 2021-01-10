/*
 * MainMenu.h
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "PaintDevice.h"
#include <functional>

enum class MenuAction
{
	Play = 0,
	HighScores,
	Exit
};

class MainMenu {
private:
	std::function<void()> playCallback;
	std::function<void()> exitCallback;

	MenuAction currentAction;
	bool isWatchingHighScores = false;

public:
	MainMenu();

	void setPlayCallback(const std::function<void()> &newCallback) {
		playCallback = newCallback;
	}

	void setExitCallback(const std::function<void()> &newCallback) {
		exitCallback = newCallback;
	}

	void parseKey(int key);
	void drawTo(PaintDevice &outputDevice) const;

private:
	void invokeSelectedAction();

	void drawMainMenu(PaintDevice &outputDevice) const;
	void drawHighScores(PaintDevice &outputDevice) const;
};

#endif /* MAINMENU_H_ */
