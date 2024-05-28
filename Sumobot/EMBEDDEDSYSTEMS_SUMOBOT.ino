int motorLPin1 = 2;
int motorLPin2 = 3;

int motorRPin1 = 4;
int motorRPin2 = 5;

int motorLSpeed = 9;
int motorRSpeed = 10;

const int trigPinR = A0;
const int echoPinR = A1;
const int trigPinL = A2;
const int echoPinL = A3;


// Ultrasonic Sensor Declaration
long durationL;
int distanceL;
int durationR;
int distanceR;

// Line Sensors (Left and Right)
const int sensorPinR = A4;
int sensorValueL = 0;
const int sensorPinL = A5;
int sensorValueR = 0;

void setup() {
  Serial.begin(9600);

  delay(3500);
  pinMode(motorLPin1, OUTPUT);
  pinMode(motorLPin2, OUTPUT);
  pinMode(motorRPin1, OUTPUT);
  pinMode(motorRPin2, OUTPUT);
  pinMode(motorLSpeed, OUTPUT);
  pinMode(motorRSpeed, OUTPUT);

  // Ultrasonic Sensor
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinR, OUTPUT);
 
}

void reverseLeftSensorWhite() {
  Serial.println("LEFT WHITE");

  analogWrite(motorLSpeed, 150);
  analogWrite(motorRSpeed, 150);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);
  delay(500);
  analogWrite(motorLSpeed, 255);
  analogWrite(motorRSpeed, 150);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);
  delay(300);
  delay(50);
 
 
}

void reverseRightSensorWhite() {
  Serial.println("RIGHT WHITE");
  analogWrite(motorLSpeed, 150);
  analogWrite(motorRSpeed, 150);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);
  delay(500);
  analogWrite(motorLSpeed, 150);
  analogWrite(motorRSpeed, 255);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);
  delay(300);
  delay(50);
 

}


void loop() {
    
  //LINE SENSORS RIGHT
  sensorValueR = digitalRead(sensorPinR);
  Serial.print("Right:");
  Serial.println(sensorValueR);
  delay(5);
  
  //LINE SENSOR LEFT
  sensorValueL = digitalRead(sensorPinL);
  Serial.print("Left:");
  Serial.println(sensorValueL);
  delay(5);

  //ULTRASONIC SENSOR LEFT
  digitalWrite(trigPinL,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH, 8750ul);
  distanceL = durationL * 0.034 / 2;

    //ULTRASONIC SENSOR RIGHT
  digitalWrite(trigPinR,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH, 9750ul);
  distanceR = durationR * 0.034 / 2;

  

  bool leftSensorWhite = sensorValueL ==0;
  bool rightSensorWhite = sensorValueR ==0;

   
 
  if (leftSensorWhite) {
    
    reverseLeftSensorWhite();
 

  }
  
  else if (rightSensorWhite){

    reverseRightSensorWhite();
  }



  
  bool frontSpeedUpLeft = distanceL > 0 && distanceL < 15;
  bool frontSpeedUpRight = distanceR > 0 && distanceR < 15;
  


  if (frontSpeedUpLeft){
    Serial.println("LEFT DETECTED");
  
   analogWrite(motorLSpeed, 255);
  analogWrite(motorRSpeed, 200);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);
   delay(50);

  }

  if (frontSpeedUpRight){
    Serial.println("RIGHT DETECTED");
   analogWrite(motorLSpeed, 200);
  analogWrite(motorRSpeed, 255);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);\
  delay(50);

  }
  else {
  analogWrite(motorLSpeed, 100);
  analogWrite(motorRSpeed, 100);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);
  }
  

  }




  

