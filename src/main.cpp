/*
 Name:		main.cpp
 Author:	Sciencelab Team
 Stage:		Alpha
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include <RobocupLib.h>

TMotor m1 (2, 3, 4);
TMotor m2 (6, 7, 5);
TMotor m3 (8, 9, 10);

IR_SENSOR ir[12] = {A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14};

int returnArray[2] = {0, 0};

void setup() {
	Serial.begin(9600);
}

void robotDirection(int dir, int speed){
	int sinm1, sinm2, sinm3;

	sinm1 = (speed) * sin((dir + 180) / RAD_TO_DEG);
	if (sinm1 < 1 && sinm1 > -1){
		sinm1 = 1;
	}
	sinm2 = (speed) * sin((dir + 60) / RAD_TO_DEG);
	if (sinm2 < 1 && sinm2 > -1){
		sinm2 = 1;
	}
	sinm3 = (speed) * sin((dir - 60) / RAD_TO_DEG);
	if (sinm3 < 1 && sinm3 > -1){
		sinm3 = 1;
	}

	Serial.print("Motor 1: ");
	Serial.println(sinm1);
	Serial.print("Motor 2: ");
	Serial.println(sinm2);
	Serial.print("Motor 3: ");
	Serial.println(sinm3);
	delay(300);
	
	
	m1.move(sinm1);
	m2.move(sinm2);
	m3.move(sinm3);

	
}

void calculateIrStrength(){
	
	int strongestValue = 0;
	int strongestInput = 0;
	for(int i = 0; i < 12; i++){
		if(ir[i].readSensor() > strongestValue){
			strongestValue = ir[i].readSensor();
			strongestInput = i;
		}
		if(strongestValue == 0){
			strongestInput = 69;
		}
	}
	returnArray[0] = strongestInput;
	returnArray[1] = strongestValue;

	Serial.print("Highest TSOP: ");
	Serial.println(returnArray[0]);	
	Serial.print("Highest Value: ");
	Serial.println(returnArray[1]);
	delay(300);
}

void loop() {
	calculateIrStrength();
	switch(returnArray[0]){
		case 0:
			robotDirection(0, 175);
			break;
		case 1:
			robotDirection(30, 175);
			break;
		case 2:
			robotDirection(60, 175);
			break;
		case 3:
			robotDirection(90, 175);
			break;
		case 4:
			robotDirection(120, 175);
			break;
		case 5:
			robotDirection(150, 175);
			break;
		case 6:
			robotDirection(180, 175);
			break;
		case 7:
			robotDirection(210, 175);
			break;
		case 8:
			robotDirection(240, 175);
			break;
		case 9:
			robotDirection(270, 175);
			break;
		case 10:
			robotDirection(300, 175);
			break;
		case 11:
			robotDirection(330, 175);
			break;																										
		case 69:
			robotDirection(0, 0);
			break;
	}
}