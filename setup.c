#include "header.h"

// Deklarerar funktioner som bara syns i denna c fil.
static inline void init_ports(void);
static inline void init_interupts(void);

/************************************************************************************************
* setup: Kallar på initieringsfunktioner för portar och avbrytsfunktioner.
************************************************************************************************/
void setup(void)
{
	init_ports();
	init_interupts();
}

/************************************************************************************************
* init_ports: Initierar portar för leds och knappar.
************************************************************************************************/
static void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
	PORTB = (1 << PREVIOUS_B) | (1 << NEXT_B) | (1 << NEXT2_B);
	PORTD = (1 << RESET_B) | (1 << PREVIOUS2_B);
}

/************************************************************************************************
* init_interupts: Initierar register för avbrytsfunktioner.
************************************************************************************************/
static void init_interupts(void)
{
	asm("SEI");
	PCICR = (1 << PCIE0);
	PCMSK0 = (1 << PREVIOUS_B) | (1 << NEXT_B) | (1 << NEXT2_B);
	
	EICRA = (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	EIMSK = (1 << INT0) | (1 << INT1);
}