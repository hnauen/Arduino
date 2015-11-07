/**
	Joystick.cpp - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#include "Arduino.h"
#include "Joystick.h"

const int Joystick::defaultAnalogPin[Joystick::axisCount] = {
		0,  // X 
		1   // Y
	};
JoystickAxis Joystick::*pJoystickAxis[Joystick::axisCount];

const int Joystick::defaultDigitalPin[Joystick::buttonCount] = {
		3, // Left
		4, // Down
		5, // Up
		6, // Right
		7  // Select
	};
JoystickButton Joystick::*pJoystickButton[Joystick::buttonCount];

Joystick::Joystick(){
	for (int i=0; i<Joystick::axisCount; i++){
		pJoystickAxis[i] = NULL;
	}
	for (int i=0; i<Joystick::buttonCount; i++){
		pJoystickButton[i] = NULL;
	}
}

Joystick::~Joystick(){
	for (int i=0; i<Joystick::axisCount; i++){
		if (pJoystickAxis[i] != NULL){
			delete pJoystickAxis[i];
			pJoystickAxis[i] = NULL;
		}
	}
	for (int i=0; i<Joystick::buttonCount; i++){
		if (pJoystickButton[i] != NULL){
			delete pJoystickButton[i];
			pJoystickButton[i] = NULL;
		}
	}
}

void Joystick::onAxis(Axis axis, JoystickAxisCallbackFunction cbFunction){
	onAxis(axis, defaultAnalogPin[axis], cbFunction);
}

void Joystick::onAxis(Axis axis, int analogPin, JoystickAxisCallbackFunction cbFunction){
	if (pJoystickAxis[axis] != NULL){
		delete pJoystickAxis[axis];
	}
	pJoystickAxis[axis] = new JoystickAxis(analogPin, cbFunction);
}

void Joystick::onButton(Button button, JoystickButtonCallbackFunction cbFunction){
	onButton(button, defaultDigitalPin[button], cbFunction);
}

void Joystick::onButton(Button button, int digitalPin, JoystickButtonCallbackFunction cbFunction){
	if (pJoystickButton[button] != NULL){
		delete pJoystickButton[button];
	}
	pJoystickButton[button] = new JoystickButton(digitalPin, cbFunction);
}

void Joystick::process(){
	for (int i=0; i<Joystick::axisCount; i++){
		if (pJoystickAxis[i] != NULL){
			pJoystickAxis[i]->process();
		}
	}
	for (int i=0; i<Joystick::buttonCount; i++){
		if (pJoystickButton[i] != NULL){
			pJoystickButton[i]->process();
		}
	}
}