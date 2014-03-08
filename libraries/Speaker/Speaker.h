#ifndef _SPEAKER__H_
#define _SPEAKER__H_

// Notes that can be played by the speaker
//   Each note stores the period of the actual note to be played
enum NOTE { C3 = 3830, D3 = 3400, E3 = 3038, F3 = 2864, G3 = 2550, R = 0 };

// Durations to play the note
//   This system simulates different lengths of notes that can be played corresponding to the
//   tempo of the speaker object. Possible lengths range from a whole note to a sixteenth note.
enum DURATION { WHOLE = 16, HALF = 8, QUARTER = 4, EIGHTH = 2, SIXTEENTH = 1 };

class Speaker {
private:
	int pinOut;		// The pin that the speaker is connected to on the Arduino board
	long tempo;		// Manages the tempo of the notes to be played
	
public:
	Speaker (int,long);				// Constructor takes in 2 parameters to set pinOut and tempo
	void setPin(int);				// Sets pinOut to the parameter passed in
	int getPin() const;				// Accessor method that returns the current pinOut value
	void setTempo(long);			// Sets the tempo to the parameter passed in
	long getTempo() const;			// Accessor method that returns the current tempo value
	void playNote(NOTE, DURATION);	// Function to play the passed in note for the given duration
};

#endif