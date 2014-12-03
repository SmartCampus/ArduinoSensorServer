#include "EBDebug.h"
#include <LiquidCrystal.h>

/* Global objects */
LiquidCrystal lcdEB(2, 3, 4, 5, 6, 7, 8);

EBDebug::EBDebug()
{
}
void EBDebug::init()
{
		lcdEB.begin(16,2);
		lcdEB.clear();
  		lcdEB.print("SmartCampusOS");

}
void EBDebug::print(int level, char * msg)
{
	lcdEB.clear(); // Clear message
	lcdEB.setCursor(0, 0);
	switch(level)
	{
		
		case 0: {
			lcdEB.print("INFO");
			break;
		}
		case 1 : {
			lcdEB.print("WARNING");
			break;
		}
		case 2 : {
			lcdEB.print("ERROR");
			break;
		}
		default : {
			lcdEB.print("INFO");
		}
	}
	lcdEB.setCursor(0, 1);
	lcdEB.print(msg);
	delay(500);
}