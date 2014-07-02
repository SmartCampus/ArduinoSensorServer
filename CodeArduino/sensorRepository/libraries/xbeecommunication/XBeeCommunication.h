/*
	XBeeCommunication.h - Libary for using XBee communication
*/

#include <XBee.h>
#include "Arduino.h"

#ifndef XBeeCommunication_h
#define XBeeCommunication_h


class XBeeCommunication
{
	public:
		XBeeCommunication();
		void send(String msg);
		void sendln(String msg);
		char* receive();
		
	private:
		void toIntArray(String str, uint8_t result[]);
};

#endif