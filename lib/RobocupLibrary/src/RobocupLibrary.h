#ifndef ROBOCUPLIB_H_
#define ROBOCUPLIB_H_

#include <Arduino.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "wiring_private.h"
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>



class Motor
{
private:
	#define M1_IN1 2
	#define M1_IN2 3
	#define M1_EN 4
	#define M2_IN1 7
	#define M2_IN2 6
	#define M2_EN 5
	#define M3_IN1 9
	#define M3_IN2 8
	#define M3_EN 10
public:
	Motor();
	void init();
	void control(int SPEED_1, int SPEED_2, int SPEED_3);
	void direction(int dir, int speed);
};

class IR_SENSOR{
	private:
		#define IR_S0 22
		#define IR_S1 23
		#define IR_S2 24
		#define IR_S3 25	
		#define COMM_OUT A0
	public:
		IR_SENSOR();
		void init();
		
};

class Sonar
{
private:
	byte US_TRIG;
	byte US_ECHO;
public:
	Sonar();
	void attachTrig(int trigAttachPIN);
	void attachEcho(int echoAttachPIN);
	float getDistance();
	void debug(int debugTime);
};


#endif