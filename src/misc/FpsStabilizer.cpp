/*
 * FpsStabilizer.cpp
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#include "FpsStabilizer.h"

#include <cmath>
#include <unistd.h>

void FpsStabilizer::applyDelay(float targetFPS, float currentFPS)
{
	const float k = 20, Ti = 0.2;
	float err = currentFPS - targetFPS;

	integrator += k*err/(Ti*currentFPS);
	integrator = std::fmin(std::fmax(0, integrator), 12000);

	float delay = k*err + integrator;
	delay = std::fmin(std::fmax(0, delay), 16000);

	usleep(static_cast<int>(delay));
}
