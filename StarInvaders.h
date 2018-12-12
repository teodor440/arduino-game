#ifndef _STARINVADERS_h
#define _STARINVADERS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Game.h"

class StarInvaders : public Game {
private:
	struct Ball {
		Point location;
		uint8_t direction;
		Ball(Point location, uint8_t direction);
		Ball();
		bool operator==(const Ball&);
	};

	int highScoreAddress = 0x1;

	Point spaceship;
	uint8_t direction;
	LinkedList<Ball> ballz;
	bool shouldFire;
	uint8_t lifes;

	uint8_t difficulty;
	unsigned long acceptInputInterval;

	// Pretty much the animation of moving dots
	void moveBalls();
	// Fire from player spaceship
	void launchProjectile(uint8_t);
	// Check if balls collide
	void processBallsInteraction();
	// Rains some light upon the player's soul
	void generateProjectile();
protected:
	virtual void init();
	virtual void onNewFrame();
	virtual void endGame(uint8_t);
public:
	StarInvaders(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick*, uint8_t button, uint8_t buzzerPin);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(unsigned int);
	virtual void onRightGesture(unsigned int);
	virtual void onUpGesture(unsigned int);
	virtual void onDownGesture(unsigned int);
};

#endif