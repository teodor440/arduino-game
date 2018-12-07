#include "GameSelector.h"

GameSelector::GameSelector(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Program(matctrl, ledctrl, joystick, button) {
	this->clearConsole();
	this->printMessage("Choose game");

	this->changeState(0);
	this->delayPeriod = 500;

	this->lastBlink = millis();
}

void GameSelector::changeState(uint8_t state_index) {
#ifdef DEBUGGING_MENU
	Serial.print("Changed game choice state to ");
	Serial.println(this->gameNames[state_index]);
#endif
	this->printMessage(this->gameNames[state_index], 1);
	this->currentSelectedIndex = state_index;
	// Draw some awesome shit to display on the matrix for the game
	this->matrixcontroller->clearDisplay(0);
	for (int i = 0; i < COORDINATES_LENGTH - 1; i += 2) {
		this->matrixcontroller->setLed(0, this->images[state_index][i], this->images[state_index][i + 1], true);
	}
	delay(1000);
}

void GameSelector::advanceState() {
	if (this->nextDirection == DIRECTION_UP) {
		if (this->currentSelectedIndex == 0) changeState(GAME_COUNT - 1);
		else changeState(this->currentSelectedIndex - 1);
	}
	else if (this->nextDirection == DIRECTION_DOWN) changeState((this->currentSelectedIndex + 1) % GAME_COUNT);
	this->nextDirection = DIRECTION_NONE;
}

uint8_t GameSelector::run() {
	// First we should check if we selected a program
	this->processInput();
	if (shutdownTrigger) {
		this->matrixcontroller->shutdown(0, false);
		return this->gamesMapCodes[this->currentSelectedIndex];
	}
	// Then process the other efects of user input5555555555555555555555
	int currentMillis = millis();
	if ((unsigned long)(currentMillis - this->lastMillis) > this->delayPeriod) {
		this->lastMillis = currentMillis;
		// Relevant periodical code
		this->advanceState();
	}

	if ((unsigned long)(currentMillis - this->lastBlink) > this->blinkingInterval) {
		this->lastBlink = millis();

		this->matrixcontroller->shutdown(0, blinkingState);
		blinkingState = !blinkingState;
	}

	return CURRENT_PROGRAM;
}

void GameSelector::onClick() {
	this->shutdownTrigger = true;
}

void GameSelector::onUpGesture(unsigned int power) {
	nextDirection = DIRECTION_UP;
}

void GameSelector::onDownGesture(unsigned int power) {
	nextDirection = DIRECTION_DOWN;
}

void GameSelector::onDoubleClick() {}

void GameSelector::onButtonPressed() {}

void GameSelector::onLeftGesture(unsigned int power) {}

void GameSelector::onRightGesture(unsigned int power) {}