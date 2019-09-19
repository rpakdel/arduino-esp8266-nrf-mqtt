 /*
* Basic sender based on RF24 example
*/

#include <LowPower.h>
#include <RF24_config.h>
#include <printf.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LowPower.h>

#define NUM_SENDERS 3
#define SENDER 0

#define CEPIN 9
#define CSPIN 10

RF24 radio(CEPIN, CSPIN);

byte addresses[NUM_SENDERS][6] = {
	"1MQTT",
	"2MQTT",
	"3MQTT",
};

void setup() 
{    
	pinMode(2, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.print(F("SENDER"));
    Serial.println(SENDER);

	radio.begin();
    radio.setRetries(15, 15);
    radio.setPALevel(RF24_PA_MIN);
    radio.openWritingPipe(addresses[SENDER]);
	radio.stopListening();
	radio.powerDown();
}

uint8_t count = 0;
void sendValue()
{
	Serial.print(F("Sending "));
	Serial.print(count);
	radio.powerUp();
	if (!radio.write((uint8_t*)&count, sizeof(uint8_t)))
	{
		Serial.println(F("...no ack"));

	}
	else
	{
		Serial.println(F("...ack"));
	}
	radio.powerDown();
	count++;
}

void wakeup()
{
	noInterrupts();
	sendValue();
	interrupts();
}

void loop()
{
	Serial.println("attach, sleep");
	attachInterrupt(digitalPinToInterrupt(2), wakeup, FALLING);
	LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
	delay(100);
	Serial.println("wakeup, detach");
	detachInterrupt(0);
}
