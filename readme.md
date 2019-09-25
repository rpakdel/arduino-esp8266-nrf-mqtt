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

![Basestation with ESP8266 MQTT client and NRF24L01 receiver.](basestation.JPG?raw=true)
Basestation with ESP8266 MQTT client and NRF24L01 receiver.

![Wireless button PCB design in Fritzing.](wireles-button-fritzing.png?raw=true)Wireless button PCB design in Fritzing.

![Dollar store LED light repurposed.](wireless-button1.JPG?raw=true)
Dollar store LED light repurposed.

![Another view of the Arduino and NRF24L01.](wireless-button2.JPG?raw=true)
Another view of the Arduino and NRF24L01. Had many connection issues with the female headers. Also many issues with power stability which required 2x 0.1uF capacitors.

![Completed project. The red LED light is covered with black tape.](wireless-button3.JPG?raw=true)
Completed project. The red power LED light is covered with black tape. 

![Node-RED Dashboard showing the sensor values](node-red-dashboard-sensors.PNG?raw=true)
<br/>
Node-RED Dashboard showing the sensor values (currently just counting to 0 to 255).

![Node-RED flow](node-red-flow.PNG?raw=true)
Node-RED flow for the sensors.

![Node-RED flow IKEA](node-red-flow-ikea.PNG?raw=true)
Node-RED flow for turning IKEA Tradfri outlet on/off with auto-off feature.
