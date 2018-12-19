#include "Game.h"

Game::Game(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button, uint8_t buzzerPin) : Program(matctrl, ledctrl, joystick, button), joystickSensivity(joystick->sensivity) {
	matctrl->clearDisplay(0);
	ledctrl->clear();
	this->speakers = Audio(buzzerPin);

	// It would be likely a delay till the game begins so a click from joystick wouldnt affect
	// It could be done from the joystick class if I'd wish but not necessary
	delay(100);
	this->nextDirection = DIRECTION_NONE;
	this->clickCount = 0;
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

uint8_t Game::run() {
	// First we should check if we want to quit
	// First increment number of readings not to divide by 0 in case of a gesture
	this->processInput();
	if (this->shutdownTrigger) return PROGRAM_SELECTOR;
	if (this->gameStatus == RUNNING) {
		// Then continue the game
		int currentMillis = millis();
		if ((unsigned long)(currentMillis - this->lastMillis) > this->delayPeriod) {
			this->lastMillis = currentMillis;
			// Relevant periodical code
			this->onNewFrame();
		}
	}

	return CURRENT_PROGRAM;
}

void Game::onButtonPressed() {
	if (this->gameStatus == RUNNING) {
		this->gameStatus = PAUSED;

		this->clearConsole();
		this->printMessage("Paused");
	}
	else if (this->gameStatus == PAUSED || this->gameStatus == WAITING_RESTART) this->shutdownTrigger = true;
}