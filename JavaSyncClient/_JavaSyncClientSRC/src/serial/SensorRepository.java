package serial;

import java.util.HashMap;

/**
 * Store all sensors to build the Arduino configuration.
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class SensorRepository
{

/** Map who store all the sensors */
private HashMap<String, SensorData> sensorsStore = new HashMap<String, SensorData>();


/**
 * Put a sensor with its key in the map.
 * 
 * @param key   Sensor name.
 * @param value Sensor data.
 */
public void put(String key, SensorData value)
{
   sensorsStore.put(key, value);
}


/**
 * Get a sensor from its key.
 * 
 * @param key Sensor key (sensor name).
 * @return    The sensor associated to the key.
 */
public SensorData get(String key)
{
   return sensorsStore.get(key);
}


/**
 * Remove a sensor with its key.
 * 
 * @param key Sensor key.
 */
public void remove(String key)
{
   sensorsStore.remove(key);
}


/**
 * Get the current HashMap.
 * 
 * @return The current HashMap.
 */
public HashMap<String, SensorData> getSensorsMap()
{
   return sensorsStore;
}

}
