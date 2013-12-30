/** Command to be processed */
String theCommand; 

/** Actual read index */
int readIndex; 

/** Return messages */
const String RETURN_OK           = "0 Command OK.";
const String RETURN_INVALIDPARAM = "1 Invalid parmeters.";
const String RETURN_UKNOWNCMD    = "2 Uknown command.";
const String RETURN_NAMEUSED     = "3 Name already in use.";
const String RETURN_PINUSED      = "4 Pin already in use.";
const String RETURN_TIMEERROR    = "5 Time not available for this sensor.";


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
    return RETURN_UKNOWNCMD;
    
  // Store command to process.
  theCommand = cmd;
  theCommand.trim();
  readIndex = 0;
  
  // Get command name. 
  String commandName = nextToken();
  if (commandName == NULL)
    return RETURN_UKNOWNCMD;
  
  // Check command to execute. 
  if (commandName.equals("add"))
  {
    return execCommandAdd();
  }
  
  else if (commandName.equals("del"))
  {
    return execCommandDel();
  }
  
  else if (commandName.equals("freq"))
  {
     return execCommandFreq();
  }
  
  else if (commandName.equals("listsensors"))
  {
     return execCommandListSensors();
  }
  
  else if (commandName.equals("sensorinfo"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    return execCommandSensorInfo(sname);
  }
  
  else if (commandName.equals("resetsensors"))
  {
    return execCommandResetSensors();
  }
  
  else if (commandName.equals("timestamp"))
  {
    return execCommandTimeStamp();      
  }
  
  else if (commandName.equals("boardid"))
  {
    return execCommandBoardId();
  }
  
  else if (commandName.equals("suspend"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    return execCommandSuspend(sname);
  }
  
  else if (commandName.equals("resume"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    return execCommandResume(sname);
  }
  
  else 
  {
    return RETURN_UKNOWNCMD; 
  }
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


/*******************************************************************************************
 * Commands list.
 * You can add command at the end of this section.
 *******************************************************************************************/


/**
 * Add a sensor to the Arduino platform.
 *
 * return : true if good command execution, false if not.
 */
String execCommandAdd()
{
   // Get sensor name.
    String sname = nextToken();
    
    // Get pin number.
    int pinNumber = nextTokenInt();
    
    // Get refresh data frequency. 
    int frequency = nextTokenInt();
    
    // Check parameters. 
    if ((sname == NULL) || (pinNumber < 0) || (frequency < 0))
      return RETURN_INVALIDPARAM;
    
    // Check if name or pin number are already in use.
    if (getSensorByName(sname) >= 0)
      return RETURN_NAMEUSED;
    if (getSensorByPinNumber(pinNumber) >= 0)
      return RETURN_PINUSED;        

    // Add the new sensor and return.
    addSensor(sname, pinNumber, frequency, true);
    return RETURN_OK;
}


/**
 * Delete a sensor from an Arduino platform.
 *
 * return : true if good execution, false if not.
 */
String execCommandDel()
{
  // Get sensor name.
  String sname = nextToken();
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(sname);
  
  // Check parameters. 
  if ((sname == NULL) || (sid < 0))
    return RETURN_INVALIDPARAM;
  
  // Delete the sensor (by name).
  deleteByName(sname); 
  return RETURN_OK;
}


/**
 * Change data frequency of an existing sensor. 
 *
 * return : true if good execution, false if not.
 */
String execCommandFreq()
{
  // Get the pin number. 
  String sname = nextToken();
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(sname);
  
  // Check parameters. 
  if ((sname == NULL) || (sid < 0))
    return RETURN_INVALIDPARAM;
    
  // Get the new frequency.
  int newFrequency = nextTokenInt();
  
  // Change the data refresh rate. 
  changeDataFrequencyByName(sname, newFrequency); 
  return RETURN_OK;
}


/**
 * List all the sensors of the Arduino Board.
 *
 * return : true if good execution, false if not.
 */
String execCommandListSensors()
{
  int sid = 0; 
    
  // Print all sensors name.
  String resp = "0";
  while((sid = getNextAvailableSensor(sid)) >= 0)
  {
    resp += " " + getSensorName(sid);  
    sid++;
  }
  
  return resp;
}


/** 
 * Get sensor informations from a sensor name.
 *
 * return : true if good execution, false if not.
 */
String execCommandSensorInfo(String name)
{
  // Get sensor ID.
  int sid = getSensorByName(name);
  if (sid < 0)
    return RETURN_INVALIDPARAM;
  
  // Print sensor informations.
  return "0 Name: " + getSensorName(sid) + " id: " + sid + " pin: " + getSensorPinNumber(sid) + " frequency: " + getSensorFrequency(sid);
}


/**
 * Get Arduino board current time. 
 *
 * return : true if good execution, false if not.
 */
String execCommandTimeStamp()
{
  return "0 Time: " + boardTime();
}


/**
 * Suspend a sensor.
 *
 * sname    : Sensor name.
 */
String execCommandSuspend(String sname)
{
  if (changeSensorStatus(sname, 0))
    return RETURN_OK;
  return RETURN_INVALIDPARAM;
}


/**
 * Resume a sensor.
 *
 * sname    : Sensor name.
 * sstatuts : New sensor status.
 */
String execCommandResume(String sname)
{
  if (changeSensorStatus(sname, 1))
    return RETURN_OK;
  return RETURN_INVALIDPARAM;
}



/**
 * Clear the sensors table.
 *
 * return : The command response.
 */
String execCommandResetSensors()
{
  clearTable();
  return RETURN_OK;
}


/**
 * Get Arduino board ID
 *
 * return : The command response.
 */
String execCommandBoardId()
{
  return "0 " + getId();
}

 
