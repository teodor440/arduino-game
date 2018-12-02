#ifndef _SNAKE_h
#define _SNAKE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Game.h"

#define GAME_COUNT 2
#define SNAKE 2
#define STAR 3
#define PROGRAM_SELECTOR 1
#define CURRENT_PROGRAM 0

#define SNAKE_BASIS_DELAY 1000

// #define DEBUGGING_SNAKE 1

class Snake : public Game {
private:
	int highScoreAddress = 0x0;

	LinkedList<Point> tail;
	Point food;
	uint8_t lastDirection;

	int freeSpaces = 64;
	// The shadow of the snake without the food ofc
	uint8_t matrixMap[8][8];

	virtual void init();
	virtual void onNewFrame();
	virtual void endGame(uint8_t);

	virtual void addToSpeed(uint8_t);
	virtual void resetSpeed();

	Point generateRandomFood();
public:
	uint8_t direction;
	Snake(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);

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