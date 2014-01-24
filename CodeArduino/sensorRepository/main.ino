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

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  Serial.print(SETUP_TERMINATED); 
  Serial.flush();
}


void loop()
{      
  // Adaptative loop delay.
  int loopDelay = MAX_LOOP_DELAY;
  
  // Check if something to read.
  if (Serial.available())
  {  
    //Serial.println("I:|Main loop| Read the input command ...");
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
    if (cnx != 0)
    {
       Serial.println(command); Serial.flush();
    
       // Execute the command.
       result[0] = 0;
       int resp = execCommand(command, result);
    
       Serial.print("R: "); 
       Serial.print(resp);
       Serial.print(" ");
       if (result[0] != 0)
       {
         Serial.print(result);
       }
       else
       {
      /*if ((resp >= 0) && (resp < NB_RETURN_CODE))
        Serial.print(RETURN_CODE_STRINGS[resp]);*/
       }
       Serial.print("\n");
       Serial.flush();
    }
    // Set shorter delay to quickly process next command.
    loopDelay = 10;
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
