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
   // Get the data from the analog port.
   float value = 0;
   value = analogRead(getSensorPinNumber(sid));
   // delay(100);
   
   // Print the data. JSON Format
   printDataJson(getSensorName(sid), value, millis());  
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
   // Start JSON
   Serial.print("D: {");
   // Display sensor's name
   Serial.print("n:"); Serial.print(sensorName); Serial.print(",");
   // Display value
   Serial.print("v:"); Serial.print(sensorValue); Serial.print(",");
   // Display timestamp
   Serial.print("t:"); Serial.print(timestamp);
   // Close JSON
   Serial.print("}"); 
   Serial.print("\n");
   Serial.flush();
}


