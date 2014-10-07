/** Maximum delay of the main loop */
#define MAX_LOOP_DELAY 1000

/** Max size of the receiving buffer */
#define COMMAND_BUFFER_LENGTH 100 

/** Response buffer length */
#define RESPONSE_BUFFER_LENGTH 200

/** Arduino setup end message */
#define SETUP_TERMINATED "I: Setup terminated\n\r"

/** Command buffer */
char command[COMMAND_BUFFER_LENGTH];

/** Command response buffer */
char result[RESPONSE_BUFFER_LENGTH];

void int2char(int a, char * result){
  String str;
  str = String(a);
  str.toCharArray(result, 16);
}

void setup()
{
  #ifdef USE_XBEE
  pinMode(XBEE_WAKEUP, OUTPUT);
  #endif
  Serial.begin(9600);
  comm.send(SETUP_TERMINATED); 
  Serial.flush();
}


void loop()
{      
  // Adaptative loop delay.
  int loopDelay = MAX_LOOP_DELAY;
  
  char* got = comm.receive();
  String received;
  received = String(got);
  Serial.flush();
  // Check if something to read.
  if (received != "")
  {  
       // Execute the command.
       result[0] = 0;
       int resp = execCommand(got, result);
       
       String toSend = "R: ";
       

       if (result[0] != 0)
       {
         toSend += resp;
         toSend += " ";
         toSend += result;
       }
       else
       {
        toSend += resp;
       }
       
       comm.sendln(toSend);
       Serial.flush();
  
  }
  else
  {
    if (loopDelay < MAX_LOOP_DELAY)
    {
      loopDelay += 10;
      if (loopDelay > MAX_LOOP_DELAY)
        loopDelay = MAX_LOOP_DELAY;
    }
  }
  
  // Update sensors data.
  queryAllSensors();
  int ndelay = computeNextUpdateDelay();
  if (ndelay > loopDelay)
    ndelay = loopDelay;
  delay(ndelay);
}
