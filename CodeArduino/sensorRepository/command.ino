/** Command to be processed */
String theCommand; 

/** Actual read index */
int readIndex; 

/** No command case */
const String NO_COMMAND = "R: No command to process";

/** Invalid parameters */
const String INVALID_PARAM = "R: Invalid parmeters.";

/** Command accepted */
const String OK_COMMAND = "R: Command OK.";


/**
 * Execute a command from a string. 
 *
 * cmd    : Command to execute.
 *  
 * return : The command execution response.
 */
String execCommand(String cmd)
{
  // Check if no command.
  if (cmd == NULL)
    return NO_COMMAND;
    
  // Store command to process.
  theCommand = cmd;
  theCommand.trim();
  readIndex = 0;
  
  // Get command name. 
  String commandName = nextToken();
  // Serial.print("Command name : "); Serial.println(commandName);
  if (commandName == NULL)
    return NO_COMMAND;
  
  // Check command to execute.
  if (commandName.equals("add"))
  {
    if (!(addCommand()))
      return INVALID_PARAM;
  }
  
  else if (commandName.equals("del"))
  {
    if (!(delCommand()))
      return INVALID_PARAM;
  }
  
  else if (commandName.equals("freq"))
  {
     if (!(freqCommand())) 
       return INVALID_PARAM;
  }
  
  else if (commandName.equals("listsensors"))
  {
    if (!(listsensorsCommand()))
      return INVALID_PARAM;
  }
  
  else if (commandName.equals("sensorinfo"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    if (!(sensorinfoCommand(sname)))
      return INVALID_PARAM;
  }
  
  else if (commandName.equals("resetsensors"))
  {
    resetSensorsCommand();
  }
  
  else if (commandName.equals("timestamp"))
  {
    if (!(timeStampCommand()))
      return INVALID_PARAM;
      
  }
  
  else 
  {
    return "R: Unknown command."; 
  }
  
  return OK_COMMAND;
}


/**
 * Get the next token in the command.
 *
 * return : The next token in the command, null if no more token.
 */
String nextToken()
{
  // Skip all blanks.
  int slen = theCommand.length();
  while ((readIndex < slen) && (theCommand.charAt(readIndex) == ' '))
    readIndex++;
  
  // Check if no more tokens.
  if (readIndex >= slen)
    return NULL;
  
  // Search the end of token.
  int endTok = theCommand.indexOf(' ', readIndex);
  if (endTok < 0) 
  {
    endTok = theCommand.length();
  }
  
  // Build result.
  String result = theCommand.substring(readIndex, endTok);
  readIndex = endTok;
  return result;  
}


/**
 * Get the next token as positive integer. 
 *
 * return : Token value as integer, -1 if none.
 */ 
int nextTokenInt()
{
   // Check if no more token.
   String stock = nextToken();
   if (stock == NULL) 
     return -1; 
   
   // Check if first token is an integer.
   char c = stock.charAt(0);
   if ((c < '0') || (c > '9')) 
     return -1;
     
   // Build result.
   return (int)stock.toInt();
}


/**
 * Add a sensor to the Arduino platform.
 *
 * return : true if good command execution, false if not.
 */
boolean addCommand()
{
   // Get sensor name.
    String sname = nextToken();
    
    // Get pin number.
    int pinNumber = nextTokenInt();
    
    // Get refresh data frequency. 
    int frequency = nextTokenInt();
    
    // Check parameters. 
    if ((sname == NULL) || (pinNumber < 0) || (frequency < 0))
      return false;
    
    // Add the new sensor and return.
    addSensor(sname, pinNumber, frequency, true);
    return true;
}


/**
 * Delete a sensor from an Arduino platform.
 *
 * return : true if good execution, false if not.
 */
boolean delCommand()
{
  // Get sensor name.
  String sname = nextToken();
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(sname);
  
  // Check parameters. 
  if ((sname == NULL) || (sid < 0))
    return false;
  
  // Delete the sensor (by name).
  deleteByName(sname); 
  return true;
}


/**
 * Change data frequency of an existing sensor. 
 *
 * return : true if good execution, false if not.
 */
boolean freqCommand()
{
  // Get the pin number. 
  String sname = nextToken();
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(sname);
  
  // Check parameters. 
  if ((sname == NULL) || (sid < 0))
    return false;
    
  // Get the new frequency.
  int newFrequency = nextTokenInt();
  
  // Change the data refresh rate. 
  changeDataFrequencyByName(sname, newFrequency); 
  return true;
}


/**
 * List all sensors plug to Arduino board.
 *
 * return : true if good execution, false if not.
 */ 
boolean listCommand()
{
  int sid = 0;
  if (getNextAvailableSensor(sid) < 0) 
    return false;
    
  // Print all the sensors. 
  Serial.print("R: Sensor array ");
  while ((sid = getNextAvailableSensor(sid)) >= 0)
  {
    Serial.print("|"); Serial.print("Sensor Name : "); Serial.print(getSensorName(sid)); 
    Serial.print(" | sensor ID : "); Serial.print(sid); Serial.print(" | sensor frequency : "); Serial.print(getSensorFrequency(sid)); Serial.print(" |"); Serial.println();
    sid++;
  } 
  return true;  
}


/**
 * List all the sensors of the Arduino Board.
 *
 * return : true if good execution, false if not.
 */
boolean listsensorsCommand()
{
  int sid = 0; 
  if (getNextAvailableSensor(sid) < 0)
    return false;
    
  // Print all sensors name.
  Serial.print("R:");
  while((sid = getNextAvailableSensor(sid)) >= 0)
  {
    Serial.print(" "); Serial.print(getSensorName(sid));  
    sid++;
  }
  
  Serial.println();
  return true;
}


/** 
 * Get sensor informations from a sensor name.
 *
 * return : true if good execution, false if not.
 */
boolean sensorinfoCommand(String name)
{
  // Get sensor ID.
  int sid = getSensorByName(name);
  if (sid < 0)
    return false;
  
  // Print sensor informations.
  Serial.print("R: ");
  Serial.print("name : "); Serial.print(getSensorName(sid)); 
  Serial.print(" id : "); Serial.print(sid); Serial.print(" pin : ");Serial.print(getSensorPinNumber(sid)); Serial.print(" frequency : ");  Serial.print(getSensorFrequency(sid)); Serial.println();
  return true;
}



/**
 * Get Arduino board current time. 
 *
 *
 * return : true if good execution, false if not.
 */
boolean timeStampCommand()
{
  int time = boardTime();
  if (time < 0)
    return false;
  Serial.print("R: Arduino time : "); Serial.print(time); Serial.println(" s.");
  return true;
}


/**
 * Clear the sensors table.
 *
 * return : None.
 */
void resetSensorsCommand()
{
  clearTable();
}


 
