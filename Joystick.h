#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

class Joystick {
private:
	uint8_t Hpin, Vpin, Cpin;
public:
	const uint8_t sensivity = 128;
	Joystick(uint8_t Hpin, uint8_t Vpin, uint8_t Cpin);
	// Values between 0-1023
	int getX();
	// Values between 0-1023
	int getY();
	void setClickInterruptRoutine(void(*routine)());
};

