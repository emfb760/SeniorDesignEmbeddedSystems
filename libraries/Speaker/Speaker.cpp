#include "Arduino.h"
#include "Speaker.h"

Speaker::Speaker(int pOut, long tmpo)
	: pinOut(pOut), tempo(tmpo)
{
	pinMode(pinOut,OUTPUT);
}

void Speaker::setPin(int p) {
	pinOut = p;
	pinMode(pinOut,OUTPUT);
}

int Speaker::getPin() const {
	return pinOut;
}

void Speaker::setTempo(long tmpo) {
	tempo = tmpo;
}

long Speaker::getTempo() const {
	return tempo;
}

void Speaker::playNote(NOTE n, DURATION d) {
	long elapsed_time = 0;
	long beats = d * tempo;
	if (n > 0) {	// Make sure the note is not a rest note
		while (elapsed_time < beats) {	// play the note for the specified duration

			// Signal High
			digitalWrite(pinOut,HIGH);
			delayMicroseconds(n / 2);

			// Signal Low
			digitalWrite(pinOut, LOW);
			delayMicroseconds(n / 2);

			// Keep track of how long we pulsed
			elapsed_time += n;
		} 
	}
	else { // Rest beat
			delayMicroseconds(beats);                                 
	} 
}