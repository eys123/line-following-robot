/*
A file for running running a line following robot.
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// is wired backwards; must run BACKWARDS to go forwards and vice versa
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// init variables for sensors
const int leftSensorPin = A1;
const int rightSensorPin = A0;
const int midRightSensorPin = A2;
const int midLeftSensorPin = A3;
int leftSensorVal = 0;
int rightSensorVal = 0;
int midLeftSensorVal = 0;
int midRightSensorVal = 0;
int sensorThreshold = 650;

// init speed variables
int adjustSpeed = 25;
int forwardSpeed = 30;
int speedMultiplier = 1;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  // check for serial input to adjust speed
  if (Serial.available() > 0) {
    speedMultiplier = Serial.parseInt();
  }
  forwardSpeed = speedMultiplier * forwardSpeed;
  adjustSpeed = speedMultiplier * adjustSpeed;
  
  // set motor to turnSpeed first
  rightMotor->setSpeed(adjustSpeed);
  leftMotor->setSpeed(adjustSpeed);

  // read sensor info and decide movement based off that
  readSensorInfo();

  if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && (midLeftSensorVal > sensorThreshold || midRightSensorVal > sensorThreshold)) {
    // check both; if both are aight then move forward
    rightMotor->setSpeed(forwardSpeed);
    leftMotor->setSpeed(forwardSpeed);
    forward();
  } 
  else if (leftSensorVal > sensorThreshold) {
    // if left sensor is over tape, turn left
    turnLeft();
  } 
  else if (rightSensorVal > sensorThreshold) {
    // if right sensor over tape, turn right
    turnRight();
  } 
  else if (leftSensorVal < sensorThreshold && rightSensorVal < sensorThreshold && midLeftSensorVal < sensorThreshold && midRightSensorVal < sensorThreshold) {
    // if none of the sensors are over tape, slowly back up
    backward();
  }
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(250);
}

void readSensorInfo() {
  /*
    Reads all sensor values and prints to Serial Monitor.
  */
  leftSensorVal = analogRead(leftSensorPin);
  rightSensorVal = analogRead(rightSensorPin);
  midLeftSensorVal = analogRead(midLeftSensorPin);
  midRightSensorVal = analogRead(midRightSensorPin);

  Serial.print(leftSensorVal);
  Serial.print(", ");
  Serial.print(midLeftSensorVal);
  Serial.print(", ");
  Serial.print(midRightSensorVal);
  Serial.print(", ");
  Serial.print(rightSensorVal);
}

void turnLeft() {
  /*
    Changes motor direction to turn left and print out speed
    of left and right motor to Serial Monitor.
  */
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

  Serial.print(", ");
  Serial.print(adjustSpeed * -1);
  Serial.print(", ");
  Serial.println(adjustSpeed);
}

void turnRight() {
  /*
    Changes motor direction to turn right and print out speed
    of left and right motor to Serial Monitor.
  */
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

  Serial.print(", ");
  Serial.print(adjustSpeed);
  Serial.print(", ");
  Serial.println(adjustSpeed * -1);
}

void forward() {
  /*
    Changes motor direction to go forwards and print out speed
    of left and right motor to Serial Monitor.
  */
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);

  Serial.print(", ");
  Serial.print(forwardSpeed);
  Serial.print(", ");
  Serial.println(forwardSpeed);
}

void backward() {
  /*
    Changes motor direction to go backwards and print out speed
    of left and right motor to Serial Monitor.
  */
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  
  Serial.print(", ");
  Serial.print(forwardSpeed * -1);
  Serial.print(", ");
  Serial.println(forwardSpeed * -1);
}