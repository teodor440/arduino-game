#include "Program.h"

Program::Program(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Interactionable(joystick, button) {
	this->matrixcontroller = matctrl;
	this->lcdcontroller = ledctrl;

	this->lastMillis = millis();
}

void Program::printMessage(String message, uint8_t row = 0) {
	#ifdef DEBUGGING_SNAKE
	Serial.print("Printed on lcd " + message + " on row " + row);
	#endif
	this->lcdcontroller->setCursor(0, row);
	char blank[LCD_COLS + 1];
	for (int i = 0; i < LCD_COLS; i++) blank[i] = ' ';
	blank[LCD_COLS] = 0;
	this->lcdcontroller->print(blank);

	this->lcdcontroller->setCursor(0, row);
	this->lcdcontroller->print(message);
}

void Program::clearConsole() {
	#ifdef DEBUGGING_SNAKE
	Serial.println("Console cleared");
	#endif
	this->lcdcontroller->clear();
	this->lcdcontroller->setCursor(0, 0);
}

Program::~Program() {
	this->detachJoystickClickInterrupt();
}
