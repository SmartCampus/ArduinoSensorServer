
package serial;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Received sensors datas from the Arduino board and print them into a logfile. 
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class DataReceiver
{

/**
 * Write Arduino datas into a file.
 * 
 * @param data     Data to write.
 * @param fileName File where the datas are write.
 */
public void writeData(String data, String fileName)
{
   try
   {
      FileWriter fw = new FileWriter(fileName, true);
      BufferedWriter bw = new BufferedWriter(fw);
      PrintWriter pw = new PrintWriter(bw);

      pw.println(data + " : " + getActualDate());
      pw.close();
   }
   catch (IOException e)
   {
      e.printStackTrace();
   }
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
}
