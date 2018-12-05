#ifndef _GAMESELECTOR_h
#define _GAMESELECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Program.h"

// Just as a reminder coord len shouldnt be less than 2
#define COORDINATES_LENGTH 12
#define NAN 64
// TODO DRAW SHIT ON MATRIX
class GameSelector : Program {
private:
	const uint8_t gamesCount = GAME_COUNT;
	String gameNames[GAME_COUNT] = { "Snake", "Star Invaders" };
	uint8_t gamesMapCodes[GAME_COUNT] = { SNAKE, STAR };
	uint8_t images[GAME_COUNT][COORDINATES_LENGTH] = {
		{2, 1, 2, 2, 3, 2, 4, 2, 4, 3, 4, 5},
		{0, 2, 0, 3, 0, 4, 1, 3, 3, 5, 7, 1}
	};

	uint8_t currentSelectedIndex;
	// A flag whether the matrix should be turned on or off
	bool blinkingState = true;
	unsigned long blinkingInterval = 250;
	unsigned long lastBlink;

	void changeState(uint8_t state_index);
	void advanceState();
public:
	GameSelector(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(unsigned int);
	virtual void onRightGesture(unsigned int);
	virtual void onUpGesture(unsigned int);
	virtual void onDownGesture(unsigned int);
	virtual void onButtonPressed();

	virtual uint8_t run();
};

#endif