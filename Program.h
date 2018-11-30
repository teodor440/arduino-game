#ifndef _PROGRAM_h
#define _PROGRAM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include "Interactionable.h"
#include "LedControl.h"
#include <LiquidCrystal.h>

#define NULL 0
#define null_ptr 0

#define lcd_cols 16
#define lcd_rows 2

class Program : public Interactionable {
protected:
	LedControl* matrixcontroller = nullptr;
	LiquidCrystal* lcdcontroller = nullptr;

	unsigned long lastMillis;
	unsigned long delayPeriod = 100;
	bool shutdownTrigger = false;
public:
	Program(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);
	// run should be called from an external source whenever there is processing power for that
	virtual uint8_t run() = 0;

	void printMessage(String, uint8_t row = 0);
	void clearConsole();

	virtual ~Program();
};