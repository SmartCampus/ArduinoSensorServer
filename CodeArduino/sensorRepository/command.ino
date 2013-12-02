/** Command to be processed */
String theCommand; 

/** Actual read index */
int readIndex; 

/** No command case */
const String NO_COMMAND = "No command to process";

/** Invalid parameters */
const String INVALID_PARAM = "Invalid parmeters.";

/** Command accepted */
const String OK_COMMAND = "Command OK.";


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
  
  // Get command name. 
  String commandName = nextToken();
  if (commandName == NULL)
    return NO_COMMAND;
  
  // Check command to execute.
  if (commandName.equals("add"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    // Get pin number.
    int pinNumber = nextTokenInt();
    
    // Get refresh data frequency. 
    int frequency = nextTokenInt();
    
    // Check parameters. 
    if ((sname == NULL) || (pinNumber < 0) || (frequency < 0))
      return INVALID_PARAM;
    
    // Add the new sensor and return.
    addSensor(sname, pinNumber, frequency, true);
    return OK_COMMAND;
    
  }
  else if (commandName.equals("del"))
  {
    // Get sensor name.
    String sname = nextToken();
    
    // Get pin number.
    int pinNumber = sname.toInt();
    
    // Delete the sensor (from name or ID).
    if (pinNumber == 0)
      deleteByName(sname);
    deleteById(pinNumber);   
    return OK_COMMAND;
  }
  else if (commandName.equals("changeFreq"))
  {
    // Get the pin number. 
    int pinNumber = nextTokenInt();
    
    // Get the new frequency.
    int newFrequency = nextTokenInt();
    
    // Change the data refresh rate. 
    changeDataFrequency(pinNumber, newFrequency);
    return OK_COMMAND;   
  }
  else 
  {
    return "Unknown command."; 
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
