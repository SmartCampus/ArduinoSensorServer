/*
	SerialCommunication.h - Libary for using serial communication
*/
#include <Arduino.h>

#ifndef SerialCommunication_h
#define SerialCommunication_h




class SerialCommunication
{
	public:
		SerialCommunication();
		void send(String msg);
		void sendln(String msg);
		char* receive();
		
};

#endif