#include "Interactionable.h"

uint8_t Interactionable::clickCount = 0;
uint8_t Interactionable::btn_pressed = 0;

Interactionable::Interactionable(Joystick* joystick, uint8_t quit_btn) {
	joystick->setClickInterruptRoutine(this->handleClickInterrupt);
	this->joystick = joystick;
	// static var
	Interactionable::clickCount = 0;
	Interactionable::btn_pressed = 0;

	this->quit_btn = quit_btn;
	pinMode(quit_btn, INPUT);
	btn_pressed = 0;
}

void Interactionable::handleClickInterrupt() {
	Interactionable::clickCount++;
}

void Interactionable::handleButtonInterrupt() {
	Interactionable::btn_pressed = 1;
}

void Interactionable::processInput() {
	if (this->btn_pressed) {
		Serial.println("Button pressed");

		onButtonPressed();
		btn_pressed = 0;
	}
	if (clickCount != 0) {
		Serial.print("Clicked - ");
		Serial.println(clickCount);

		if (clickCount == 1)
			onClick();
		else
			onDoubleClick();
		clickCount = 0;
	}

	int x = joystick->getX();
	int y = joystick->getY();
	Serial.print("x=");
	Serial.println(x);
	Serial.print("y=");
	Serial.println(y);

	if (x > (joystick->sensivity + 512)) {
		Serial.println("Right gesture");
		this->onRightGesture(x - 512);
	}
	else if (x < (512 - joystick->sensivity)) {
		Serial.println("Left gesture");
		this->onLeftGesture(512 - x);
	}

	if (y > (joystick->sensivity + 512)) {
		Serial.println("Up gesture");
		this->onUpGesture(y - 512);
	}
	else if (y < (512 - joystick->sensivity)) {
		Serial.println("Down gesture");
		this->onDownGesture(512 - y);
	}
}