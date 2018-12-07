// Audio.h

#ifndef _AUDIO_h
#define _AUDIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Audio {
private:
	uint8_t buzzerPin;
public:
	static const uint8_t beep = 1;

	Audio(uint8_t buzzerPin);
	// Should never use an audio made this way
	Audio();
	// Thread blocking function
	void play(uint8_t song);
};

#endif

