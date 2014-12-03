/*
	GroveDebug Library - Display information on a LCD Screen
*/

#include <Arduino.h>

#ifndef GroveDebug_h
#define GroveDebug_h

class GroveDebug
{
	public:
		GroveDebug();
		/* Print a debug message
		   Level (int): 0 (info), 1 (warning), 2 (error)
		   msg (char *): message
		*/
		void print(int level, char * msg);	
		void init();	
};

#endif