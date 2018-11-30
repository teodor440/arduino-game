Star::Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Game(matctrl, ledctrl, joystick, button) {

}

void Star::init() {}

void Star::onNewFrame() {}

uint8_t Star::run() {

	if (this->shutdownTrigger) return program_selector;
	return current_program;
}

void Star::onButtonPressed() {
	this->shutdownTrigger = true;
}

void Star::onClick() {}

void Star::onDoubleClick() {}

void Star::onLeftGesture(uint8_t power) {}

void Star::onRightGesture(uint8_t power) {}

void Star::onUpGesture(uint8_t power) {}

void Star::onDownGesture(uint8_t power) {}