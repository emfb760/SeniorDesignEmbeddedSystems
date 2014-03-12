#include <SonarSensor.h>
#include <VibrationMotor.h>
#include <Speaker.h>

#define DEBUG 0  // Set to 1 to compile debug version of the code;
                 //   In Debug version, data information is printed to the serial monitor

#define triggerPIN 11  // Arduino Pin connected to the trigger pin of the sonar sensor
#define echoPIN 12     // Arduino Pin connected to the echo pin of the sonar sensor

#define vibPIN 10      // Arduino Pin connected to the vibration motor 
#define granularity 10 // Number of levels that can be represented by the vibration motor
#define LEDPIN 5       // Arduino Pin connected to an LED to visually display the feedback given by the vibration motor
                       //   This is an additional feature added to help demonstrate the system to onlookers
#define vibTime 0      // Length in which to pulse the current speed before re-checking the distance

#define speakerPIN 9   // Arduino Pin connected to the speaker 
#define tempo 10000    // Tempo to play notes on the speaker

#define modePin 6      // Arduino Pin connected to switch to allow user to toggle between object finding mode and way finding mode
#define modeLED 7      // Arduino Pin connected to LED to display the current mode

// Initialize objects used in the system (i.e. sonar sensor, vibration motor, and speaker)
SonarSensor s(triggerPIN,echoPIN);
VibrationMotor vm(vibPIN,granularity,LEDPIN,vibTime);
Speaker spkr(speakerPIN,tempo);

void setup() {

#if DEBUG == 1
  Serial.begin(9600);
  delay(5000);
#endif

  // Play a simple jingle to let the wearer know that the system is ready to work

  spkr.playNote(C3,WHOLE);

#if DEBUG == 1
  Serial.println("Played C3");
#endif

  delay(100);
  spkr.playNote(E3,WHOLE);
  
#if DEBUG == 1  
  Serial.println("Played E3");
#endif  
  
  delay(100);
  spkr.playNote(G3,WHOLE);
  
#if DEBUG == 1  
  Serial.println("Played G3");
#endif  
  
  pinMode(modePin,INPUT_PULLUP);  // Set mode pin to be an input pin
  pinMode(modeLED,OUTPUT);  // Set mode LED pin to be an output pin
  
  delay(100);
}

void loop()
{
  // Take measurement with sonar sensor
  s.measureDuration();
 
#if DEBUG == 1 
  s.printMeasurements();
#endif

  if( digitalRead(modePin) == LOW ) {  // Check if the switch is set to way finding mode
    // Set the speed of the vibration motor given the distance calculate converted to 6 inch increments
    vm.setSpeed(s.getInchIncrement(6));
    
    digitalWrite(modeLED,HIGH);
  }
  else {
    // Set the speed of the vibration motor given the distance calculated converted to inches
    vm.setSpeed(s.getInches());
    
    digitalWrite(modeLED,LOW);
  }
  
  // Pulse the vibration motor
  vm.pulse();
  
}
