#include "EBDebug.h"
#include <LiquidCrystal.h>

/* Global objects */
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

Debug::Debug()
{
}
void Debug::init()
{
		lcd.begin(16,2);
		lcd.clear();
  		lcd.print("SmartCampusOS");

}
void Debug::print(int level, char * msg)
{
	lcd.clear(); // Clear message
	lcd.setCursor(0, 0);
	switch(level)
	{
		
		case 0: {
			lcd.print("INFO");
			break;
		}
		case 1 : {
			lcd.print("WARNING");
			break;
		}
		case 2 : {
			lcd.print("ERROR");
			break;
		}
		default : {
			lcd.print("INFO");
		}
	}
	lcd.setCursor(0, 1);
	lcd.print(msg);
	delay(500);
}