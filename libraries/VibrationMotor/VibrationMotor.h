#ifndef VIBRATION_MOTOR_H_
#define VIBRATION_MOTOR_H_

#define DELTA 50			//Constant delta value used for delay between pulses

class VibrationMotor {
private:
	int pinOut;			// The pin that the motor is connected to on the Arduino board
	int maxGranularity;	// Controls the range in which the vibration motor will function
	int pinLED;			// The pin that the additional LED is connected to on the Arduino board
	int speed;			// Used to set the speed of the pulsing (the lower the value the faster the vibration: Operational Extremes - Max=0, Min=maxGranularity-1)
	int vibrationTime;	// Used to specify the length given to the vibration motor to pulse at the current speed

public:
	VibrationMotor(int,int,int,int);// Constructor takes in 4 parameters to set pinOut, maxGranularity, pinLED, and vibrationTime
	void setSpeed(int);				// Sets speed to the passed in 'int' value
	void setSpeed(long);			// Sets speed to the passed in 'long' value (value is cast to 'int')
	int getSpeed() const;			// Accessor method that returns the current speed
	void setPin(int);				// Sets the current Vibration Motor pin to another pin
	int getPin() const;				// Accessor method that returns the current pin number of the Vibration Motor
	void setLEDPin(int);			// Sets the current LED pin to another pin
	int getLEDPin() const;			// Accessor method that returns the current pin number of the LED
	void setMaxGranularity(int);	// Sets maxGranularity to a new value
	int getMaxGranularity() const;	// Accessor method that returns the current maxGranularity value
	void setVibrationTime(int);		// Sets vibrationTime to a new value
	int getVibrationTime() const;	// Accessor method that returns the current vibrationTime value
	void pulse();					// Function to pulse vibration motor for 'VIBRATION_TIME' ms
};

#endif