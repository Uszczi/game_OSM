/*
 * MainMenu.h
 *
 *  Created on: 10 sty 2021
 *      Author: Adam
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "PaintDevice.h"

class MainMenu {
private:

public:
	MainMenu();
	virtual ~MainMenu();

	void drawTo(PaintDevice &outputDevice) const;
};

#endif /* MAINMENU_H_ */
