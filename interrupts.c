#include "header.h"

// Port 2 på register D resetar programmet.
ISR(INT0_vect)
{
	fsm_reset();
}

// Port 3 på register D uppdaterar programmet med och ändrar tillståndet.
ISR(INT1_vect)
{
	fsm_update();
}

// Resten av alla knaparna uppdaterar programmet och ändrar tillståndet.
ISR(PCINT0_vect)
{
	if (PREVIOUS_B_IS_PRESSED || NEXT_B_IS_PRESSED || NEXT2_B_IS_PRESSED)
	{
		fsm_update();
	}
}