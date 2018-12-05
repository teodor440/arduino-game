#ifndef _STARGAME_h
#define _STARGAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Game.h"

class Star : public Game {
private:
	struct Ball {
		Point location;
		uint8_t direction;
		Ball(Point location, uint8_t direction);
		Ball();
	};

	Point spaceship;
	uint8_t direction;
	LinkedList<Ball> ballz;
	bool shouldFire;
	uint8_t lifes;

	// Pretty much the animation of moving dots
	void moveBalls();
	// Fire from player spaceship
	void launchProjectile(uint8_t);
	// Check if balls collide
	void processBallsInteraction();
	// Create random new balls coming to attack player
	void generateProjectile();
protected:
	virtual void init();
	virtual void onNewFrame();
	virtual void endGame(uint8_t);
public:
	Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick*, uint8_t button);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(unsigned int);
	virtual void onRightGesture(unsigned int);
	virtual void onUpGesture(unsigned int);
	virtual void onDownGesture(unsigned int);
};

#endif