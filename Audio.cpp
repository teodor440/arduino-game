#include "Audio.h"

Audio::Audio(uint8_t buzzerPin) {
	this->buzzerPin = buzzerPin;
	pinMode(buzzerPin, OUTPUT);
	analogWrite(buzzerPin, 0);
}

Audio::Audio() {
	this->buzzerPin = A0;
}

void Audio::play(uint8_t song) {
	if (song == this->beep) {
		analogWrite(this->buzzerPin, 188);
		delay(10);
		analogWrite(this->buzzerPin, 0);
	}
	else if (song == this->gameOver) {
		analogWrite(this->buzzerPin, 188);
		delay(100);
		analogWrite(this->buzzerPin, 0);
	}
	else if (song == this->gameStart) {
		analogWrite(this->buzzerPin, 188);
		delay(5);
		analogWrite(this->buzzerPin, 0);
	}
}
