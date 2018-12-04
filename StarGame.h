#ifndef _STARGAME_h
#define _STARGAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Game.h"

class Star : public Game {
protected:
	virtual void init();
	virtual void onNewFrame();
	virtual void endGame(uint8_t);

	virtual void addToSpeed(uint8_t);
	virtual void resetSpeed();
public:
	Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick*, uint8_t button);

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