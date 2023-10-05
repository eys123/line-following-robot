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
int sensorThreshold = 820;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  rightMotor->setSpeed(50);
  leftMotor->setSpeed(50);
}

void loop() {
  readSensorInfo();
  // check both; if both are aight then move forward
  if (leftSensorVal > sensorThreshold && rightSensorVal > sensorThreshold) {
    leftMotor -> run(FORWARD);
    leftMotor -> run(BACKWARD);
  }
  else if (leftSensorVal > sensorThreshold) {
    leftMotor -> run(RELEASE);
    rightMotor -> run(BACKWARD);
  }
  else if (rightSensorVal > sensorThreshold) {
    leftMotor -> run(FORWARD);
    rightMotor -> run(RELEASE);
  }
  else {
    leftMotor -> run(FORWARD);
    rightMotor -> run(FORWARD);
  }
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