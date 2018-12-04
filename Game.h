#ifndef _GAME_h
#define _GAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Program.h"
#include <EEPROM.h>

#define RUNNING 0
#define PAUSED 1
#define WAITING_RESTART 2

#define GAME_WON 1
#define GAME_LOST 0

class Game : public Program {
private:
	// Just tolerate this surplus global variable, just for the sake of a private joystick
	const uint8_t joystickSensivity;
	unsigned long speedAdjuster;
	unsigned long basisGameDelay = 1000;
protected:
	uint8_t frameCount = 0;
	uint8_t game_status;
	
	uint8_t score = 0;

	virtual void init() = 0;
	virtual void onNewFrame() = 0;
	virtual void endGame(uint8_t) = 0;

	// Value should be the (power) from gesture interface
	virtual void influenceSpeed(unsigned int value);
	virtual void resetSpeed();
	// Change the basis game speed by a multiplier 
	virtual void changeBasisPace(float);
public:
	Game(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);
};

#endif

