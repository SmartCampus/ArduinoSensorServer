/*
	Debug Library - Display information on a LCD Screen
*/

#include <Arduino.h>

#ifndef EBDebug_h
#define EBDebug_h

class EBDebug
{
	public:
		EBDebug();
		/* Print a Debug message
		   Level (int): 0 (info), 1 (warning), 2 (error)
		   msg (char *): message
		*/
		void print(int level, char * msg);	
		void init();	
};

#endif