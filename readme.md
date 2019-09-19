# ESP8266 connected to sensors via NRF24L01 publishing via MQTT

* RobotDyn ESP8266-PRO connected to NRF24L01 listening to three pipes.
* ESP8266-PRO publishes sensor values to Mosquitto server.

* Three remote sensors connected to Arduino Pro Mini send values to ESP8266-PRO via NRF24L01.
* Sensors go to sleep periodically and put the radio to sleep as well.
* Sensor ID 0 is connected to a button and runs on 3 AA batteries. 
 * Interrupt routine wakes up Arduino and NRF24L01 radio when button pressed.
 * Arduino and radio go back to sleep after sending message.

* Node-RED on Raspberry Pi decides what to do with sensor messages.
* Sensor ID 0 messages toggle IKEA Tradfri wireles outlet via CC2531 Zigbee module connected to Raspberry Pi.

## Pictures

![Dollar store LED button repurposed](wireless-button1.JPG?raw=true)
![Another view of the Arduino and NRF24L01](wireless-button2.JPG?raw=true)
![Completed project. LED light is covered with black tape](wireless-button3.JPG?raw=true)
![Node-RED Dashboard showing the sensor values](node-red-dashboard-sensors.PNG?raw=true)
![Node-RED flow](node-red-flow.PNG?raw=true)