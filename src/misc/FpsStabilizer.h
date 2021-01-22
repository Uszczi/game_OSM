/*
 * FpsStabilizer.h
 *
 *  Created on: 14 sty 2021
 *      Author: Adam
 */

#ifndef MISC_FPSSTABILIZER_H_
#define MISC_FPSSTABILIZER_H_

class FpsStabilizer
{
	float integrator = 0;

public:
	void applyDelay(float targetFPS, float currentFPS);
};

#endif /* MISC_FPSSTABILIZER_H_ */
