/*
 * InputDevice.h
 *
 *  Created on: 4 sty 2021
 *      Author: Adam
 */

#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_

class InputDevice {
private:
	int inputEventsFD;

public:
	InputDevice();
	virtual ~InputDevice();

	int getKey();
};

#endif /* INPUTDEVICE_H_ */
