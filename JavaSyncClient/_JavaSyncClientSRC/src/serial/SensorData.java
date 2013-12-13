
package serial;

import java.net.UnknownHostException;
import java.util.StringTokenizer;

/**
 * Model the sensor data and informations, like name, time and sensor value. 
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class SensorData
{

/** Sensor name in the following format : <PC_NAME>.<PORT_NAME>.<SENSOR_NAME> */
private String sensorName;

/** Sensor value */
private float sensorValue;

/** Time where the info is received */
private long sensorTime;


/**
 * Default constrctor.
 * Construct a sensor with a String content.
 * 
 * @param sdata        Sensor data value received from the Arduino.
 * 
 * @throws UnknownHostException Address error.
 */
public SensorData(String sdata)
throws UnknownHostException
{
   // Build the object from the String.
   StringTokenizer tkz = new StringTokenizer(sdata, ": ");
   while (tkz.hasMoreElements())
   {
      // Build sensor name.
      if (tkz.nextToken().equals("n"))
         sensorName = tkz.nextToken();

      // Build sensor value.
      if (tkz.nextToken().equals("v"))
         sensorValue = Float.parseFloat(tkz.nextToken());
   }
   sensorTime = System.currentTimeMillis();
}


/**
 * Second constructor.
 * Create a SensorData by the help of real values.
 * 
 * @param name  Sensor name.
 * @param value Sensor current value.
 */
public SensorData(String name, float value)
{
   sensorName = name;
   sensorValue = value;
   sensorTime = System.currentTimeMillis();
}


/**
 * Get the sensor name.
 * 
 * @return Sensor name.
 */
public String getSensorName()
{
   return sensorName;
}


/**
 * Get the sensor value.
 * 
 * @return Sensor value.
 */
public float getValue()
{
   return sensorValue;
}


/**
 * Get the sensor update date.
 * 
 * @return Sensor update date.
 */
public long getTime()
{
   return sensorTime;
}


/**
 * Convert an object to its String representation.
 * 
 * @return The String representation of an object.
 */
public String toString()
{
   return "name: " + sensorName + " value: " + sensorValue + " date: " + sensorTime;
}

/**
 * Program test main.
 * 
 * @param args Main program arguments.
 * @throws UnknownHostException 
 */
/*public static void main(String[] args)
throws UnknownHostException
{
   SensorData sd = new SensorData("n: temperature2 v: 479.00", "COM3");
   System.out.println(sd);
}*/
}
