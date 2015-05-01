/**
	JoystickButton.h - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#ifndef JoystickButton_h
#define JoystickButton_h

/**
	Calback for changes on button state.
	
	@param pressed true if the button is pressed.
*/
typedef void (*JoystickButtonCallbackFunction) (bool pressed);

class JoystickButton {
  
	public:
    	JoystickButton(int digitalPin, JoystickButtonCallbackFunction callback);
		~JoystickButton();
		void process();
  
	private:
		static const int debounceMillis = 50;
		
		int digitalPin;
		bool pressed;
		unsigned long lastChange;
		JoystickButtonCallbackFunction callback;
	};

#endif
