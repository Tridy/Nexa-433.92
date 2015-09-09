#include "NexaSender.h"

NexaSender::NexaSender(int pinId, unsigned long deviceId)
{
	_pinId = pinId;
	_deviceId = deviceId;
	unitLength = 250;
	longLowRatio = 5;
	introLowRatio = 10;
	endPauseRatio = 40;
	_binarySignalData[33];
}


void NexaSender::SendAllGroupOffSignal()
{
	SendSignal(true, false, 3, 3);
}

void NexaSender::SendAllGroupOnSignal()
{
	SendSignal(true, true, 3, 3);
}

void NexaSender::SendDeviceOffSignal(byte groupId, byte buttonId)
{
	SendSignal(false, false, groupId, buttonId);
}

void NexaSender::SendDeviceOnSignal(byte groupId, byte buttonId)
{
	SendSignal(false, true, groupId, buttonId);
}

void NexaSender::SendSignal(bool turnAllOff, bool turnOn, byte groupId, byte buttonId)
{
	Serial.print("#:" + String(_deviceId));

	AssignDeviceIdToSignalData();
	AssignTurnAllOffToSignalData(turnAllOff);
	AssignTurnOnToSignalData(turnOn);
	AssignGroupIdToSignalData(groupId);
	AssignButtonIdToSignalData(buttonId);

	Serial.println("");

	for (size_t i = 0; i < 32; i++)
	{
		Serial.print(_binarySignalData[i]);
	}

	Serial.println("");

	Send();
}

void NexaSender::AssignDeviceIdToSignalData()
{
	char buf[27];
	String deviceString = String(_deviceId, BIN);

	deviceString.toCharArray(buf, 27);

	int j;
	for (j = 0; j < 26; j++)
	{
		_binarySignalData[j] = (buf[j] == '1');
	}
}

void NexaSender::AssignTurnAllOffToSignalData(bool turnAllOff)
{
	_binarySignalData[26] = !turnAllOff;
}

void NexaSender::AssignTurnOnToSignalData(bool turnOn)
{
	_binarySignalData[27] = !turnOn;
}

void NexaSender::AssignGroupIdToSignalData(byte groupId)
{
	_binarySignalData[28] = groupId & 10;
	_binarySignalData[29] = groupId & 1;
}

void NexaSender::AssignButtonIdToSignalData(byte buttonId)
{
	_binarySignalData[30] = buttonId & 10;
	_binarySignalData[31] = buttonId & 1;
}

void NexaSender::Send()
{
	int i;
	int j;

	pinMode(_pinId, OUTPUT);

	for (i = 0; i < 5; i++)
	{
		SendIntro();

		for (j = 0; j < 32; j++)
		{
			if (_binarySignalData[j])
			{
				SendOne();
			}
			else
			{
				SendZero();
			}
		}

		SendSignal(endPauseRatio);
	}
}

void NexaSender::SendIntro()
{
	SendSignal(introLowRatio);
}

void NexaSender::SendOne()
{
	SendSignal(1);
	SendSignal(longLowRatio);
}

void NexaSender::SendZero()
{
	SendSignal(longLowRatio);
	SendSignal(1);
}

void NexaSender::SendSignal(int lowUnitsCount)
{
	digitalWrite(_pinId, HIGH);
	delayMicroseconds(unitLength);
	digitalWrite(_pinId, LOW);
	delayMicroseconds(unitLength * lowUnitsCount);
}