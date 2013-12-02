void setup()
{
  Serial.begin(9600);
  clearTable(); // Clear sensors table. 
  Serial.println("Tab cleared.");
  
  // Method add test.
  int sensor = addSensor("temperature1", 1, 3, true); 
  Serial.print("Sensor created : "); 
  Serial.println(sensor);
  
 // execCommand("add temperature2 2 5"); // Add a sensor name temperature2, on the pin number 2, with a refresh rate of 5 seconds. 
}

void loop()
{  
  String content = "";
  char character;
  while (Serial.available() > 0)
  {
    character = Serial.read();
    content.concat(character);
  }
  
  Serial.println(execCommand(content));
  
  queryAllSensors();
  delay(1000);
}
