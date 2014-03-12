#include "Arduino.h"
#include "SonarSensor.h"

SonarSensor::SonarSensor(int t, int e)
	:trigger(t), echo(e), duration(0)
{
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
}

void SonarSensor::measureDuration() {
	// The HC-SR04 requires the trigger to supply a 10uS pulse
  // to do this we first set the trigger to LOW to make sure we get a clean pulse,
  // then we assert the pin connected to the trigger, wait 10uS, and then set it back to LOW
  // An 8-cycle burst of ultrasound at 40kHz is emitted after the falling edge of this pulse
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Now we need to measure the time until the echo pin reads the returned ultrasound. The 
  // function pulseIn() does this for us. It returns the duration in microseconds between the
  // time the function was called and a 'HIGH' value is read in on the 'echo' pin.
  duration = pulseIn(echo, HIGH);
}

long SonarSensor::uSToInches() const {
	
  // According to ElecFreak's datasheet for the HC-SR04, the formula for
  // calculating the distance in inches is uS/148
  return duration / 148;
}

long SonarSensor::uSToCentimeters() const {
  // According to ElecFreak's datasheet for the HC-SR04, the formula for
  // calculating the distance in centimeters is uS/58
  return duration / 58;
}

void SonarSensor::setTrigger(int t) {
	trigger = t;
	pinMode(trigger,OUTPUT);
}

void SonarSensor::setEcho(int e) {
	echo = e;
	pinMode(echo,INPUT);
}

int SonarSensor::getTrigger() const {
	return trigger;
}

int SonarSensor::getEcho() const {
	return echo;
}

long SonarSensor::getInches() const {
	return uSToInches();
}

long SonarSensor::getInchIncrement(int increment) const {
	return (long)(uSToInches()/increment);
}

long SonarSensor::getCentimeters() const {
	return uSToCentimeters();
}

void SonarSensor::printMeasurements() {
	
  // convert the time into distance (inch and cm)
  long inches = uSToInches();
  long cm = uSToCentimeters();
  
  Serial.print("duration: ");
  Serial.print(duration);
  Serial.print(", ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}