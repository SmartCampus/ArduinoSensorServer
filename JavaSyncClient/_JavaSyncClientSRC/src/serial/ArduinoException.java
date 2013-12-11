
package serial;

/**
 * Arduino exceptions manager.
 * 
 * @author  Jean Oudot - IUT Nice / Sophia Antipolis - S4D
 * @version 1.0.0
 */
public class ArduinoException
extends Exception
{

/**
 * Default constructor.
 * 
 * @param message Exception message.
 */
public ArduinoException(String message)
{
   super(message);
}
}
