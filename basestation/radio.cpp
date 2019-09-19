#include "radio.h"



Radio::Radio(uint16_t cepin, uint16 cspin)
{
	mRadio = new RF24(cepin, cspin);
}

void Radio::setup(byte* addresses, int numAddresses, int addressLength)
{
	mRadio->begin();
	mRadio->setPALevel(RF24_PA_MIN);
	mRadio->setAutoAck(1);
	mRadio->setRetries(15, 15);
	for (int i = 0; i < numAddresses; i++)
	{
		mRadio->openReadingPipe(i, addresses[i]);
	}
	mRadio->startListening();
}

void Radio::loop()
{
	if (mRadio->available())
	{
		uint8_t buffer;
		mRadio->read((uint8_t*)&buffer, sizeof(uint8_t));
		Serial.print(F("Receiver: "));
		Serial.println(buffer);
		//oled.setCursor(0, 1);
		//oled.print(F("Receiver: "));
		//oled.print(buffer);
	}
}