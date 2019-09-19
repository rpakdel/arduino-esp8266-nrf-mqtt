#pragma once

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class Radio
{
public:
	Radio(uint16_t cepin, uint16 cspin);

	void setup(byte* addresses, int numAddresses, int addressLength);
	void loop();
private:
	RF24* mRadio;
};

