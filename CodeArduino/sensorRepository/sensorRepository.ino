/** Maximum number of sensor on an Arduino platform */
#define MAX_SENSORS 10

/** Max token size */
#define TOKEN_SIZE 30

/** Board Id */
#define BOARD_ID "42"


/**
 * Descriptor of a sensor.
 */
typedef struct 
{
    char name[TOKEN_SIZE];         // Sensor name.
    int pin;                       // Arduino pin where the sensor is plugged.
    int refreshDataFrequency;      // Refresh data frequency.
    unsigned long nextUpdateTime;  // Next update time of the sensor.
    int isEnabled;                 // Sensor status (0=disabled, 1=enabled)
    boolean isUsed;                // Descriptor used (true = used).
}
SENSOR_DESCRIPTOR;


/** Tab of sensors */
SENSOR_DESCRIPTOR sensorTab[MAX_SENSORS];


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
int addSensor(char* name, int pinNumber, int frequency, boolean isOutput)
{
  // Check if name is already used.
  if (getSensorByName(name) >= 0)
    return -2; 
    
  // Check pin number.
  if ((pinNumber < 0) || (pinNumber >= MAX_SENSORS))
    return -3;
    
  // Check if pin number already used.
  if (getSensorByPinNumber(pinNumber) >= 0)
    return -4;
    
  // Search for a free place in sensor tab.
  int i = getFreeSensorId();
  if (i < 0)
    return -1;
    
  // Fill new sensor descriptor.
  strncpy(sensorTab[i].name, name, TOKEN_SIZE);
  sensorTab[i].pin = pinNumber;
  sensorTab[i].refreshDataFrequency = frequency * 1000;
  sensorTab[i].nextUpdateTime = millis();
  sensorTab[i].isUsed = true;
  //Serial.print("Add a new sensor:"); Serial.print(i); Serial.print(" name: '"); Serial.print(sensorTab[i].name); Serial.println("'");
  return i;
}


/**
 * Get a free sensor id.
 *
 * return : Index of a free sensor ID, -1 if none.
 */
int getFreeSensorId()
{
  int i;
  for (i = 0; i < MAX_SENSORS; i++)
  {
    if (!(sensorTab[i].isUsed))
      return i;  
  }
  return -1;
}

/**
 * Delete a sensor from an array of sensors. 
 *
 * sid    : Sensor index in sensor tab.
 *
 * return : true if successful, false if not.
 */
boolean deleteById(int sid)
{
  if (!isSensorExists(sid))
    return false;
  sensorTab[sid].isUsed = false;
  return true;  
}


/**
 * Delete a sensor from an array of sensors and shut it. 
 *
 * sensoreName : Name of the sensor to delete.
 * return      : true if successful, false if not.
 */
boolean deleteByName(char* sensorName)
{
  return deleteById(getSensorByName(sensorName));
}


/**
 * Get sensor name from its index.
 *
 * sid    : Sensor index.
 * 
 * return : Sensor name.
 */
char* getSensorName(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return "";
   
  return sensorTab[sid].name;
}


/**
 * Get sensor pin number from its index.
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
  
  return sensorTab[sid].pin;
}


/**
 * Get sensor frequency from its index.
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
    
  return sensorTab[sid].refreshDataFrequency;
}


/**
 * Get sensor next update time from its index.
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
    
  return sensorTab[sid].nextUpdateTime;
}


/**
 * Get a sensor index from its name.
 *
 * sensorName : Name of the sensor. 
 *
 * return : Sensor index in sensor tab, -1 if sensor not found.
 */
int getSensorByName (char* sensorName) 
{   
  // Search for a sensor who have the same name as sensorName. 
  int i;
  for (i = 0 ; i < MAX_SENSORS; i++)
  {
    if (sensorTab[i].isUsed && (strcmp(sensorName, sensorTab[i].name) == 0))
      return i;
  }
  
  // Nothing find.
  return -1;
}


/**
 * Get a sensor index from its pin number.
 *
 * pNum : Sensor pin number.
 *
 * return : Sensor index in sensor tab, -1 if sensor not found.
 */
int getSensorByPinNumber (int pNum) 
{   
  // Search for a sensor who have the same name as sensorName. 
  int i;
  for (i = 0 ; i < MAX_SENSORS; i++)
  {
    if (sensorTab[i].isUsed && (pNum == sensorTab[i].pin))
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
    if ((sensorTab[i].isUsed) && (sensorTab[i].nextUpdateTime <= time) && (sensorTab[i].isEnabled == 1))
      return i;
  }
  
  return -1;
}


/**
 * Get the next available sensor.
 *
 * firstId : Start sensor Id.
 *
 * return  : Id of the next available sensor, -1 if none.
 */ 
int getNextAvailableSensor(int firstId)
{
  if (firstId < 0) 
    firstId = 0;
    
  // Get the next available sensor.
  for ( ; firstId < MAX_SENSORS; firstId++)
  {
    if (sensorTab[firstId].isUsed)
      return firstId;
  }
  
  // No more sensors available.
  return -1;
}



/**
 * Change the refresh data frequency of a sensor.
 *
 * sid          : Sensor ID.
 * newFrequency : New sensor refresh rate frequency.
 */ 
boolean changeDataFrequencyById(int sid, int newFrequency)
{
  // Check if sensor exists. 
  if (!(isSensorExists(sid)))
    return false;
  sensorTab[sid].refreshDataFrequency = newFrequency * 1000;
  return true;
  
}


/**
 * Change the refresh data frequency of a sensor.
 *
 * sid          : Sensor ID.
 * newFrequency : New sensor refresh rate frequency.
 */ 
boolean changeDataFrequencyByName(char* sname, int newFrequency)
{
  return changeDataFrequencyById(getSensorByName(sname), newFrequency);
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
  return ((sid < MAX_SENSORS) && (sid >= 0) && (sensorTab[sid].isUsed));
}


/**
 * Clear the sensor table. 
 */
void clearTable()
{
  int i;
  for (i = 0; i < MAX_SENSORS; i++)
  {
    sensorTab[i].isUsed = false;
  }
}


/**
 * Change the sensor status.
 *
 * sname     : Sensor name.
 * newStatus : Sensor new status.
 *
 * return    : true if good execution, false otherwise.
 */
boolean changeSensorStatus(char* sname, int newStatus)
{
  // Check is sensor exists
  int sid = getSensorByName(sname);
  if (sid < 0)
    return false;
    
  // Update sensor status
  sensorTab[sid].isEnabled = newStatus;
  return true;
}


/**
 * Update the next update time of the sensor.
 */
boolean updateNextSensorTime(int sid)
{
  // Check if sensor exists.
  if (!(isSensorExists(sid)))
    return false;
 
  // Build the new sensor refresh frequency.
  sensorTab[sid].nextUpdateTime = millis() + sensorTab[sid].refreshDataFrequency;
  return true;
}
