#include "StarGame.h"

Star::Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Game(matctrl, ledctrl, joystick, button) {

}

void Star::init() {}

void Star::onNewFrame() {}

uint8_t Star::run() {

	if (this->shutdownTrigger) return PROGRAM_SELECTOR;
	return PROGRAM_SELECTOR;
}

void Star::addToSpeed(uint8_t value) {
	// TODO
}

void Star::resetSpeed() {
	// TODO
}

void Star::onButtonPressed() {
	this->shutdownTrigger = true;
}

void Star::endGame(uint8_t end) {}

void Star::onClick() {}

void Star::onDoubleClick() {}

void Star::onLeftGesture(unsigned int power) {}

void Star::onRightGesture(unsigned int power) {}

void Star::onUpGesture(unsigned int power) {}

void Star::onDownGesture(unsigned int power) {}