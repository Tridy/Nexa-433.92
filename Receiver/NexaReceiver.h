#ifndef _NEXARECEIVER_h
#define _NEXARECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

class NexaReceiver
{

 public:
	 NexaReceiver(int pinId);
	 void Receive(bool receivedData[]);

 private:
	 int _pinId;
	 bool* _readValues;
	 unsigned long _extractedValues;
	 int _counter;
	 unsigned long _timing;
	 
	 void ResetVariables();
	 void ReceiveSignal();
	 void WaitForLongLow();
	 void ReadLows();
};




