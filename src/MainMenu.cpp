/*
 * MainMenu.cpp
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#include "MainMenu.h"
#include <string>

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::drawTo(PaintDevice &outputDevice) const
{
	constexpr unsigned MENU_WIDTH = 280;
	constexpr unsigned MENU_HEIGHT = 400;

	const unsigned x0 = (outputDevice.getWidth() - MENU_WIDTH)/2;
	const unsigned y0 = (outputDevice.getHeight() - MENU_HEIGHT)/2;

	outputDevice.drawRect(x0, y0, MENU_WIDTH, MENU_HEIGHT, 0x181818);

	constexpr unsigned Y_OFFSET = CHAR_SIZE_Y + 10;
	constexpr unsigned X_OFFSET = 20;

	outputDevice.drawText("Play", x0 + X_OFFSET, y0 + Y_OFFSET);
	outputDevice.drawText("High Scores", x0 + X_OFFSET, y0 + 2*Y_OFFSET);
	outputDevice.drawText("Exit", x0 + X_OFFSET, y0 + 3*Y_OFFSET);
}
