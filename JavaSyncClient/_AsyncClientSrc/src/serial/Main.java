
package serial;

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

   // Create a new Arduino interface (redefine the abstract methods).
   ArduinoInterface ai = new ArduinoInterface(args[0])
   {

      public void sensorDataReceived(String data)
      {
         dr.writeData(data, "dataReceived.json");
      }


      public void infoReceived(String data)
      {
         // Log the received informations. 
         ir.informationToLog(data);
      }
   };

   // Testing add command.
   System.out.println("Send add command.");
   ai.execCommand("add temperature2 3 4");
   System.out.println("Add command executed.");
}

}
