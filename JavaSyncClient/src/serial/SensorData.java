
package serial;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
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
private String sensorTime;


/**
 * Default constrctor.
 * 
 * @param informations Sensor informations.
 * @param currentPort  Current serial port.
 * 
 * @throws UnknownHostException Address error.
 */
public SensorData(String informations, String currentPort)
throws UnknownHostException
{
   // Build the object from the String.
   StringTokenizer tkz = new StringTokenizer(informations, ": ");
   while (tkz.hasMoreElements())
   {
      // Build sensor name.
      if (tkz.nextToken().equals("n"))
         sensorName = InetAddress.getLocalHost().getHostName() + "." + currentPort + "." + tkz.nextToken();

      // Build sensor value.
      if (tkz.nextToken().equals("v"))
         sensorValue = Float.parseFloat(tkz.nextToken());
      break;
   }
   sensorTime = getActualDate();
}


/**
 * Get actual date of the system.
 * 
 * @return The acutal date of the system.
 */
public String getActualDate()
{
   // Build date to the format "yyyy-MM-dd".
   Date actualDate = new Date();
   DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
   return df.format(actualDate);

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
public float getSensorValue()
{
   return sensorValue;
}


/**
 * Get the sensor update date.
 * 
 * @return Sensor update date.
 */
public String getSensorDate()
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
   return "Sensor name: " + sensorName + " value: " + sensorValue + " date: " + sensorTime;
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
