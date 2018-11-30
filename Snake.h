#ifndef _SNAKE_h
#define _SNAKE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

#include "Game.h"

class Snake : public Game {
private:
	LinkedList<Point> tail;
	Point food;
public:
	uint8_t direction;
	Snake(LedControl*, LiquidCrystal*, Joystick*, uint8_t button, uint8_t start_x, uint8_t start_y);
	LinkedList<Point> getSnake();
	LinkedList<Point> getFoodAsDrawable();

	virtual void init();
	virtual void onNewFrame();

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(uint8_t);
	virtual void onRightGesture(uint8_t);
	virtual void onUpGesture(uint8_t);
	virtual void onDownGesture(uint8_t);
	virtual void onButtonPressed();

	virtual uint8_t run();
};
