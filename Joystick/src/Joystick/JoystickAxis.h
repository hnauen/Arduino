/**
	JoystickAxis.h - Library for the OpenJumper Joystick Shield

	Created by Holger Nauen, hn [at] holgernauen [dot] de
	Copyright 2015 - Under creative commons license 4.0:
		Attribution-ShareAlike CC BY-SA
		http://creativecommons.org/licenses/by-sa/4.0/

	This software is furnished "as is", without technical support, and with no
	warranty, express or implied, as to its usefulness for any purpose.
*/

#ifndef JoystickAxis_h
#define JoystickAxis_h

/**
	Callback for changes on an analog axis.
	
	@param position The position of the Axis in percent: -100.0 to 100.0.
*/
typedef void (*JoystickAxisCallbackFunction) (float position);

class JoystickAxis {
  
	public:
    	JoystickAxis(int analogPin, JoystickAxisCallbackFunction callback);
		~JoystickAxis();
		void process();
  
	private:
		static const int flickerMillis = 50;
		
		int analogPin;
		int currentValue;
		int zeroValue;
		unsigned long lastChange;
		JoystickAxisCallbackFunction callback;
		
		float getPosition();
		
	};

#endif
