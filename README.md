## ThermoDeliver
ThermoDeliver, a sensor-driven temperature regulation system for food delivery. Features a PID system that works closely with two (2) DHT22 sensors mounted on the cooling and heating side respectively, moreover, the system allows the user to set a certain temperature threshold that will initiate the PID.

A PID library was utilized for this project, with REVERSE as its output setting. The PID takes in the sensor output as well as the user threshold values, which are automatically fitted into the PID.compute() function. As the sensor data deviates from the set user threshold, the PID output will increase as well, which is then used to decrement the motor speed.
