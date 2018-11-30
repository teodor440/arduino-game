#ifndef _GAMESELECTOR_h
#define _GAMESELECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Program.h"

// TODO DRAW SHIT ON MATRIX
class GameSelector : Program {
private:
	const uint8_t gamesCount = GAME_COUNT;
	String gameNames[GAME_COUNT] = { "Snake", "Star Shit" };
	uint8_t gamesMapCodes[GAME_COUNT] = { SNAKE, STAR };
	uint8_t images[GAME_COUNT][30] = {
		{0, 0},
		{1, 1}
	};

	uint8_t currentSelectedIndex;

	void changeState(uint8_t state_index);
	void advanceState();
public:
	GameSelector(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(uint8_t);
	virtual void onRightGesture(uint8_t);
	virtual void onUpGesture(uint8_t);
	virtual void onDownGesture(uint8_t);
	virtual void onButtonPressed();

	virtual uint8_t run();
};

#endif