#include "GroveDebug.h"
#include <rgb_lcd.h>
#include <Wire.h>
/* Global objects */
rgb_lcd lcd;


Debug::Debug()
{
}
void Debug::init()
{
		lcd.begin(16, 2);
    	lcd.print("SmartCampusOS");

}
void Debug::print(int level, char * msg)
{
	switch(level)
	{
		case 0: {
			lcd.setRGB(255, 255, 255);
			break;
		}
		case 1 : {
			lcd.setRGB(255, 255, 0);
			break;
		}
		case 2 : {
			lcd.setRGB(255, 0, 0);
			break;
		}
		default : {
			lcd.setRGB(255, 255, 255);
		}
	}
	lcd.clear(); // Clear message
	lcd.home(); // Set cursor to top left corner
	lcd.print(msg);
}