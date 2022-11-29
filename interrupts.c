#include "header.h"

// Port 2 p� register D resetar programmet.
ISR(INT0_vect)
{
	fsm_reset();
}

// Port 3 p� register D uppdaterar programmet med och �ndrar tillst�ndet.
ISR(INT1_vect)
{
	fsm_update();
}

// Resten av alla knaparna uppdaterar programmet och �ndrar tillst�ndet.
ISR(PCINT0_vect)
{
	if (PREVIOUS_B_IS_PRESSED || NEXT_B_IS_PRESSED || NEXT2_B_IS_PRESSED)
	{
		fsm_update();
	}
}