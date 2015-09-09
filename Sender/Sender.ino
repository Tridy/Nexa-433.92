int ledPin = 11;
int unitLength = 250;
int longLowRatio = 5;
int introLowRatio = 10;
int endPauseRatio = 40;

bool _binarySignalData [33];


void setup()
{
	pinMode(ledPin, OUTPUT);
	/* add setup code here */

}

void loop()
{

	SendOeviceOnSignal(55799201, 3, 3);

	delay(500);

	SendDeviceOffSignal(55799201, 3, 3);

	Serial.println("SENT");
	delay(2000);
}

void SendAllGroupOffSignal(unsigned long deviceId)
{
	SendSignal(deviceId, true, false, 3, 3);
}

void SendAllGroupOnSignal(unsigned long deviceId)
{
	SendSignal(deviceId, true, true, 3, 3);
}

void SendDeviceOffSignal(unsigned long deviceId, byte groupId, byte buttonId)
{
	SendSignal(deviceId, false, false, groupId, buttonId);
}

void SendOeviceOnSignal(unsigned long deviceId, byte groupId, byte buttonId)
{
	SendSignal(deviceId, false, true, groupId, buttonId);
}

void SendSignal(unsigned long deviceId, bool turnAllOff, bool turnOn, byte groupId, byte buttonId)
{
	AssignDeviceIdToSignalData(deviceId);
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

void AssignDeviceIdToSignalData(unsigned long deviceId)
{
	char buf[27];
	String deviceString = String(deviceId, BIN);

	deviceString.toCharArray(buf, 27);

	int j;
	for (j = 0; j < 26; j++)
	{
		_binarySignalData[j] = (buf[j] == '1');
	}
}

void AssignTurnAllOffToSignalData(bool turnAllOff)
{
	_binarySignalData[26] = !turnAllOff;
}

void AssignTurnOnToSignalData(bool turnOn)
{
	_binarySignalData[27] = !turnOn;
}

void AssignGroupIdToSignalData(byte groupId)
{
	_binarySignalData[28] = groupId & 10;
	_binarySignalData[29] = groupId & 1;
}

void AssignButtonIdToSignalData(byte buttonId)
{
	_binarySignalData[30] = buttonId & 10;
	_binarySignalData[31] = buttonId & 1;
}

void Send()
{
	int i;
	int j;

	pinMode(ledPin, OUTPUT);

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

void SendIntro()
{
	SendSignal(introLowRatio);
}

void SendOne()
{
	SendSignal(1);
	SendSignal(longLowRatio);
}

void SendZero()
{
	SendSignal(longLowRatio);
	SendSignal(1);
}

void SendSignal(int lowUnitsCount)
{
	digitalWrite(ledPin, HIGH);
	delayMicroseconds(unitLength);
	digitalWrite(ledPin, LOW);
	delayMicroseconds(unitLength * lowUnitsCount);
}