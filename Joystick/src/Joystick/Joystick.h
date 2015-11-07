/**
	Joystick.h - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#ifndef Joystick_h
#define Joystick_h
#include "JoystickButton.h"
#include "JoystickAxis.h"

class Joystick {
  
	public:
		Joystick();
		~Joystick();

		static const int axisCount = 2;
		enum Axis {X, Y};

		/**
    		Registers a callback function for changes on the given axis. 
			The default analog pin will be used.

 			@param axis The axis.
			@param cbFunction The callback function. Use NULL to unregister.
		*/
		void onAxis(Axis axis, JoystickAxisCallbackFunction cbFunction);

		/**
    		Registers a callback function for changes on the given axis and analog pin.

 			@param axis The axis.
 			@param analogPin The appropriate analog pin.
			@param cbFunction The callback function. Use NULL to unregister.
		*/
		void onAxis(Axis axis, int analogPin, JoystickAxisCallbackFunction cbFunction);

		static const int buttonCount = 5;
		enum Button {Left, Down, Up, Right, Select};

		/**
    		Registers a callback function for changes on the given button. 
			The default digital pin will be used.

 			@param axis The axis.
			@param cbFunction The callback function. Use NULL to unregister.
		*/
		void onButton(Button button, JoystickButtonCallbackFunction cbFunction);

		/**
    		Registers a callback function for changes on the given button and digital pin. 

 			@param axis The axis.
 			@param digitalPin The appropriate digital pin.
			@param cbFunction The callback function. Use NULL to unregister.
		*/
		void onButton(Button button, int digitalPin, JoystickButtonCallbackFunction cbFunction);
	
		/**
    		Check changes. To be called from loop().
		*/
		void process();

	private:
		static const int defaultAnalogPin[Joystick::axisCount];
		JoystickAxis *pJoystickAxis[Joystick::axisCount];

		static const int defaultDigitalPin[Joystick::buttonCount];
		JoystickButton *pJoystickButton[Joystick::buttonCount];

};

#endif
