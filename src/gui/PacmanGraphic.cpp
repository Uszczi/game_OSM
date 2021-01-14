/*
 * PacmanGraphic.cpp
 *
 *  Created on: 13 sty 2021
 *      Author: Adam
 */

#include "PacmanGraphic.h"
#include "../game/Pacman.h"

PacmanGraphic::PacmanGraphic(const Pacman *pacman) :
	pacman(pacman),
	p_right(std::string("static/pacman_right.ppm")),
	p_left(std::string("static/pacman_left.ppm")),
	p_up(std::string("static/pacman_up.ppm")),
	p_down(std::string("static/pacman_down.ppm"))
{
	width = p_right.getWidth();
	height = p_right.getHeight();
}

void PacmanGraphic::drawTo(PaintDevice &paintDevice) const
{
	const auto pos = pacman->getPos();
	const auto v = pacman->getSpeed();

	if (v.first < 0){
		paintDevice.drawPixmap(p_left, pos.first, pos.second);
	} else if (v.second > 0){
		paintDevice.drawPixmap(p_down, pos.first, pos.second);
	} else if (v.second < 0){
		paintDevice.drawPixmap(p_up, pos.first, pos.second);
	} else {
		paintDevice.drawPixmap(p_right, pos.first, pos.second);
	}
}

Rect PacmanGraphic::boundingRect() const
{
	auto pos = pacman->getPos();
	return Rect(pos.first, pos.second, width, height);
}
