//PID Library
#include <PID_v1.h>

//PID setpoints
  int user_value_cold, user_value_heat;
  double setpoint_cold;
  double setpoint_heat;
  double input_cold, input_heat, output_cold, output_heat;
  double Kp_heat = 0.5, Ki_heat = 0.5, Kd_heat = 0.5;
  double Kp_cold = 0.5, Ki_cold = 0.5, Kd_cold = 0.5;

//PID Constants
PID pid_cold(&input_cold, &output_cold, &setpoint_cold, Kp_cold, Ki_cold, Kd_cold, REVERSE);
PID pid_heat(&input_heat, &output_heat, &setpoint_heat, Kp_heat, Ki_heat, Kd_heat, REVERSE);


//Temperature OFFSET
float tempOffset = 0.0;
float humidityOffset = 0.0;


//DHT22 Sensors Library
#include <DHT.h>
#include <DHT_U.h>
#include "thingProperties.h"

//DHT22 Sensors
#define DHT_SENSOR_PIN_heat A0
#define DHT_SENSOR_PIN_cold A1
#define DHT_SENSOR_TYPE DHT22

//DHT22 Sensors Declaration  
DHT dht_sensor_heat(DHT_SENSOR_PIN_heat, DHT_SENSOR_TYPE);
DHT dht_sensor_cold(DHT_SENSOR_PIN_cold, DHT_SENSOR_TYPE);


//Cold Side BTS7960
int RPWM_COLD = 8;
int L_EN_COLD = 9;
int R_EN_COLD = 10;


int motorSpeedheat_decrement = (output_heat);
int motorSpeedcold_decrement = (output_cold);

//Heat Side BTS7960
int RPWM_HEAT = 5;
int L_EN_HEAT = 6;
int R_EN_HEAT = 7;

void setup() {

  //PID SETUP
  pid_cold.SetMode(AUTOMATIC);
  pid_heat.SetMode(AUTOMATIC);

  //DHT SENSORS PINOUT
  pinMode(DHT_SENSOR_PIN_heat, INPUT);
  pinMode(DHT_SENSOR_PIN_cold, INPUT);

  //BTS7960 Motor Driver PINOUT
  pinMode(R_EN_COLD, OUTPUT);
  pinMode(RPWM_COLD, OUTPUT);
  pinMode(L_EN_COLD, OUTPUT);

  pinMode(R_EN_HEAT, OUTPUT);
  pinMode(RPWM_HEAT, OUTPUT);
  pinMode(L_EN_HEAT, OUTPUT);

  //DHT SENSOR BEGIN
  dht_sensor_heat.begin();
  dht_sensor_cold.begin();
    
  //HEATING SIDE
  digitalWrite(R_EN_HEAT, HIGH);
  digitalWrite(L_EN_HEAT, HIGH);

  //COLD SIDE
  digitalWrite(R_EN_COLD, HIGH);
  digitalWrite(L_EN_COLD, HIGH);
  
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  
  ArduinoCloud.update();

  int humi_heat = dht_sensor_heat.readHumidity() + humidityOffset;
  input_heat = dht_sensor_heat.readTemperature() + tempOffset;

  temp_heat = input_heat;
  temp_cold = input_cold;

  int humi_cold = dht_sensor_cold.readHumidity() + humidityOffset;
  input_cold = dht_sensor_cold.readTemperature() + tempOffset;

  
  if(isnan(humi_heat) || isnan(input_heat) || isnan(input_cold) || isnan(humi_cold)){
    Serial.println("Failed to read");
  }
  else{

    setpoint_heat = user_input_heat;
    setpoint_cold = user_input_cold;
  
    pid_cold.Compute();
    pid_heat.Compute();
    
    Serial.println("Heat Side Temperature"); Serial.println(input_heat);
    Serial.println("Heat Side PID"); Serial.println(output_heat);
    Serial.println(" | ");
    Serial.println("Cold Side Temperature"); Serial.println(input_cold);
    Serial.println("Cold Side PID"); Serial.println(output_cold);

  }
 
  delay(2000);

  onUserInputColdChange();
  onUserInputHeatChange();
 
}

void onUserInputColdChange() {
  if (input_cold >= user_input_cold){
     analogWrite(RPWM_COLD, 255);
     //user_value_cold = user_input_cold;
  } else {
    analogWrite(RPWM_COLD, 255 - (output_cold * 1.2));
  }

}

void onUserInputHeatChange()  {
  if(input_heat >= user_input_heat){
    analogWrite(RPWM_HEAT, 255 - (output_heat * 1.2));
  } 
  else{
    analogWrite(RPWM_HEAT, 255);
  }
    
  }
