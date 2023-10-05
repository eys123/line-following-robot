const int leftSensorPin = A0;
const int rightSensorPin = A1;
int leftSensorVal = 0;
int rightSensorVal = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  leftSensorVal = analogRead(leftSensorPin);
  rightSensorVal = analogRead(rightSensorPin);
  // print the results to the Serial Monitor:
  printSensorInfo();
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(250);
}

void printSensorInfo() {
  Serial.print("[");
  Serial.print(leftSensorVal);
  Serial.print(", ");
  Serial.print(rightSensorVal);
  Serial.println("]");
}