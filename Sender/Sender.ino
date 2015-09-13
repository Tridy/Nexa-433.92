#include "NexaSender.h"

unsigned long _deviceId = 55799201;
const byte _pinId = 11;

const byte _groupId = 3;
const byte _buttonId = 3;

NexaSender _sender(_pinId, _deviceId);


void setup()
{

}

void loop()
{
	_sender.SendDeviceOnSignal(_groupId, _buttonId);
	delay(500);
	_sender.SendDeviceOffSignal(_groupId, _buttonId);
	delay(2000);
}