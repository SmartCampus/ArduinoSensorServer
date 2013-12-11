
package serial;

import java.net.UnknownHostException;

/**
 * Main class of program execution.
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class Main
{

/**
 * Program main.
 * 
 * @param args       Program argument.
 * @throws Exception Creation error.
 */
public static void main(String[] args)
throws Exception
{
   // Prepare to get Arduino datas and Arduino informations.
   final InformationReceiver ir = new InformationReceiver();
   final DataReceiver dr = new DataReceiver();
   final String portName = args[0];

   // Create a new Arduino interface (redefine the abstract methods).
   ArduinoInterface ai = new ArduinoInterface(args[0])
   {
      public void sensorDataReceived(String data)
      {
         dr.writeData(data, "dataReceived.txt");
         try
         {
            SensorData sd = new SensorData(data, portName);
         }
         catch (UnknownHostException e)
         {
            e.printStackTrace();
         }
      }
      
      public void infoReceived(String data)
      {
         // Log the received informations. 
         ir.informationToLog(data);
      }
   };

   // Testing add command.
   System.out.println("Send file command.");
   ai.execFileCommand("command1");
   ai.execCommand("add temperature2 3 4");
   System.out.println("File command executed.");
}

}
