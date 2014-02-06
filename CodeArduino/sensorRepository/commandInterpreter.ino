/** Return messages */
#define RETURN_OK            0
#define RETURN_INVALIDPARAMS 1
#define RETURN_UKNOWNCMD     2
#define RETURN_NAMEUSED      3
#define RETURN_PINUSED       4
#define RETURN_TIMEERROR     5
#define RETURN_INVALIDFREQ   6
#define NB_RETURN_CODE       7


/** Command to be processed */
char* theCommand; 

/** Actual read index */
int readIndex; 

/** Last read token */
char lastToken[TOKEN_SIZE];


/** Return messages */
const char* RETURN_CODE_STRINGS[NB_RETURN_CODE] =
{
  "Command OK",
  "Invalid parmeters",
  "Uknown command",
  "Name already in use",
  "Pin already in use",
  "Time not available for this sensor",
  "The given frequency is inferior to 0"
};


/**
 * Execute a command from a string. 
 *
 * cmd    : Command to execute.
 *  
 * return : The command execution response.
 */
int execCommand(char* cmd, char* result)
{    
  // Store command to process.
  theCommand = cmd;
  readIndex = 0;
  
  //Serial.print("I: Command to execute : "); Serial.println(cmd);
  
  // Get command name. 
  if (nextToken())
    return RETURN_UKNOWNCMD;
    
  //Serial.print("I: Command name : "); Serial.println(lastToken);
  
/*******************************************************************************************
 * Commands execution.
 * You can add command at the end of this section.
 *******************************************************************************************/
  
  // Check command to execute. 
  if (!strcmp(lastToken, "add"))
    return execCommandAdd(result);
  
  if (!strcmp(lastToken, "del"))
    return execCommandDel(result);
  
  if (!strcmp(lastToken, "freq"))
     return execCommandFreq(result);
    
  if (!strcmp(lastToken, "listsensors"))
     return execCommandListSensors(result);
  
  if (!strcmp(lastToken, "sensorinfo"))    
    return execCommandSensorInfo(result);
  
  if (!strcmp(lastToken, "resetsensors"))
    return execCommandResetSensors(result);
  
  if (!strcmp(lastToken, "timestamp"))
    return execCommandTimeStamp(result);      
  
  if (!strcmp(lastToken, "boardid"))
    return execCommandBoardId(result);
  
  if (!strcmp(lastToken, "suspend"))  
    return execCommandSuspend(result);
  
  if (!strcmp(lastToken, "resume"))
    return execCommandResume(result);
  
  // Unknown command.
  return RETURN_UKNOWNCMD; 
}


/**
 * Get the next token in the command.
 *
 * return : 0 if token has been read, 1 if end of input.
 */
int nextToken()
{
  // Skip all blanks.
  while ((theCommand[readIndex] != 0) && (theCommand[readIndex] <= ' '))
    readIndex++;
  
  // Check if no more tokens.
  if (theCommand[readIndex] == 0)
    return 1;
  
  // Search the end of token.
  int endTok = readIndex + 1;
  while ((theCommand[endTok] != 0) && (theCommand[endTok] > ' '))
    endTok++;
  
  // Build result.
  strncpy(lastToken, theCommand + readIndex, endTok - readIndex);
  lastToken[endTok - readIndex] = 0;
  readIndex = endTok;
  return 0;
}


/**
 * Get the next token as integer. 
 *
 * res : Result int.
 *
 * return : 0 if token has been read, 1 if end of input.
 */ 
int nextTokenInt(int *res)
{
   // Check if no more token.
   if (nextToken())
     return 1; 
   
   // Check if first token is an integer.
   char c = lastToken[0];
   if (((c < '0') || (c > '9')) && (c != '-'))
     return 1;
     
   // Build result.
   *res = atoi(lastToken);
   return 0;
}


/**
 * Get the next string token.
 *
 * str : Result string (of size at least TOKEN_SIZE).
 *
 * return : 0 if token has been read, 1 if end of input.
 */
int nextTokenString(char* str)
{
   if (nextToken())
     return 1;
   strncpy(str, lastToken, TOKEN_SIZE);
   return 0;
}


/**
 * Check if sensor type is allowed.
 *
 * type   : Type to check.
 * 
 * return : 1 if sensor type is allowed, 0 if not.
 */
int isTypeAllowed(int type)
{
  return ((type >= 0) && (type < NB_SENSOR_TYPE));
}


