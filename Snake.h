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

	Point generateRandomFood();
public:
	uint8_t direction;
	Snake(LedControl*, LiquidCrystal*, Joystick*, uint8_t button, uint8_t buzzerPin);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(unsigned int);
	virtual void onRightGesture(unsigned int);
	virtual void onUpGesture(unsigned int);
	virtual void onDownGesture(unsigned int);
};


#endif