import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.Scanner;

/**
 * Read the data from a Serial.
 * 
 * @author Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class SerialInterface
{

/** The serial port */
private SerialPort port;

/** The port we are normally going to use. */
private String portName;

/** Port time out */
private static final int TIME_OUT = 2000;

/** Default bits per second for CMD port */
private static final int DATA_RATE = 9600;

/**
 *  Convert the bytes received by a InputStreamReader into
 *  characters and displayed them. 
 */
private BufferedReader input;

/** The output stream to the port */
private OutputStream output;


/**
 * Initialize the connection between the computer and the 
 * serial port. 
 * @param portN Serial port name.
 * 
 * @throws IOException 
 * @throws UnsupportedCommOperationException 
 * @throws PortInUseException 
 * @throws InterruptedException 
 * 
 */
public SerialInterface(String portN)
throws IOException, UnsupportedCommOperationException, PortInUseException, InterruptedException
{
   portName = portN;

   // Get all the availables ports on the computer. 
   CommPortIdentifier portId = null;
   Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

   // Find an instance of a serial port who is in PORT_NAME.
   while (portEnum.hasMoreElements())
   {
      CommPortIdentifier currentPortId = (CommPortIdentifier) portEnum.nextElement();
      if (currentPortId.getName().equals(portName))
      {
         portId = currentPortId;
         break;
      }
   }
   if (portId == null)
   {
      throw new IOException("Could not find port : " + portName);
   }

   // Open the serial. 
   port = (SerialPort) portId.open(this.getClass().getName(), TIME_OUT);

   // Set port parameters.
   port.setSerialPortParams(DATA_RATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

   // Open the streams.
   input = new BufferedReader(new InputStreamReader(port.getInputStream()));
   output = port.getOutputStream();

   // Wait for port to be available.
   Thread.sleep(2000);
}


/**
 * This method has to be call when you stop using the port.
 */
public synchronized void close()
{
   if (port != null)
   {
      port.close();
      port = null;
   }
}


/**
 * Send a message on the serial port.
 * 
 * @param toSend String to send.
 * @throws IOException 
 * @throws InterruptedException 
 */
public void send(String toSend)
throws IOException, InterruptedException
{
   System.out.println("Send : " + toSend);
   output.write(toSend.getBytes());
   output.flush();
   Thread.sleep(1500);
}


/**
 * Send a file line by line. 
 * 
 * @param filePath File path.
 * @throws IOException 
 * @throws InterruptedException 
 */
public void sendFile(String filePath)
throws IOException, InterruptedException
{
   Scanner scanner = new Scanner(new File(filePath));

   while (scanner.hasNextLine())
   {
      String line = scanner.nextLine();
      send(line);
      String rsp;
      while(!((rsp = receive()).startsWith("R")))
      {
         System.out.println("   Wait response : " + rsp);
      }
   }
   scanner.close();
}


/**
 * Receive a message frome the serial port.
 * 
 * @return The message received.
 * @throws InterruptedException 
 * @throws IOException 
 */
public String receive()
throws InterruptedException, IOException
{
   while (!input.ready())
   {
      Thread.sleep(100);
   }

   // Received line from serial.
   String inputLine = input.readLine();
   return inputLine;
}


/**
 * Test main.
 * 
 * @param args Program arguments.
 * @throws Exception
 */
public static void main(String[] args)
throws Exception
{
   final SerialInterface si = new SerialInterface("COM3");
  /* new Thread()
   {
      public void run()
      {
         while (true)
         {
            try
            {
               System.out.println(si.receive());
            }
            catch (InterruptedException e)
            {
               e.printStackTrace();
            }
            catch (IOException e)
            {
               e.printStackTrace();
            }
         }
      }
   }.start(); */

   si.sendFile("command1");
   while (true)
   {
     System.out.println(si.receive());
   }

}

}
