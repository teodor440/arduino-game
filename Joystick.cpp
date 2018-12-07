#include "Joystick.h"

Joystick::Joystick(uint8_t Hpin, uint8_t Vpin, uint8_t Cpin) {
	this->Hpin = Hpin;
	this->Vpin = Vpin;
	this->Cpin = Cpin;

	pinMode(Hpin, INPUT);
	pinMode(Vpin, INPUT);
	pinMode(Cpin, INPUT_PULLUP);
}

int Joystick::getX() {
	return analogRead(this->Hpin);
}

int Joystick::getY() {
	return analogRead(this->Vpin);
}

void Joystick::setClickInterruptRoutine(void(*ptr)()) {
	this->detachClickInterrupt();
	attachInterrupt(digitalPinToInterrupt(this->Cpin), ptr, RISING);
}

void Joystick::detachClickInterrupt() {
	if(setInterrupt) detachInterrupt(digitalPinToInterrupt(this->Cpin));
	setInterrupt = false;
}

Joystick::~Joystick() {
	if (setInterrupt) detachInterrupt(digitalPinToInterrupt(this->Cpin));
}
