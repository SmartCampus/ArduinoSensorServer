/** Maximum number of sensor on an Arduino platform */
#define MAX_SENSORS 20  

/**
 * Define the comportement of a sensor.
 */ 
class Sensor 
{
  public :
    String name;                   // Sensor name.
    int pin;                       // Arduino pin where the sensor is plugged.
    int refreshDataFrequency;      // Refresh data frequency.
    unsigned long nextUpdateTime;  // Next update time of the sensor.
   
    /**
     * Normal constructor.
     */  
    public : Sensor(int dataF, int p, String n, boolean isOut)
    {
      refreshDataFrequency = dataF * 1000;
      pin = p;
      name = n;
      //pinMode(pin, isOut);
      nextUpdateTime = millis();
    }  
};

/** Tab of sensors */
Sensor * sensorTab[MAX_SENSORS];

/** Number of elements in sensorTab */
int sensorNb = 0;


/**
 * Add a sensor to an array of sensors.
 *
 * name      : Sensor name.
 * pin       : Arduino pin where the sensor is plugged
 * frequency : Sensor data refresh frequency (in seconds).
 * isOutput  : Sensor mode (OUTPUT if true, INPUT if false).
 *
 * return    : Sensor index int sensor tab or -1 if sensor tab is full, -2 if name is already in use, -3 if pin is overwhelm, -4 if pin is already in use.
 */
int addSensor(String name, int pinNumber, int frequency, boolean isOutput)
{
  int i = 0;
  
  // Check if existing.
  if (getSensorByName(name) >= 0)
    return -2; 
  else if (pinNumber > MAX_SENSORS)
    return -3;
    
  // Search for a free place in sensor tab.
  for (i; i < MAX_SENSORS; i++)
  {
    if (sensorTab[i]->pin == pinNumber)
      return -4;
    if (sensorTab[i] == NULL)
    {
      sensorTab[i] = new Sensor(frequency, pinNumber, name, isOutput);
      return i;
    }
  }
  return -1;
}


/**
 * Delete a sensor from an array of sensors and shut it. 
 *
 * sid    : Sensor index in sensor tab.
 *
 * return : true if successful, false if not.
 */
boolean deleteById(int sid)
{
  if (!isSensorExists(sid)) 
    return false;
  sensorTab[sid] = NULL;
  return true;  
}


/**
 * Delete a sensor from an array of sensors and shut it. 
 *
 * sensoreName : Name of the sensor to delete.
 * return      : true if successful, false if not.
 */
boolean deleteByName(String sensorName)
{
  return deleteById(getSensorByName(sensorName));
}


/**
 * Get sensor name by the help of its index.
 *
 * sid    : Sensor index.
 * 
 * return : Sensor name.
 */
String getSensorName(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return NULL;
   
  return sensorTab[sid]->name;
}


/**
 * Get sensor pin number by the help of its index.
 *
 * sid    : Sensor index.
 * 
 * return : Sensor pin number.
 */
int getSensorPinNumber(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return -1;
  
  return sensorTab[sid]->pin;
}


/**
 * Get sensor frequency by the help of its index.
 *
 * sid    : Sensor index. 
 * 
 * return : Sensor frequency.
 */
int getSensorFrequency(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return -1;
    
  return sensorTab[sid]->refreshDataFrequency;
}


/**
 * Get sensor next update time by the help of its index.
 *
 * sid    : Sensor index.
 *
 * return : Sensor next update time. 
 */
unsigned long getNextUpdateTime(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return -1;
    
  return sensorTab[sid]->nextUpdateTime;
}


/**
 * Get a sensor index from its name.
 *
 * sensorName : Sensor index in sensor tab.
 */
int getSensorByName (String sensorName) 
{
  // Check parameters.
  if (sensorName == NULL) 
    return -1;
   
  // Search for a sensor who have the same name as sensorName. 
  int i;
  for (i = 0 ; i < MAX_SENSORS; i++)
  {
    if (sensorTab[i] == NULL)
      continue;
    if (sensorName.equals(sensorTab[i]->name))
      return i;
  }
  
  // Nothing find.
  return -1;
}


/**
 * Search in the array the next sensor which its hour 
 * overwhelm the nextUpdateTime. 
 *
 * return : The next sensor. 
 */
int getNextSensorToQuery()
{
  unsigned long time = millis();
  int i; 
  for (i = 0; i < MAX_SENSORS; i++)
  {
    if ((sensorTab[i] != NULL) && (sensorTab[i]->nextUpdateTime <= time))
      return i;
  }
  
  return -1;
}


/**
 * Change the refresh data frequency of a sensor.
 *
 * sid          : Sensor ID.
 * newFrequency : New sensor refresh rate frequency.
 */ 
boolean changeDataFrequency(int sid, int newFrequency)
{
  // Check if sensor exists. 
  if (!(isSensorExists(sid)))
    return false;
  sensorTab[sid]->refreshDataFrequency = newFrequency * 1000;
  return true;
  
}


/**
 * Check if a sensor ID corresponds to an existing sensor.
 *
 * sid    : Sensor ID.
 *
 * return : true if ID corresponds to an existing sensor.
 */
boolean isSensorExists(int sid)
{
  return ((sid < MAX_SENSORS) && (sid >= 0) && (sensorTab[sid] != NULL));
}


/**
 * Clear the sensor table. 
 */
void clearTable()
{
  int i;
  for (i = 0; i < MAX_SENSORS; i++)
  {
    sensorTab[i] = NULL;
  }
}


/**
 * Update the next update time of the sensor.
 */
boolean updateNextSensorTime(int sid)
{
  /*Serial.print("Update time for sid : "); 
  Serial.println(sid);*/
  if (!(isSensorExists(sid)))
    return false;
  
 /* Serial.print("Update data."); 
  Serial.println(sensorTab[sid]->refreshDataFrequency);*/
  sensorTab[sid]->nextUpdateTime = millis() + sensorTab[sid]->refreshDataFrequency;
  
 /* Serial.print("Next refresh time : ");
  Serial.println(sensorTab[sid]->nextUpdateTime);*/
  return true;
}








