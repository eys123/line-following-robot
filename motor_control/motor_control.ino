#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// is wired backwards; must run BACKWARDS to go forwards and vice versa
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

const int leftSensorPin = A1;
const int rightSensorPin = A0;
const int midRightSensorPin = A2;
const int midLeftSensorPin = A3;
int leftSensorVal = 0;
int rightSensorVal = 0;
int midLeftSensorVal = 0;
int midRightSensorVal = 0;
int sensorThreshold = 650;
int turnSpeed = 25;
int forwardSpeed = 30;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  // if (Serial.available() != 0) {
  //   forwardSpeed = Serial.parseInt();
  // }
  rightMotor->setSpeed(turnSpeed);
  leftMotor->setSpeed(turnSpeed);
  readSensorInfo();
  // check both; if both are aight then move forward
  if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && (midLeftSensorVal > sensorThreshold || midRightSensorVal > sensorThreshold)) {
    rightMotor->setSpeed(forwardSpeed);
    leftMotor->setSpeed(forwardSpeed);
    forward();
  } else if (leftSensorVal > sensorThreshold) {
    turnLeft();
  } else if (rightSensorVal > sensorThreshold) {
    turnRight();
  } else if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && midLeftSensorVal < sensorThreshold && midRightSensorVal < sensorThreshold) {
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    Serial.print(", ");
    Serial.print(forwardSpeed * -1);
    Serial.print(", ");
    Serial.print(forwardSpeed * -1);
    Serial.println("]");
  }
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(250);
}

void readSensorInfo() {
  // read the analog in value:
  leftSensorVal = analogRead(leftSensorPin);
  rightSensorVal = analogRead(rightSensorPin);
  midLeftSensorVal = analogRead(midLeftSensorPin);
  midRightSensorVal = analogRead(midRightSensorPin);
  // // print the results to the Serial Monitor:
  Serial.print("[");
  Serial.print(leftSensorVal);
  Serial.print(", ");
  Serial.print(midLeftSensorVal);
  Serial.print(", ");
  Serial.print(midRightSensorVal);
  Serial.print(", ");
  Serial.print(rightSensorVal);
}

void turnLeft() {
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  Serial.print(", ");
  Serial.print(turnSpeed * -1);
  Serial.print(", ");
  Serial.print(turnSpeed);
  Serial.println("]");
}

void turnRight() {
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  Serial.print(", ");
  Serial.print(turnSpeed);
  Serial.print(", ");
  Serial.print(turnSpeed * -1);
  Serial.println("]");
}

void forward() {
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);
  Serial.print(", ");
  Serial.print(forwardSpeed);
  Serial.print(", ");
  Serial.print(forwardSpeed);
  Serial.println("]");
}