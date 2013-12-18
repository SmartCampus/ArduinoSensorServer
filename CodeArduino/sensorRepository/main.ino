#define BOARD_ID "42";

/** Check if the setup is done or not */
boolean initDone = false;

void setup()
{
  Serial.begin(9600);
  clearTable(); // Clear sensors table. 
  Serial.println("I: Tab cleared.");
  
  if (!initDone)
  {
    Serial.println("I: Arduino setup finished.");
    initDone = true;
  }
  
  
  
}

void loop()
{  
   // Character read by the serial. v
  char character;
  
  // Check if something to read.
  if (Serial.available())
  {  
    String content = ""; // Command to build.
    while (Serial.available() > 0)
    {
      character = Serial.read();
      content.concat(character);
    }
    
    // Execute the command.
    // Serial.print("Received command : "); Serial.println(content);
    Serial.println(execCommand(content));
  }
  
  // Update sensors data.
  queryAllSensors();
  delay(1000);
}

/**
* Get Board Unique ID (BUID)
*
* return Board ID
*/
String getId(){
    return BOARD_ID; 
}
