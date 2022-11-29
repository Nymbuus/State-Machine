#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definerar vilka portar lamporna ska ligga p�.
#define LED1 0
#define LED2 1
#define LED3 2

// Definerar vilka pins knapparna ska ligga p�.
#define PREVIOUS_B 3
#define NEXT_B 4
#define NEXT2_B 5
#define RESET_B 2
#define PREVIOUS2_B 3

// Makron f�r att t�nda lamporna indiviuellt p� register B.
#define LED1_ON PORTB |= (1 << LED1)
#define LED2_ON PORTB |= (1 << LED2)
#define LED3_ON PORTB |= (1 << LED3)

// Makron f�r att sl�cka lamporna indiviuellt p� register B.
#define LED1_OFF PORTB &= ~(1 << LED1)
#define LED2_OFF PORTB &= ~(1 << LED2)
#define LED3_OFF PORTB &= ~(1 << LED3)

// Makron f�r att t�nda och sl�cka lamporna kollektivt p� register B.
#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3))

// Makron f�r att kolla om knapparna �r nedtryckta.
#define PREVIOUS_B_IS_PRESSED (PINB & (1 << PREVIOUS_B))
#define NEXT_B_IS_PRESSED (PINB & (1 << NEXT_B))
#define NEXT2_B_IS_PRESSED (PINB & (1 << NEXT2_B))
#define PREVIOUS2_B_IS_PRESSED (PIND & (1 << PREVIOUS2_B))

// Skapat datatypen bool som inneh�ller true och false.
typedef enum { false, true }bool;

// Skapat datatypen led_state_t som inneh�ller alla olika tillst�nd till tillst�ndsmaskinen.
typedef enum
{
	LED_STATE_OFF,
	LED_STATE_SLOW,
	LED_STATE_MEDIUM,
	LED_STATE_FAST,
	LED_STATE_ON
} led_state_t;

// Deklarerat funktioner.
void setup(void);
void fsm_reset(void);
void fsm_update(void);
void fsm_set_output(void);

#endif /* HEADER_H_ */