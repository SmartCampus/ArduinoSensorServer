#include "SerialCommunication.h"
#include <Arduino.h>

#define COMMAND_BUFFER_LENGTH 100


SerialCommunication::SerialCommunication()
{
}
		
void SerialCommunication::send(String msg)
{
	Serial.print(msg);	
	
}

void SerialCommunication::sendln(String msg)
{
	Serial.println(msg);	
	
}

char* SerialCommunication::receive()
{
	Serial.flush();

	/** Command buffer */
	char command[COMMAND_BUFFER_LENGTH] = {0};
	
    // Check if something to read.
  	if (Serial.available())
  	{  
    int cnx = 0;
    int c = 0;
    int nbEndInput = 0;
    while (((c = Serial.read()) != '\n') && (c != '\r') && (cnx < COMMAND_BUFFER_LENGTH - 1))
    {
      if (c <= 0)
      {
        // Check excessive number of consecutive end input.
        nbEndInput++; 
        if (nbEndInput >= 10)
          break;
        delay(1);
      }
      else
      {
        nbEndInput = 0;
        command[cnx++] = c;
      }
    }
    command[cnx] = 0;
  }
   return command;
}
