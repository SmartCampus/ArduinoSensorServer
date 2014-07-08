#include <XBee.h>
#include "Arduino.h" 
#include "xbeecommunication.h"


/* Global objects */
XBee xbee = XBee();

XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();
TxStatusResponse txStatus = TxStatusResponse();


XBeeCommunication::XBeeCommunication()
{
	xbee.setSerial(Serial);
}

void XBeeCommunication::sendln(String msg)
{
	send(msg + '\n');
	
}		
void XBeeCommunication::send_internal(String msg)
{
	// Define the XBee frame payload
	uint8_t payload[msg.length()];
	
	// Convert message into a int array
	toIntArray(msg, payload);
	
	//Build the request
	Tx16Request tx = Tx16Request(0x1234, payload, sizeof(payload));
	
	//Send the request
	xbee.send(tx);
	
	// Check status response
	if (xbee.readPacket(5000)){
		if(xbee.getResponse().getApiId() == TX_STATUS_RESPONSE){
			xbee.getResponse().getZBTxStatusResponse(txStatus);
               
           	if (txStatus.getStatus() != SUCCESS) {
           		// No ACK from remote, retry sending
           		send_internal(msg);
           	}

		}	
	}
	
	
	
}

void XBeeCommunication::send(String msg)
{
	
	// Switch on XBee chip
	digitalWrite(XBEE_WAKEUP, HIGH);

	// Wait for XBee being fully operational
	
	delay(1000);
	
	// Send message	
	send_internal(msg);
	
	
	// Switch off XBee chip
	digitalWrite(XBEE_WAKEUP, LOW);


	
	
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