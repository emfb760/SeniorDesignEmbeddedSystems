#ifndef SONAR_SENSOR_H_
#define SONAR_SENSOR_H_

class SonarSensor {
private:
	int trigger;					// Pin number for the trigger of the sonar sensor (output)
	int echo;						// Pin number for the echo of the sonar sensor (input)
	long duration;					// Holds the last duration value read by the sonar sensor
	long uSToInches() const;		// Private function to convert duration value to inches
	long uSToCentimeters() const;	// Private function to convert duration value to centimeters
public:
	SonarSensor(int, int);			// Constructor takes in the trigger and echo pin numbers
	void measureDuration();			// Main function of the sonar sensor; emits sonar frequency and measures how long until it comes back (if at all)
	void setTrigger(int);			// Sets trigger to a different pin
	void setEcho(int);				// Sets echo to a different pin
	int getTrigger() const;			// Accessor method to retrieve trigger pin
	int getEcho() const;			// Accessor method to retrieve echo pin
	long getInches() const;			// Returns the converted duration value in inches
	long getCentimeters() const;	// Returns the converted duration value in centimeters
	long getDuration() const;		// Returns the duration value
	void printMeasurements();		// Prints the duration value on the serial monitor in units of time, inches, and centimeters
};

#endif