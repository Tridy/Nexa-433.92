#include "NexaDecoder.h"

const int MaxReadingsCount = 65;

NexaDecoder::NexaDecoder()
{

}

String NexaDecoder::Decode(bool* signalValues)
{
	_decodedValues = "";

	bool isValid = ProcessPairs(signalValues);
	
	if (!isValid)
	{
		return "CHECKSUM ERROR of: " + String(_extractedValues);
	}

	AddDeviceId();
	AddSettingValue("AllOff", 32, 5);
	AddSettingValue("SetOn", 16, 4);
	AddSettingValue("Group", 12, 2);
	AddSettingValue("ButtonId", 3, 0);

	return _decodedValues;
}

bool NexaDecoder::ProcessPairs(bool* signalValues)
{
	int i;
	bool isValid = true;
	byte bit = 0;
	for (i = 1; i < MaxReadingsCount - 1; i = i + 2)
	{
		bit = signalValues[i];
		_extractedValues <<= 1;
		_extractedValues |= bit;
		if (!(signalValues[i] ^ signalValues[i + 1]))
		{
			isValid = false;
		}
	}

	return isValid;
}

void NexaDecoder::AddDeviceId()
{
	unsigned long deviceId = _extractedValues >> 6;
	_decodedValues += "DeviceId=" + String(deviceId);
}

void NexaDecoder::AddSettingValue(String settingName, byte position, byte rightShift)
{
	unsigned long value = _extractedValues & position;
	value >>= rightShift;
	_decodedValues += ("; " + settingName + "=" + String(value));
}