/*
 * PacmanGraphic.h
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#ifndef GUI_PACMANGRAPHIC_H_
#define GUI_PACMANGRAPHIC_H_

#include "GraphicObject.h"
#include "PPMPixmap.h"

class Pacman;

class PacmanGraphic : GraphicObject {
	const Pacman *pacman;

	PPMPixmap p_right;
	PPMPixmap p_left;
	PPMPixmap p_up;
	PPMPixmap p_down;

public:
	PacmanGraphic(const Pacman *pacman);
	virtual void drawTo(PaintDevice &paintDevice) const override;
};

#endif /* GUI_PACMANGRAPHIC_H_ */
