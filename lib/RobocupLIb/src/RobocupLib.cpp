#include <Arduino.h>
#include <RobocupLib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

TMotor::TMotor(int pin1, int pin2, int pin3) {
    in1 = pin1;
    in2 = pin2;
    pwm = pin3; 

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(pwm, OUTPUT);
}

void TMotor::move(int setPWM){
    if(setPWM >= -255 && setPWM <= -1) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, abs(setPWM));
    }
    if(setPWM <= 255 && setPWM >= 1) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwm, abs(setPWM));
    }
    
}

IR_SENSOR::IR_SENSOR(int pin){
    ir_pin = pin;
    
    pinMode(ir_pin, INPUT);
}

int IR_SENSOR::readSensor(){
    int value = analogRead(ir_pin);
	// Serial.println(value);
	
    return value;
}


Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

void gyroInit(){
    startMillis = millis();

	Serial.begin(115200);
	while (!Serial) {
		delay(10); // will pause Zero, Leonardo, etc until serial console opens
	}

	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
		delay(10);
		}
	}

	mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
	mpu.setGyroRange(MPU6050_RANGE_250_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
	Serial.println("");
	delay(100);
}

float calculateElapsedTime(float delayTime){
	float rawDuration = (float)millis() - startMillis;
	startMillis = (float)millis();

	float duration_diff = rawDuration - delayTime;
	float duration = rawDuration - duration_diff;

	return duration;
}

float returnGyro(){
	mpu.getEvent(&a, &g, &temp);

	float axis = (float)g.gyro.z;
	return axis;
}

float calculateError(int calTime){
	static float totalValue;
	for(static int i = 0; i < calTime;){
		mpu.getEvent(&a, &g, &temp);
		float value = (float)g.gyro.z;
		totalValue = totalValue + value;
		Serial.print("Cycle: ");
		Serial.println(i);
		Serial.print("Total Value: ");
		Serial.println(value, 6);
		delay(100);
		i++;
	}
	float errorMargin = totalValue / (float)calTime;
	Serial.print("Error margin: ");
	Serial.println(errorMargin, 6);
	return errorMargin;
}


float calculateDegree(float errorMargin, float delayTime){
	static float totalRadian = 0;
	mpu.getEvent(&a, &g, &temp);
	

	int duration = calculateElapsedTime(delayTime);
	delay(delayTime);
	float axis = (float)g.gyro.z - errorMargin;

	totalRadian = totalRadian + axis * (duration / 1000.0);
	//Serial.println(axis, 6);
	//Serial.print("Duration: ");
	//Serial.println(duration, 6);
	//Serial.print("Radian: ");
	//Serial.println(totalRadian, 6);
	float totalDegree = totalRadian * (180/PI);
	if (totalDegree > 180) {
		totalDegree = 0;
	} else if (totalDegree < -180){
		totalDegree = 0;
	} else {
		totalDegree = totalDegree;
	}
	
	// Serial.print("Degree: ");
	// Serial.println(totalDegree, 6);

	return totalDegree;
}
