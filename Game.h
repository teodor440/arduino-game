#ifndef _GAME_h
#define _GAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Program.h"
#include "Audio.h"
#include <EEPROM.h>

#define RUNNING 0
#define PAUSED 1
#define WAITING_RESTART 2

#define GAME_WON 1
#define GAME_LOST 0

#define DIFFICULTY_EASY 1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD 3

class Game : public Program {
private:
	// Just tolerate this surplus global variable, just for the sake of a private joystick
	const uint8_t joystickSensivity;
	unsigned long speedAdjuster;
	unsigned long basisGameDelay = 1000;
protected:
	// Has methods to play sounds
	Audio speakers;

	uint8_t frameCount = 0;
	uint8_t gameStatus;
	
	uint8_t score = 0;

	virtual void init() = 0;
	virtual void onNewFrame() = 0;
	virtual void endGame(uint8_t) = 0;

	// Value should be the (power) from gesture interface
	void influenceSpeed(unsigned int value);
	void resetSpeed();
	// Change the basis game speed by a multiplier 
	void changeBasisPace(float);

	virtual uint8_t run();

	virtual void onButtonPressed();
public:
	Game(LedControl*, LiquidCrystal*, Joystick*, uint8_t button, uint8_t buzzerPin);
};

#endif

