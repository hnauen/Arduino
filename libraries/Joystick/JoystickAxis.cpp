/**
	JoystickAxis.cpp - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#include "Arduino.h"
#include "JoystickAxis.h"

JoystickAxis::JoystickAxis(int analogPin, JoystickAxisCallbackFunction callback){
	this->analogPin = analogPin;
	this->callback = callback;
	this->lastChange = millis();
	
	pinMode(this->analogPin, INPUT);
	this->currentValue = analogRead(this->analogPin);
	this->zeroValue = this->currentValue;
	this->callback(this->getPosition());
}

JoystickAxis::~JoystickAxis(){
}

void JoystickAxis::process(){
	int currentValue = analogRead(this->analogPin);
		
	// Detect change
	if (abs(this->currentValue - currentValue)>1){
		unsigned long now = millis();

		// Overflow?
		if (now < this->lastChange){
			this->lastChange = now;
		}
		
		// Flicker?
		if ((now - this->lastChange)>JoystickAxis::flickerMillis){
			this->lastChange = now; 
			this->currentValue = currentValue;
			this->callback(this->getPosition());
		}		
	}
}

float JoystickAxis::getPosition(){
	if (this->currentValue < this->zeroValue){
		return this->currentValue * 100.0 / this->zeroValue - 100.0;
	} else if (this->currentValue > this->zeroValue){
		return (this->currentValue - this->zeroValue) * 100.0 / (1023 - this->zeroValue);
	} 
	return 0.0;
}