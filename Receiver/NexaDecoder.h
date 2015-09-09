#ifndef _READINGSDECODER_h
#define _NEXADECODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class NexaDecoder
{

public:
	NexaDecoder();
	String Decode(bool signalValues[]);

private:	
	String _decodedValues;
	unsigned long _extractedValues;

	bool ProcessPairs(bool signalValues[]);
	void AddDeviceId();
	void AddSettingValue(String settingName, byte position, byte rightShift);
};

