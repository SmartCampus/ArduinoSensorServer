/**
 * Consult and send data of all sensors whose
 * refresh time as elapsed. 
 * Must be call periodically to refresh sensors at appropriate 
 * frequency. 
 */
void queryAllSensors()
{
  int sid = 0;
  while ((sid = getNextSensorToQuery(sid)) >= 0)
  {
    refreshSensorData(sid);
    updateNextSensorTime(sid);
  }
}


/**
 * Get sensor information and send its data by 
 * the help of its index.
 *
 * sid    : Sensor index.
 */ 
void refreshSensorData(int sid)
{
   /**
    * Check the sensor type and get its data back.
    */
   int type = getSensorType(sid);
   if (type == SONAR)
   {
     Ultrasonic * ultrasonic = (Ultrasonic*) sensorTab[sid].sensorSpecific;
     ultrasonic->MeasureInCentimeters();
     int value = (int) ultrasonic->RangeInCentimeters;
     printDataJson(getSensorName(sid), value, millis());
   }
   else
   {
     // Get the data from the analog port.
     float value = 0;
     value = analogRead(getSensorPinNumber(sid));
     
   // Print the data. JSON Format
   printDataJson(getSensorName(sid), value, millis());  
   }
}

/**
* Print sensor information (JSON Format)
*
* sensorName  : Sensor's name
* sensorValue : Sensor's value
* timestamp   : Time
*/
void printDataJson(char* sensorName, int sensorValue, unsigned long timestamp)
{
  // Data conversion
   char sensorValueChar[16];
   String value;
   value = String(sensorValue);
   value.toCharArray(sensorValueChar, 16);

   char timestampValueChar[32];
   String value2;
   value2 = String(timestamp);
   value2.toCharArray(timestampValueChar, 32);
   
   
   // Start JSON
   comm.send("D: {");
   // Display sensor's name
   comm.send("n:"); comm.send(sensorName);comm.send(",");
   // Display value
   comm.send("v:"); comm.send(sensorValueChar); comm.send(",");
   // Display timestamp
   comm.send("t:"); comm.send(timestampValueChar);
   // Close JSON
   comm.send("}"); 
   comm.send("\n");
   Serial.flush();
}

