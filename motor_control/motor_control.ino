#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
// is wired in reverse; has to run BACKWARD to go forwards

const int leftSensorPin = A0;
const int rightSensorPin = A1;
int leftSensorVal = 0;
int rightSensorVal = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  rightMotor->setSpeed(150);
}

void loop() {
  readSensorInfo();
  rightMotor->run(BACKWARD);
  
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(250);
}

void readSensorInfo() {
  // read the analog in value:
  leftSensorVal = analogRead(leftSensorPin);
  rightSensorVal = analogRead(rightSensorPin);
  // print the results to the Serial Monitor:
  Serial.print("[");
  Serial.print(leftSensorVal);
  Serial.print(", ");
  Serial.print(rightSensorVal);
  Serial.println("]");
}