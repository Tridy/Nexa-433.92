#ifndef _NEXASENDER_h
#define _NEXASENDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class NexaSender
{

public:
	NexaSender(int pinId, unsigned long deviceId);
	void SendAllGroupOffSignal();
	void SendAllGroupOnSignal();
	void SendDeviceOffSignal(byte groupId, byte buttonId);
	void SendDeviceOnSignal(byte groupId, byte buttonId);

private:
	unsigned long _deviceId;
	int _pinId;
	int unitLength;
	int longLowRatio;
	int introLowRatio ;
	int endPauseRatio;
	// bool *_binarySignalData;

	void SendSignal(bool turnAllOff, bool turnOn, byte groupId, byte buttonId);
	void AssignDeviceIdToSignalData();
	void AssignTurnAllOffToSignalData(bool turnAllOff);
	void AssignTurnOnToSignalData(bool turnOn);
	void AssignGroupIdToSignalData(byte groupId);
	void AssignButtonIdToSignalData(byte buttonId);
	void Send();
	void SendIntro();
	void SendOne();
	void SendZero();
	void SendSignal(int lowUnitsCount);
};