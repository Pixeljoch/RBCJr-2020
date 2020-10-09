#include <RobocupLibrary.h>
#include <math.h>

// MOTOR FUNCTIONS	

Motor::Motor()
= default;

void Motor::init() 
{
	pinMode(M1_IN1, OUTPUT);
	pinMode(M1_IN2, OUTPUT);
	pinMode(M1_EN, OUTPUT);
	pinMode(M2_IN1, OUTPUT);
	pinMode(M2_IN2, OUTPUT);
	pinMode(M2_EN, OUTPUT);
	pinMode(M3_IN1, OUTPUT);
	pinMode(M3_IN2, OUTPUT);
	pinMode(M3_EN, OUTPUT);
}

void Motor::control(int SPEED_1, int SPEED_2, int SPEED_3) {
	switch (SPEED_1){
		case -255 ... -1:
			digitalWrite(M1_IN1, HIGH);
			digitalWrite(M1_IN2, LOW);
			analogWrite(M1_EN, SPEED_1 * -1);
		case 1 ... 255:
			digitalWrite(M1_IN1, LOW);
			digitalWrite(M1_IN2, HIGH);
			analogWrite(M1_EN, SPEED_1);
		case 0:
			digitalWrite(M1_IN1, LOW);
			digitalWrite(M1_IN2, HIGH);
			analogWrite(M1_EN, 1);
	};

	switch (SPEED_2){
		case -255 ... -1:
			digitalWrite(M2_IN1, LOW);
			digitalWrite(M2_IN2, HIGH);
			analogWrite(M2_EN, SPEED_2 * -1);
		case 1 ... 255:
			digitalWrite(M2_IN1, HIGH);
			digitalWrite(M2_IN2, LOW);
			analogWrite(M2_EN, SPEED_2);
		case 0:
			digitalWrite(M2_IN1, HIGH);
			digitalWrite(M2_IN2, LOW);
			analogWrite(M2_EN, 1);
	}

	switch (SPEED_3){
		case -255 ... -1:
			digitalWrite(M3_IN1, LOW);
			digitalWrite(M3_IN2, HIGH);
			analogWrite(M3_EN, SPEED_3 * -1);
		case 1 ... 255:
			digitalWrite(M3_IN1, HIGH);
			digitalWrite(M3_IN2, LOW);
			analogWrite(M3_EN, SPEED_3);
		case 0:
			digitalWrite(M3_IN1, HIGH);
			digitalWrite(M3_IN2, LOW);
			analogWrite(M3_EN, 1);
	}


	// if(SPEED_1 < 0 && SPEED_1 >= -255)
	// {
	// 	digitalWrite(M1_IN1, HIGH);
	// 	digitalWrite(M1_IN2, LOW);
	// 	analogWrite(M1_EN, SPEED_1 * -1);
	// }
	// if(SPEED_1 > 0 && SPEED_1 <= 255)
	// {
	// 	digitalWrite(M1_IN1, LOW);
	// 	digitalWrite(M1_IN2, HIGH);
	// 	analogWrite(M1_EN, SPEED_1);
	// }
	
	// if (SPEED_2 < 0 && SPEED_2 >= -255)
	// {
	// 	digitalWrite(M2_IN1, LOW);
	// 	digitalWrite(M2_IN2, HIGH);
	// 	analogWrite(M2_EN, SPEED_2 * -1);
	// }
	// if (SPEED_2 > 0 && SPEED_2 <= 255)
	// {
	// 	digitalWrite(M2_IN1, HIGH);
	// 	digitalWrite(M2_IN2, LOW);
	// 	analogWrite(M2_EN, SPEED_2);
	// }

	// if(SPEED_3 < 0 && SPEED_3 >= -255)
	// {
	// 	digitalWrite(M3_IN1, LOW);
	// 	digitalWrite(M3_IN2, HIGH);
	// 	analogWrite(M3_EN, SPEED_3 * -1);
	// }

	// if(SPEED_3 > 0 && SPEED_3 <= 255)
	// {
	// 	digitalWrite(M3_IN1, HIGH);
	// 	digitalWrite(M3_IN2, LOW);
	// 	analogWrite(M3_EN, SPEED_3);
	// }

	
}

void Motor::direction(int dir, int speed)
{
	double pi = 57.29577951;
	double m1, m2, m3 = 0;

	m1 = -(speed)*sin((dir + 180) / pi);
	if (m1 < 1 && m1 > -1) {
		m1 = 1;
	}
	m2 = -(speed - 30) * sin((dir + 60) / pi);
	if (m2 < 1 && m2 > -1) {
		m2 = 1;
	}
	m3 = -(speed)*sin((dir - 60) / pi);
	if (m3 < 1 && m3 > -1) {
		m3 = 1;
	}
	Serial.println(m1);

	control(m1, m2, m3);
}

// IR FUNCTIONS

IR_SENSOR::IR_SENSOR()
= default;

// MODE: 0 = Standalone; 1 = Multiplexer

void IR_SENSOR::init(int mode){
	switch (mode){
		case 0:
			for (int i = 3; i < 15; i++){
				pinMode(IR_SENS[i], INPUT);
			}	
		case 1:
			pinMode(IR_S0, INPUT);
			pinMode(IR_S1, INPUT);
			pinMode(IR_S2, INPUT);
			pinMode(IR_S3, INPUT);
			pinMode(COMM_OUT, OUTPUT);
	}
}

void IR_SENSOR::selectSens(){
	int input[] = {
         analogRead(IR_SENS[0]),
		 analogRead(IR_SENS[1]),
		 analogRead(IR_SENS[2]),
		 analogRead(IR_SENS[3]),
		 analogRead(IR_SENS[4]),
		 analogRead(IR_SENS[5]),
		 analogRead(IR_SENS[6]),
		 analogRead(IR_SENS[7]),
		 analogRead(IR_SENS[8]),
		 analogRead(IR_SENS[9]),
		 analogRead(IR_SENS[10]),
		 analogRead(IR_SENS[11])
     };


    int strongestValue = 0;
    int strongestInput = 0;
    for (int i = 0; i < 12; i++) {
        if (input[i] > strongestValue) {
            strongestValue = input[i];
            strongestInput = i;
        }
    }
    returnArray[0] = strongestInput;
    returnArray[1] = calculateStrength(strongestValue);
	

}

int IR_SENSOR::calculateStrength(int strength) {
    if (strength >= 300) {
        return 1;
    }
    else if (strength >= 200) {
        return 2;
    }
    else if (strength >= 100) {
        return 3;
    }
    else if (strength >= 50) {
        return 4;
    }
}

// SONAR FUNCTIONS

Sonar::Sonar()
= default;

void Sonar::attachTrig(int trigAttachPIN)
{
	US_TRIG = trigAttachPIN;
}

void Sonar::attachEcho(int echoAttachPIN)
{
	US_ECHO = echoAttachPIN;
}

float Sonar::getDistance()
{
	float duration, distance;
	int tries = 0;

	pinMode(US_TRIG, OUTPUT);
	digitalWrite(US_TRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(US_TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(US_TRIG, LOW);
	do {
		duration = pulseIn(US_ECHO, HIGH, 30000);
		distance = 0.034 * duration / 2;
		if (duration == 0) {
			delay(100);
			pinMode(US_ECHO, OUTPUT);
			digitalWrite(US_ECHO, LOW);
			delay(100);
			pinMode(US_ECHO, INPUT);  //echo pin reset
		}
	} while (duration == 0 && ++tries < 3);
	return distance;
}

void Sonar::debug(int debugTime) {
	Serial.println(getDistance());
	delay(debugTime);
}

