
package serial;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

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
      // Open the streams.
      FileWriter fw = new FileWriter(fileName, true);
      BufferedWriter bw = new BufferedWriter(fw);
      PrintWriter pw = new PrintWriter(bw);

      // Write datas in the file.
      pw.println(data);
      pw.close();
   }
   catch (IOException e)
   {
      e.printStackTrace();
   }
}



}
