#include "header.h"
// Initierar systemet vid start och sedan k�rs tillst�ndsmaskinen kontunuerligt.
int main(void)
{
	setup();
	
    while (true) 
    {
		fsm_set_output();
    }
	
	return 0;
}

