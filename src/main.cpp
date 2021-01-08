#include <Arduino.h>
#include <Core.h>
#include <Motor.h>
#include <Encoder_ctm.h>

EncoderData datam2;
EncoderData datam3;
Motor m1 (2, 3, 4, 0, 0);
Motor m2 (6, 7, 5, 11, 12);
Motor m3 (8, 9, 10, 0, 0);

void encoder2change() {
  if (digitalRead(12)==LOW)
  {
    datam3.ticksmoved++;
  }
  else
  {
    datam3.ticksmoved--;
  }
  datam3.currentpulsetime=micros()-datam3.previoustime;
  datam3.previoustime=micros();
}

void encoder1change() {
  if (digitalRead(11)==LOW)
  {
    datam2.ticksmoved++;
  }
  else
  {
    datam2.ticksmoved--;
  }
  datam2.currentpulsetime=micros()-datam2.previoustime;
  datam2.previoustime=micros();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(20, INPUT);
  pinMode(11, INPUT);
  pinMode(21, INPUT);
  pinMode(12, INPUT);
  attachInterrupt(digitalPinToInterrupt(20), encoder1change, RISING);
  attachInterrupt(digitalPinToInterrupt(21), encoder2change, RISING);

  m2.setup();
  m3.setup();
}

int speed = 200;

void loop() {
//   Serial.print("Motor 2: ");
//   Serial.println(datam2.calcRPM());
//   Serial.print("Motor 3: ");
//   Serial.println(datam3.calcRPM());
  m2.move(100);
  Serial.println(millis());

  m1.move(100);
  Serial.println(millis());

  
  m3.move(100);
  Serial.println(millis());

  delay(1000);

  // for(int i = 0; i < speed; i+=10) {
  //   m2.move(i);
  //   m3.move(i*-1);
  //   delay(100);
  // }
  // delay(500);
  // m1.move(-200);
  // m2.move(100);
  // m3.move(100);
  // delay(500);

}