
package serial;

import java.io.File;

/**
 * This class represents a micro-controller.
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class MicroController
{

/** Sensors history */
private SensorHistory history;

/** Sensors data */
private LastSensorDataRepository repository;

/** Arduino configuration */
private MicroControllerConfig config;

/** Arduino interface */
private ArduinoInterface arduinoInterface;


/**
 * Default constructor. 
 * 
 * @param portName   Port name.
 * @param rdir       Micro controller data root directory.
 * @param configMode Launch the previous Arduino configuration.
 * 
 * @throws Exception Error.
 */
public MicroController(String portName, File rdir, boolean configMode)
throws Exception
{
   // Create the micro controller root directory. 
   rdir.mkdirs();

   // Create the sensors data repository.
   repository = new LastSensorDataRepository();

   // Create the sensors data history.
   history = new SensorHistory(new File(rdir, "History"));

   // Create the Arduino interface.
   arduinoInterface = new ArduinoInterface(portName)
   {

      public void sensorDataReceived(String data)
      {
         try
         {
            SensorData sd = new SensorData(data);

            // Add data to repository.
            repository.addData(sd);

            // Add data to history.
            history.addData(sd);
         }
         catch (Exception e)
         {
            e.printStackTrace();
         }
      }
      public void infoReceived(String data)
      {
         // Log the received informations. 
         // TODO 
      }
   };

   // Create the micro controller configuration.
   config = new MicroControllerConfig(arduinoInterface, new File(rdir, "MicroControllerConfig"), configMode);
}


/**
 * Get the micro controller configuration.
 * 
 * @return The micro controller configuration.
 */
public MicroControllerConfig getConfig()
{
   return config;
}


/**
 * Get the micro controller sensor repository. 
 * 
 * @return The micro controller sensor repository.
 */
public LastSensorDataRepository getRepository()
{
   return repository;
}


/**
 * Get the arduino interface.
 * 
 * @return The arduino interface.
 */
public ArduinoInterface getInterface()
{
   return arduinoInterface;
}


/**
 * Get the micro controller sensor history.
 * 
 * @return The micro controller sensor history.
 */
public SensorHistory getHistory()
{
   return history;
}
}
