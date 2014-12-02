/*
	DEBUG Library - Display information on a LCD Screen
*/

#include <Arduino.h>

#ifndef Debug_h
#define Debug_h

class Debug
{
	public:
		Debug();
		/* Print a debug message
		   Level (int): 0 (info), 1 (warning), 2 (error)
		   msg (char *): message
		*/
		void print(int level, char * msg);	
		void init();	
};

#endif