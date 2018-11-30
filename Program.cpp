#include "Program.h"

Program::Program(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Interactionable(joystick, button) {
	this->matrixcontroller = matctrl;
	this->lcdcontroller = ledctrl;

	this->lastMillis = millis();
}

void Program::printMessage(String message, uint8_t row = 0) {
	Serial.print("Printed on lcd " + message + " on row " + row);

	this->lcdcontroller->setCursor(0, row);
	char blank[lcd_cols + 1];
	for (int i = 0; i < lcd_cols; i++) blank[i] = ' ';
	blank[lcd_cols] = 0;
	this->lcdcontroller->print(blank);

	this->lcdcontroller->setCursor(0, row);
	this->lcdcontroller->print(message);
}

void Program::clearConsole() {
	Serial.println("Console cleared");
	this->lcdcontroller->clear();
	this->lcdcontroller->setCursor(0, 0);
}

Program::~Program() {

}