/*******************************************************************************************
 * Commands list.
 * You can add command at the end of this section.
 *******************************************************************************************/


/**
 * Add a sensor to the Arduino platform.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandAdd(char* result)
{
   // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
     
   // Get pin number.
   int pinNumber;
   if (nextTokenInt(&pinNumber))
     return RETURN_INVALIDPARAMS;
    
   // Get refresh data frequency. 
   int frequency;
   if (nextTokenInt(&frequency))
     return RETURN_INVALIDPARAMS;
     
   // Get sensor type.
   int type;
   if (nextTokenInt(&type) || !isTypeAllowed(type))
     return RETURN_INVALIDPARAMS;
     
   // Check parameters. 
   if ((pinNumber < 0) || (frequency < 0))
     return RETURN_INVALIDPARAMS;
    
   // Check if name or pin number are already in use.
   if (getSensorByName(name) >= 0)
     return RETURN_NAMEUSED;
   if (getSensorByPinNumber(pinNumber) >= 0)
     return RETURN_PINUSED;       

   // Add the new sensor and return.
   addSensor(name, pinNumber, frequency, type, true);
   return RETURN_OK;
}


/**
 * Delete a sensor from an Arduino platform.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandDel(char* result)
{
  // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
  //Serial.print("I:|Command interpreter| Name:"); Serial.println(name);
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(name);
  if (sid < 0)
    return RETURN_INVALIDPARAMS;
  
  // Delete the sensor (by name).
  deleteById(sid);
  return RETURN_OK;
}


/**
 * Change data frequency of an existing sensor. 
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandFreq(char* result)
{
  // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
  
  // Get sensor index and check if sensor exists.
  int sid = getSensorByName(name);
  
  // Check parameters. 
  if (sid < 0)
    return RETURN_INVALIDPARAMS;
    
  // Get the new frequency.
  int newFrequency;
  if (nextTokenInt(&newFrequency))
     return RETURN_INVALIDPARAMS;
  
  // Change the data refresh rate. 
  changeDataFrequencyByName(name, newFrequency); 
  return RETURN_OK;
}


/**
 * List all the sensors of the Arduino Board.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandListSensors(char* result)
{
  int sid = 0; 
    
  // Print all sensors name.
  result[0] = 0;
  strcat(result, " ");
  while((sid = getNextAvailableSensor(sid)) >= 0)
  {
    strcat(result, getSensorName(sid));  
    strcat(result, " ");
    sid++;
  }
  
  return RETURN_OK;
}


/** 
 * Get sensor informations from a sensor name.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandSensorInfo(char* result)
{
  // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
  
  // Get sensor ID.
  int sid = getSensorByName(name);
  //Serial.print("Name: '"); Serial.print(name); Serial.print("' Sid:");Serial.println(sid);Serial.flush();
  if (sid < 0)
    return RETURN_INVALIDPARAMS;
  
  // Print sensor informations.
  sprintf(result, "Name:%s pin:%d frequency:%d type:%d", getSensorName(sid), getSensorPinNumber(sid), getSensorFrequency(sid), getSensorType(sid));
  return RETURN_OK;
}


/**
 * Get Arduino board current time. 
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandTimeStamp(char* result)
{
  sprintf(result, "Time:%ld", millis());
  return RETURN_OK;
}


/**
 * Suspend a sensor.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandSuspend(char* result)
{
  // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
  
  if (changeSensorStatus(name, 0))
    return RETURN_OK;
  return RETURN_INVALIDPARAMS;
}


/**
 * Resume a sensor.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandResume(char* result)
{
  // Get sensor name.
   char name[TOKEN_SIZE];
   if (nextTokenString(name))
     return RETURN_INVALIDPARAMS;
  
  if (changeSensorStatus(name, 1))
    return RETURN_OK;
  return RETURN_INVALIDPARAMS;
}


/**
 * Clear the sensors table.
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandResetSensors(char* result)
{
  //Serial.println("Passing in resetsensors command");
  clearTable();
  //Serial.println("I:|Command interpreter| Reset sensors OK");
  return RETURN_OK;
}


/**
 * Get Arduino board ID
 *
 * result : Result buffer to fill.
 *
 * return : exec return code.
 */
int execCommandBoardId(char* result)
{
  sprintf(result, "%s", BOARD_ID);
  return RETURN_OK;
}
