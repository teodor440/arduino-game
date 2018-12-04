#include "Game.h"

Game::Game(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Program(matctrl, ledctrl, joystick, button), joystickSensivity(joystick->sensivity) {
	matctrl->clearDisplay(0);
	ledctrl->clear();
}

// Some values that work pretty well used here
void Game::influenceSpeed(unsigned int value) {
	// Sa fie 0.7 ca la colt de strada meeen
	// Shy un 0.9 ca la bastani
	long mapping = map(value, 0, 512 - .7*this->joystickSensivity, 0, .9*this->basisGameDelay);
	this->speedAdjuster = max(this->speedAdjuster, mapping);
	this->delayPeriod = this->basisGameDelay - this->speedAdjuster;
}

void Game::resetSpeed() {
	this->speedAdjuster = 0;
	this->delayPeriod = this->basisGameDelay;
}

void Game::changeBasisPace(float percentage) {
	this->basisGameDelay *= percentage;
}