#include "Arduino.h"
#include "VibrationMotor.h"

VibrationMotor::VibrationMotor(int pOut, int maxG, int pLED = -1)
	: pinOut(pOut), maxGranularity(maxG), pinLED(pLED), speed(0)
{
	pinMode(pinOut,OUTPUT);
	
	if( pinLED != -1 ) {
		pinMode(pinLED,OUTPUT);
	}
}

void VibrationMotor::setSpeed(int s) {
	speed = s;
}

void VibrationMotor::setSpeed(long s) {
	speed = (int)s;
}

int VibrationMotor::getSpeed() const {
	return speed;
}

void VibrationMotor::setPin(int pOut) {
	pinOut = pOut;
	pinMode(pinOut,OUTPUT);
}

int VibrationMotor::getPin() const {
	return pinOut;
}

void VibrationMotor::setLEDPin(int pLED) {
	pinLED = pLED;
	
	if( pinLED != -1 ) {
		pinMode(pinLED,OUTPUT);
	}
}

int VibrationMotor::getLEDPin() const {
	return pinLED;
}

void VibrationMotor::setMaxGranularity(int maxG) {
	maxGranularity = maxG;
}

int VibrationMotor::getMaxGranularity() const {
	return maxGranularity;
}

void VibrationMotor::pulse() {
	if( speed < maxGranularity ) {	// Only vibrate when the reading is within a certain range
		int time = 0;
		while( time < VIBRATION_TIME ) {	// This timing condition ensures that the motor pulses for the same amount of time regardless of 'speed'
			if( speed <= 0 ) {				// Continuously vibrate
				digitalWrite(pinOut,HIGH);
				if( pinLED != -1 ) {
					digitalWrite(pinLED,HIGH);
				}
				
				delay(VIBRATION_TIME);
				
				time = VIBRATION_TIME;
			}
			else {							// Vibrate at a pulse relative to the speed variable
				digitalWrite(pinOut,HIGH);
				if( pinLED != -1 ) {
					digitalWrite(pinLED,HIGH);
				}
				
				delay(DELTA*speed);
				
				digitalWrite(pinOut,LOW);
				if( pinLED != -1 ) {
					digitalWrite(pinLED,LOW);
				}
				
				delay(DELTA*speed);
				
				time += 2*DELTA*speed;
			}
		}
	}
	else {
		digitalWrite(pinOut,LOW);
		if( pinLED != -1 ) {
			digitalWrite(pinLED,LOW);
		}
	}
}