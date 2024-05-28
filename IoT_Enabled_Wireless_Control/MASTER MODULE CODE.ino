#include <SoftwareSerial.h>
#define BT_NAME "BT_Master"
#define SLAVE_ADDRESS "0022:09:01A40B"

SoftwareSerial BTSerial(0, 1);  // RX, TX

const int potPin = A0;
const int forceSensorPin = A1;
const int slidepotentiometerPin = A2;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int forceSensorValue = analogRead(forceSensorPin);
  int slidepotentiometerValue = analogRead(slidepotentiometerPin);
  int servoPositionMapped = map(potValue,0,1024,67.5,112.5);

  Serial.write("P");
  Serial.write(servoPositionMapped);
  delay(50);

  Serial.write("F");
  Serial.write(forceSensorValue);
  delay(100);


 delay(100); // Adjust the delay as needed
}
