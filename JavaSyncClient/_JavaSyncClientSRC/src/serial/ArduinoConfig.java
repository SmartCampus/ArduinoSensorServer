
package serial;

import java.io.IOException;
import java.util.HashMap;

/**
 * Represents the Arduino old config. 
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class ArduinoConfig
{

/** The database of sensors */
private SensorRepository repository;

/** Arduino Interface */
private ArduinoInterface arduinoInterface;


/**
 * Default constructor.
 * 
 * @param ai ArduinInterface currently in use.
 */
public ArduinoConfig(ArduinoInterface ai)
{
   repository = new SensorRepository();
   arduinoInterface = ai;
}


/**
 * Add a new sensor to the sensors repository.
 * 
 * @param name      Sensor name to add.
 * @param pinNumber Pin where the Arduino is plugged.
 * @param frequency Sensor refresh data frequency.
 * 
 * @throws InterruptedException Thread interrupted.
 * @throws IOException          IO error.
 */
public void addSensor(String name, int pinNumber, int frequency)
throws IOException, InterruptedException
{
   // Build the string add command
   String command = "add " + name + pinNumber + frequency;
   arduinoInterface.execCommand(command);
   
   // Add the sensor to the repository. 
   repository.put(name, new SensorData(name, 0));
}


/**
 * Delete a sensor from the sensors repository.
 * 
 * @param name Name of the sensor to delete.
 * 
 * @throws ArduinoException The name is not in the map.
 */
public void delSensor(String name) 
throws ArduinoException
{
   // Get the current map of sensors.
   HashMap<String, SensorData> currentMap = repository.getSensorsMap();
   if (!(currentMap.containsKey(name)))
      throw new ArduinoException("This sensor " + name + " does not exist.");
   currentMap.remove(name);
}
}
