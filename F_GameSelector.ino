GameSelector::GameSelector(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Program(matctrl, ledctrl, joystick, button) {
	this->clearConsole();
	this->printMessage("Choose game");

	this->changeState(0);
}

void GameSelector::changeState(uint8_t state_index) {
	Serial.print("Changed game choice state to ");
	Serial.println(this->gameNames[state_index]);
	this->printMessage(this->gameNames[state_index], 1);
	this->currentSelectedIndex = state_index;
}

void GameSelector::advanceState() {
	if (this->nextDirection == DIRECTION_UP) {
		if (this->currentSelectedIndex == 0) changeState(game_count - 1);
		else changeState(this->currentSelectedIndex - 1);
	}
	else if(this->nextDirection == DIRECTION_DOWN) changeState((this->currentSelectedIndex + 1) % game_count);
}

uint8_t GameSelector::run() {
	int currentMillis = millis();
	if ((unsigned long)(currentMillis - this->lastMillis) > this->delayPeriod) {
		this->lastMillis = currentMillis;
		// Relevant periodical code
		this->advanceState();
	}

	this->processInput();
	if (shutdownTrigger) return this->gamesMapCodes[this->currentSelectedIndex];

	return current_program;
}

void GameSelector::onClick() {
	this->shutdownTrigger = true;
}

void GameSelector::onUpGesture(uint8_t power) {
	nextDirection = DIRECTION_UP;
}

void GameSelector::onDownGesture(uint8_t power) {
	nextDirection = DIRECTION_DOWN;
}

void GameSelector::onDoubleClick() {}

void GameSelector::onButtonPressed() {}

void GameSelector::onLeftGesture(uint8_t power) {}

void GameSelector::onRightGesture(uint8_t power) {}