/*
    JoystickDemo.ino - Library for the OpenJumper Joystick Shield

    Created by Holger Nauen, hn [at] holgernauen [dot] de
    Copyright 2015 - Under creative commons license 4.0:
        Attribution-ShareAlike CC BY-SA
        http://creativecommons.org/licenses/by-sa/4.0/

    This software is furnished "as is", without technical support, and with no
    warranty, express or implied, as to its usefulness for any purpose.
*/

#include <Joystick.h>

void onAxisX(float position){
    Serial.print("Axis-X ");
    Serial.println(position);  
}
void onAxisY(float position){
    Serial.print("Axis-Y ");
    Serial.println(position);
}

void onButtonLeft(bool pressed){
    Serial.print("Button-Left ");
    Serial.println(pressed?"down":"up");  
}
void onButtonRight(bool pressed){
    Serial.print("Button-Right ");
    Serial.println(pressed?"down":"up");  
}
void onButtonUp(bool pressed){
    Serial.print("Button-Up ");
    Serial.println(pressed?"down":"up");  
}
void onButtonDown(bool pressed){
    Serial.print("Button-Down ");
    Serial.println(pressed?"down":"up");  
}
void onButtonSelect(bool pressed){
    Serial.print("Button-Select ");
    Serial.println(pressed?"down":"up");  
}

Joystick joystick;

void setup() {
    Serial.begin(9600);

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