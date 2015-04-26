/*
    ArMiJoy.ino - A MIDI input device build with the OpenJumper Joystick Shield

    Created by Holger Nauen, hn [at] holgernauen [dot] de
    Copyright 2015 - Under creative commons license 4.0:
        Attribution-ShareAlike CC BY-SA
        http://creativecommons.org/licenses/by-sa/4.0/

    This software is furnished "as is", without technical support, and with no
    warranty, express or implied, as to its usefulness for any purpose.
*/

#include <Joystick.h>
#include <MIDI.h>

// Uncomment next line to get readable serial output
// #define DEBUG

#ifndef DEBUG

    MIDI_CREATE_DEFAULT_INSTANCE();
    #define BEGIN()                     MIDI.begin(MIDI_CHANNEL_OMNI)
    #define SEND_ON(note)               MIDI.sendNoteOn(note,currentVelocity,channel)
    #define SEND_OFF(note)              MIDI.sendNoteOff(note,currentVelocity,channel)
    #define SEND_AFTER_TOUCH(pressure)  MIDI.sendAfterTouch(pressure,channel)
    #define SEND_PITCH_BEND(value)      MIDI.sendPitchBend(value,channel)

#else

    #define BEGIN() Serial.begin(9600)
    #define SEND_ON(note)               Serial.print("note on    ");   \
                                        Serial.print(note);            \
                                        Serial.print(", ");            \
                                        Serial.print(currentVelocity); \  
                                        Serial.println()

    #define SEND_OFF(note)              Serial.print("note off   ");   \
                                        Serial.print(note);            \
                                        Serial.print(", ");            \
                                        Serial.print(currentVelocity); \
                                        Serial.println()
 
    #define SEND_AFTER_TOUCH(pressure)  Serial.print("aftertouch ");   \
                                        Serial.print(pressure);        \
                                        Serial.println()

    #define SEND_PITCH_BEND(value)      Serial.print("pitchbend ");    \
                                        Serial.print(value);           \
                                        Serial.println()
                                        
#endif

// Four of the joystick buttons are used as piano keys.
enum Keys {
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR
};

// Adjust the channel to your MIDI equipment.
const byte channel = 1;


// Midi notes
enum Notes {
    NOTE_A = 45,
    NOTE_A_SHARP,
    NOTE_B,
    NOTE_C,
    NOTE_C_SHARP,
    NOTE_D,
    NOTE_D_SHARP,
    NOTE_E,
    NOTE_F,
    NOTE_F_SHARP,
    NOTE_G,
    NOTE_G_SHARP,
};

// Simple chords, e.g. for Bad Moon Rising by CCR
const byte harmonyCount = 3;
const byte harmony[] = {NOTE_D, NOTE_A, NOTE_G};

// The four keys are play a major chord.
const byte chordMajor[] = {0, 4, 7, 12};

byte currentVelocity = 0;
byte currentHarmony = 0;

Joystick joystick;

void playKey(byte key, bool pressed){
    byte note = harmony[currentHarmony]+chordMajor[key];
        
    if (pressed == true){
        SEND_ON(note); 
    } else {
        SEND_OFF(note); 
    }
}

void onAxisX(float position){
    currentVelocity = map(position,-100,100,0,127);
}

void onAxisY(float position){
	// used MIDI_PITCHBEND_MIN+1 to get rid of ugly -1 if postion is 0.0
    int value = map(position,-100,100,MIDI_PITCHBEND_MIN+1,MIDI_PITCHBEND_MAX);
    SEND_PITCH_BEND(value);

	// You could also try after touch.
    // byte pressure = map(abs(position),0,100,0,127);  
    // SEND_AFTER_TOUCH(pressure);
}

void onButtonLeft(bool pressed){
    playKey(KEY_ONE, pressed);  
}
void onButtonUp(bool pressed){
    playKey(KEY_TWO, pressed);  
}
void onButtonDown(bool pressed){
    playKey(KEY_THREE, pressed);  
}
void onButtonRight(bool pressed){
    playKey(KEY_FOUR, pressed);  
}

void onButtonSelect(bool pressed){
    if(pressed){
		// select next harmony
        currentHarmony = (currentHarmony+1) % harmonyCount;
    }
}

void setup() {
    BEGIN();

    joystick.onAxis(Joystick::X, &onAxisX);
    joystick.onAxis(Joystick::Y, &onAxisY);

    joystick.onButton(Joystick::Left,   &onButtonLeft);
    joystick.onButton(Joystick::Down,   &onButtonDown);
    joystick.onButton(Joystick::Up,     &onButtonUp);
    joystick.onButton(Joystick::Right,  &onButtonRight);
    joystick.onButton(Joystick::Select, &onButtonSelect);
}
 
void loop() {
    joystick.process();
}