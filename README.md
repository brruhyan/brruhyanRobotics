## Index
[ThermoDeliver](https://github.com/brruhyan/brruhyanRobotics/tree/main/PID_Temperature_Control) <br>
[Sumobot](https://github.com/brruhyan/brruhyanRobotics/tree/main/Sumobot) <br>
[IoT-enalbed Wireless Control](https://github.com/brruhyan/brruhyanRobotics/tree/main/IoT_Enabled_Wireless_Control) <br>



## ThermoDeliver
ThermoDeliver, a sensor-driven temperature regulation system for food delivery. Features a PID system that works closely with two (2) DHT22 sensors mounted on the cooling and heating side respectively, moreover, the system allows the user to set a certain temperature threshold that will initiate the PID.

A PID library was utilized for this project, with REVERSE as its output setting. The PID takes in the sensor output as well as the user threshold values, which are automatically fitted into the PID.compute() function. As the sensor data deviates from the set user threshold, the PID output will increase as well, which is then used to decrement the motor speed.

## IoT-enabled Wireless Control
A wireless controller which involves non-conventional components for controlling the movement of an RC Car. A potentiometer attached to the master module controls the direction of the RC car through the use of servos. A pressure sensor is then utilized to control the acceleration of the motors.

## SumoBot 
An automated robotic system with an Arduino UNO R3 at its core. Automation is achieved through various sensors, in conjunction with an L298N Motor Driver.
