/**
	JoystickButton.cpp - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#include "Arduino.h"
#include "JoystickButton.h"

JoystickButton::JoystickButton(int digitalPin, JoystickButtonCallbackFunction callback){
	this->digitalPin = digitalPin;
	this->callback = callback;
	this->lastChange = millis();
	
	pinMode(this->digitalPin, INPUT_PULLUP);
	this->pressed = (digitalRead(this->digitalPin)==LOW);
	this->callback(this->pressed);
}

JoystickButton::~JoystickButton(){
}

void JoystickButton::process(){
	bool pressed = (digitalRead(this->digitalPin)==LOW);
		
	// Detect change
	if (this->pressed != pressed){
		unsigned long now = millis();
		
		// Overflow?
		if (now < this->lastChange){
			this->lastChange = now;
		}
		
		// Debounce!
		if ((now - this->lastChange) > JoystickButton::debounceMillis){
			this->lastChange = now; 
			this->pressed = pressed;
			this->callback(this->pressed);
		}
	}
}