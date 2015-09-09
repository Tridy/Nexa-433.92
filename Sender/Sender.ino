#include "NexaSender.h"

NexaSender* _sender;


void setup()
{
	unsigned long deviceId = 55799201;
	NexaSender _sender(11, deviceId);
}

void loop()
{
	_sender->SendDeviceOnSignal(3, 3);
	delay(500);
	_sender->SendDeviceOffSignal(3, 3);
	delay(2000);
}