#ifndef _GAME_h
#define _GAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

#include "Program.h"

class Game : public Program {
protected:
	bool shutdownTrigger = false;
	uint8_t frameCount = 0;
public:
	Game(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);
	virtual void init() = 0;
	virtual void onNewFrame() = 0;
};
