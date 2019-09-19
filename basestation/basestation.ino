/* 
* RobotDyn ESP8266-PRO with I2C and SPI connections
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "myssid.h"
#include "esp8266-pro-pins.h"

// GPIO15 -> GND with 4.7k resistor
// EN -> 3.3v with 10k resistor
// GPIO0 -> GND to flash/program
// GPIO0 -> 3.3v to run normally

// OLED SDA -> GPIO4
// OLED SCK -> GPIO5
//SSD1306AsciiWire oled;

// RF MISO -> GPIO12
// RF MOSI -> GPIO13
// RF SCK  -> GPIO14
#define CSPIN GPIO15 // to GND with 4.7k resistor
#define CEPIN GPIO16

RF24 radio(CEPIN, CSPIN);
#define NUM_SENDERS 3
byte addresses[NUM_SENDERS][6] = { 
	"1MQTT",
	"2MQTT",
	"3MQTT",
};

#define MQTT_SERVER "192.168.1.29"
#define MQTT_TOPIC "ESP82266NRF"

WiFiClient espClient;
PubSubClient pubsubClient(espClient);

void setupWiFi()
{
    // Connect to WiFi network
    Serial.print(F("Connecting to "));
    Serial.println(MYSSID);

    WiFi.begin(MYSSID, MYPASSWORD);

    while (WiFi.status() != WL_CONNECTED) 
	{
        delay(500);
        Serial.print(F("."));
    }
    Serial.println();
    Serial.print(F("WiFi connected: "));
    Serial.println(WiFi.localIP());
}

void setupRadio()
{
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setAutoAck(1);
    radio.setRetries(15, 15);
	for (int i = 0; i < NUM_SENDERS; i++)
	{
		radio.openReadingPipe(i, addresses[i]);
	}
    radio.startListening();
}

void checkRadio()
{
	uint8_t pipeNum = 0;
    if (radio.available(&pipeNum))
    {
        uint8_t buffer;
        radio.read((uint8_t*)&buffer, sizeof(uint8_t));
		//Serial.print(pipeNum);
        //Serial.print(F(" Receiver: "));
        //Serial.println(buffer);

		String payload = "{ ";
		payload += "\"pipe\" : " + String(pipeNum) + ", ";
		payload += "\"value\" : " + String(buffer);
		payload += " }";

		Serial.println(payload);
		pubsubClient.publish(MQTT_TOPIC, payload.c_str());
    }
}

void reconnectToMQTTServer() 
{
	while (!pubsubClient.connected()) 
	{
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (pubsubClient.connect(clientId.c_str()))
		{
			// Once connected, publish an announcement...
			pubsubClient.publish(MQTT_TOPIC, "online");
		}
		else 
		{
			Serial.print("failed, rc=");
			Serial.print(pubsubClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void mqttCallback(char* topic, byte* payload, unsigned int length) 
{
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) 
	{
		Serial.print((char)payload[i]);
	}
	Serial.println();
}

void setupMQTT()
{
	pubsubClient.setServer(MQTT_SERVER, 1883);
	pubsubClient.setCallback(mqttCallback);
}

void setup()
{
    Serial.begin(115200);
    setupRadio();
    setupWiFi();
	setupMQTT();
}

void loop()
{
	if (!pubsubClient.connected()) 
	{
		reconnectToMQTTServer();
	}

	pubsubClient.loop();
    checkRadio();
}
