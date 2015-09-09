#include "NexaDecoder.h"
#include "NexaReceiver.h"

const int PinId = 8;
bool _receivedCode[65];


void setup()
{
	
}
void loop()
{
	ResetResult();
	NexaReceiver(PinId).Receive(_receivedCode);
	String decodedValue = NexaDecoder().Decode(_receivedCode);
	Serial.println(decodedValue);

	delay(1000);
}

void ResetResult()
{
	for (size_t i = 0; i < 65; i++)
	{
		_receivedCode[i] = 0;
	}
}