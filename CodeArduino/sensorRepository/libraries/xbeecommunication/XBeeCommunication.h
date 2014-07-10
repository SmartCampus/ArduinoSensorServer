/*
	XBeeCommunication.h - Libary for using XBee communication
*/

#include <XBee.h>
#include "Arduino.h"

#ifndef XBeeCommunication_h
#define XBeeCommunication_h

#define XBEE_WAKEUP 9
#define COMMAND_BUFFER_LENGTH 100

class XBeeCommunication
{
	public:
		XBeeCommunication();
		void send(String msg);
		void sendln(String msg);
		char* receive();
		
	private:
		void toIntArray(String str, uint8_t result[]);
		void send_internal(String msg);
};

#endif