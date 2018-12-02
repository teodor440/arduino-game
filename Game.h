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

#define GAME_WON 1
#define GAME_LOST 0

class Game : public Program {
protected:
	uint8_t frameCount = 0;
	uint8_t game_status = PAUSED;
	
	uint8_t score = 0;

	virtual void init() = 0;
	virtual void onNewFrame() = 0;
	virtual void endGame(uint8_t) = 0;

	// Value should be the (power) from gesture interface
	virtual void addToSpeed(uint8_t value) = 0;
	virtual void resetSpeed() = 0;
public:
	Game(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);
};

#endif

