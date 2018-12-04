#ifndef _INTERACTIONABLE_h
#define _INTERACTIONABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Utils.h"
#include "Joystick.h"

// #define DEBUGGING_MENU 1

#define DIRECTION_NONE 0
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4
class Interactionable {
private:
	Joystick* joystick;
	uint8_t quit_btn;
protected:
	uint8_t nextDirection = DIRECTION_NONE;
public:
	static uint8_t clickCount;
	static uint8_t btn_pressed;

	Interactionable(Joystick*, uint8_t button);
	virtual void onClick() = 0;
	virtual void onDoubleClick() = 0;
	virtual void onLeftGesture(unsigned int) = 0;
	virtual void onRightGesture(unsigned int) = 0;
	virtual void onUpGesture(unsigned int) = 0;
	virtual void onDownGesture(unsigned int) = 0;
	virtual void onButtonPressed() = 0;

	// CALL THIS LITTLE FAT BOY WHEN RUNNING ANY FUCKING PROGRAM 
	void processInput();

	// public interrupts methods
	static void handleClickInterrupt();
	static void handleButtonInterrupt();
};

#endif