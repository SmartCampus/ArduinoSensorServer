void setup()
{
  Serial.begin(9600);
  clearTable(); // Clear sensors table. 
  Serial.println("I : Tab cleared.");
  
  // Method add test.
  int sensor = addSensor("temperature1", 1, 3, true); 
  Serial.print("I : Sensor created : "); 
  Serial.println(sensor);
  Serial.println("Arduino setup finished");
}

void loop()
{  
  char character; // Character read by the serial. 
  
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
