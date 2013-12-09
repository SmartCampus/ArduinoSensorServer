
package serial;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/**
 * Print Arduino informations into a log file. 
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class InformationReceiver
{

/** Class logger */
private static final Logger logger = Logger.getLogger("serial.InformationReceiver");

/** File handler */
private Handler fh;


/**
 * Default constructor.
 * 
 * @throws IOException       IO error.
 * @throws SecurityException Security error.
 */
public InformationReceiver()
{
   try
   {
      fh = new FileHandler("informationLog.log", false);
      fh.setFormatter(new SimpleFormatter());
      logger.addHandler(fh);
   }
   catch (SecurityException | IOException e)
   {
      logger.throwing("InformationReceiver.class", "InformationReceiver()", e);
   }
}


/**
 * Log an Anrduino information into the log journal. 
 * 
 * @param information Information to log.
 */
public void informationToLog(String information)
{
   logger.log(Level.INFO, information);
}
}
