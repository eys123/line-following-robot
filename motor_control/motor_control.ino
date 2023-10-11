#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
// is wired in reverse; has to run BACKWARD to go forwards

const int leftSensorPin = A1;
const int rightSensorPin = A0;
const int midRightSensorPin = A2;
const int midLeftSensorPin = A3;
int leftSensorVal = 0;
int rightSensorVal = 0;
int midLeftSensorVal = 0;
int midRightSensorVal = 0;
int sensorThreshold = 650;
int turnSpeed = 20;
int forwardSpeed = 30;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  rightMotor->setSpeed(turnSpeed);
  leftMotor->setSpeed(turnSpeed);
  readSensorInfo();
  // check both; if both are aight then move forward
  if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && (midLeftSensorVal > sensorThreshold || midRightSensorVal > sensorThreshold)) {
    rightMotor->setSpeed(forwardSpeed);
    leftMotor->setSpeed(forwardSpeed);
    forward();
  }
  else if (leftSensorVal > sensorThreshold) {
    turnLeft();
  }
  else if (rightSensorVal > sensorThreshold) {
    turnRight();
  }
  else if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && midLeftSensorVal < sensorThreshold && midRightSensorVal < sensorThreshold) {
    leftMotor -> run(FORWARD);
    rightMotor -> run(BACKWARD);
  }
  else if (leftSensorVal > sensorThreshold && rightSensorVal > sensorThreshold) {
    rightMotor->setSpeed(30);
    leftMotor->setSpeed(30);
    turnRight();
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
  // print the results to the Serial Monitor:
  Serial.print("[");
  Serial.print(leftSensorVal);
  Serial.print(", ");
  Serial.print(midLeftSensorVal);
  Serial.print(", ");
  Serial.print(midRightSensorVal);
  Serial.print(", ");
  Serial.print(rightSensorVal);
  Serial.println("]");
}

void turnLeft() {
  leftMotor -> run(FORWARD);
  rightMotor -> run(FORWARD);
  Serial.println("TURN LEFT");
}

void turnRight() {
  leftMotor -> run(BACKWARD);
  rightMotor -> run(BACKWARD);
  Serial.println("TURN RIGHT");
}

void forward() {
  leftMotor -> run(BACKWARD);
  rightMotor -> run(FORWARD);
}