#include <XBee.h>
#include "Arduino.h" 
#include "xbeecommunication.h"

#define COMMAND_BUFFER_LENGTH 100

/* Global objects */
XBee xbee = XBee();

XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();


XBeeCommunication::XBeeCommunication()
{
	xbee.setSerial(Serial);
}

void XBeeCommunication::sendln(String msg)
{
	send(msg + '\n');
	
}		
void XBeeCommunication::send(String msg)
{
	// Define the XBee frame payload
	uint8_t payload[msg.length()];
	
	// Convert message into a int array
	toIntArray(msg, payload);
	
	//Build the request
	Tx16Request tx = Tx16Request(0x1234, payload, sizeof(payload));
	
	//Send the request
	xbee.send(tx);
	
	
}

char* XBeeCommunication::receive()
{
	char command[COMMAND_BUFFER_LENGTH] = {0};

	xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // Got something
		if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        	// Got a rx packet
	        xbee.getResponse().getRx16Response(rx16);
//	        char* t = new char[rx16.getDataLength()];
	        if (rx16.getDataLength() < COMMAND_BUFFER_LENGTH)
	        {
	            for (int i = 0; i < rx16.getDataLength(); i++)
	            {
	            	command[i] = (char) rx16.getData(i);
	            }
	        }
		}
    }
	return command;
}

void XBeeCommunication::toIntArray(String str, uint8_t result[]){
	for (int i = 0; i < str.length(); i ++)
		result[i] = (uint8_t) str.charAt(i);
}