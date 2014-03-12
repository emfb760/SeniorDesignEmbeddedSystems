#include "Arduino.h"
#include "VibrationMotor.h"

VibrationMotor::VibrationMotor(int pOut, int maxG, int pLED = -1, int vTime = 400)
	: pinOut(pOut), maxGranularity(maxG), pinLED(pLED), vibrationTime(vTime), speed(0)
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

void VibrationMotor::setVibrationTime(int vTime) {
	vibrationTime = vTime;
}

int VibrationMotor::getVibrationTime() const {
	return vibrationTime;
}

void VibrationMotor::pulse() {
	if( speed == 0 ) {					// If speed is zero, vibrate continuously
		digitalWrite(pinOut,HIGH);
		if( pinLED != -1 ) {
			digitalWrite(pinLED, HIGH);
		}
		delay(200);
	}
	else if( speed < maxGranularity ) {	// When the reading is within the granularity range and greater than zero
		int time = 0;
		while( time <= vibrationTime ) {	// This timing condition allows the user to simulate a delay between a change in speed
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
	else {								// Out of range
		digitalWrite(pinOut,LOW);
		if( pinLED != -1 ) {
			digitalWrite(pinLED,LOW);
		}
	}
}