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

	   // Conversion int->charArray
   	   char respCharArray[16] = {0};
   	   int2char(resp, respCharArray);

       comm.send("R: "); 
       comm.send(respCharArray);
       comm.send(" ");
       if (result[0] != 0)
       {
         comm.send(result);
       }
       else
       {
      /*if ((resp >= 0) && (resp < NB_RETURN_CODE))
        Serial.print(RETURN_CODE_STRINGS[resp]);*/
       }
       comm.send("\n");
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
