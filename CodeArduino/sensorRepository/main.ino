#define MAX_LOOP_DELAY 1000

/** Command buffer */
char* command;

/** Command response buffer */
char* result;

void setup()
{
  command = (char*)malloc(100);
  result = (char*)malloc(200);
  
  Serial.begin(9600);
  // clearTable(); // Clear sensors table. 
  Serial.println("I: Tab cleared.");
  Serial.println("I: Setup terminated");
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
      command[cnx++] = c;
    }
    command[cnx] = 0;
    
    // Serial.print("I: Command size received : "); Serial.println(cnx); 
    
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
    Serial.println();
    
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
