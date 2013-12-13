
package serial;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * This class manage the history of sensor values for all sensors of one Arduino. 
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class SensorHistory
{

/** Root directory of the sensors history */
private File rootDirectory;


/**
 * Default constructor.
 * 
 * @param dir Directory where are stored history files.
 * @throws IOException 
 */
public SensorHistory(File dir)
throws IOException
{
   rootDirectory = dir;
   if (!(rootDirectory.mkdirs()))
   {
      if (!rootDirectory.exists())
         throw new IOException("Unable to create the history directory : " + rootDirectory.getCanonicalPath());
   }
}


/**
 * Add a new sensor data to the history.
 * 
 * @param sd Sensor data to add to the history.
 * 
 * @throws IOException IO error.
 */
public void addData(SensorData sd)
throws IOException
{
   // Find the file corresponding to this sensor. 
   File f = new File(rootDirectory, sd.getSensorName());
   if (!(f.exists()))
      f.createNewFile();

   // Append sensors data at the end of the file.
   PrintWriter pw;
   pw = new PrintWriter(new FileWriter(f, true));
   try
   {
      pw.println(sd);
   }
   finally
   {
      pw.close();
   }
}
}
