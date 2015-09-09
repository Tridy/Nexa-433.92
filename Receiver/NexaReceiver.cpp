#include "NexaReceiver.h"

const int MaxReadingsCount = 65;

NexaReceiver::NexaReceiver(int pinId)
{
	pinMode(pinId, INPUT);
	_pinId = pinId;
}

void NexaReceiver::Receive(bool receivedData[])
{
	_readValues = receivedData;
	ResetVariables();
	ReceiveSignal();
}

void NexaReceiver::ResetVariables()
{
	_extractedValues = 0;
	_counter = 0;
	_timing = 0;
}

void NexaReceiver::ReceiveSignal()
{
	WaitForLongLow();
	ReadLows();
}

void NexaReceiver::WaitForLongLow()
{
	while ((_timing < 9500 || _timing > 10350))
	{
		_timing = pulseIn(_pinId, LOW, 1000000);
	}
}

void NexaReceiver::ReadLows()
{
	while (_counter < MaxReadingsCount)
	{
		_timing = pulseIn(_pinId, LOW, 1000000);
		_readValues[_counter] = _timing < 500;
		_counter = _counter + 1;
	}
}