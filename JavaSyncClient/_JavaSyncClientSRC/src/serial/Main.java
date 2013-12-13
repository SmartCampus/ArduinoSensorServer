
package serial;

import java.io.File;

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
   // Create root directory of all micro controller datas.
   File rootDir = new File("ControllerDatas");
   
   // Create micro controller objects data required in this environnement.
   String portName = args[0];
   MicroController mc1 = new MicroController(portName, new File(rootDir, "PORT_" + portName), false);
   
   // Test of sensor creation.
   mc1.getConfig().addSensor("t1", 2, 3);
   mc1.getConfig().addSensor("t2", 3, 4);
}
}
