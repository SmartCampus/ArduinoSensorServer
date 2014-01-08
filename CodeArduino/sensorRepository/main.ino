#define MAX_LOOP_DELAY 1000
#define SETUP_TERMINATED "I: Setup terminated\n\r"

/** Command buffer */
char command[100];

/** Command response buffer */
char result[200];

void setup()
{
  /*command = (char*)malloc(100);
  result = (char*)malloc(200);*/
  
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
    int cnx = 0;
    while (Serial.available())
    {
      int c = Serial.read();
      if (c == '\n')
        break;
      if (c != '\r')
        command[cnx++] = c;
    }
    command[cnx] = 0;
    Serial.print("I:|Main loop| command received :"); Serial.println(command); Serial.flush();
    
    
    // Serial.print("I: Command size received : "); Serial.println(cnx); 
    
    // Execute the command.
    result[0] = 0;
    Serial.print("I:|Main loop| command "); Serial.print(command); Serial.println(" in execution ..."); Serial.flush();
    int resp = execCommand(command, result);
    Serial.print("I:|Main loop| command "); Serial.print(command); Serial.print(" executed. Result: "); Serial.println(resp); Serial.flush();
    
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
    Serial.println();
    Serial.flush();
    Serial.print("I:|Main loop| return code "); Serial.print(resp); Serial.println(" sent."); Serial.flush();
    
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
  delay(loopDelay);
}
