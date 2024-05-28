#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>

#define BT_NAME "BT_Slave"

SoftwareSerial BTSerial(0, 1);  // RX, TX

AF_DCMotor rightwheel(4);
AF_DCMotor leftwheel(2);
Servo myServo;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  myServo.attach(10);  // Attach the servo to pin 9
  rightwheel.run(RELEASE);
  leftwheel.run(RELEASE);
}

void processPotentiometer(int value) {
  // Map the potentiometer value to the restricted servo range (67.5-112.5 degrees)
  int servoPosition = value;

  // Set the servo position based on the mapped value
  myServo.write(servoPosition);

  // Print the potentiometer value for debugging
  Serial.print("Potentiometer Value: ");
  Serial.println(value);
}

void processForceSensor(int value) {
  // Map the force sensor value to the motor speed range (0-255)
  int speed = map(value, 0, 200, 0, 255);

  // Set motor speeds based on the force sensor value
  rightwheel.run(FORWARD);
  leftwheel.run(FORWARD);
  rightwheel.setSpeed(speed);
  leftwheel.setSpeed(speed);

  // Print the force sensor value for debugging
  Serial.print("Force Sensor Value: ");
  Serial.println(value);
}



void loop() {
  while (Serial.available() > 1) {
    // Read the identifier from the master over Bluetooth
    char identifier = Serial.read();

    // Read the corresponding sensor value from the master over Bluetooth
    int sensorValue = Serial.read();

    // Handle the sensor value based on the identifier
    switch (identifier) {
      case 'P':  // Potentiometer
        processPotentiometer(sensorValue);
        break;

      case 'F':  // Force sensor
        processForceSensor(sensorValue);
        break;

      default:
        break;
    }
  }
}
