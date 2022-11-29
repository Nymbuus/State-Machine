#include "header.h"

// Deklarerar funktioner och variabler som bara syns i denna c fil.
static void blink(const volatile uint16_t* blink_speed_ms);
static void delay_ms(const volatile uint16_t* blink_speed_ms);

static led_state_t state = LED_STATE_OFF;
static uint16_t speed_ms = 0;

/************************************************************************************************
* fsm_reset: Resetar tillståndsmaskinen genom att släcka alla lampor och sätter delayen till 0ms.
************************************************************************************************/
void fsm_reset(void)
{
	state = LED_STATE_OFF;
	speed_ms = 0;
	LEDS_OFF;
}

/************************************************************************************************
* fsm_update: Kollar vilken state maskinen ligger i och byter till ett annat state beroende på viken 
*             knapp du trycker på.
************************************************************************************************/
void fsm_update(void)
{
	switch(state)
	{
		case LED_STATE_OFF:
		{
			if(NEXT_B_IS_PRESSED)
			{
				state = LED_STATE_SLOW;
			}
			else if (NEXT2_B_IS_PRESSED)
			{
				state = LED_STATE_MEDIUM;
			}
			else if (PREVIOUS_B_IS_PRESSED)
			{
				state = LED_STATE_ON;
			}
			else if (PREVIOUS2_B_IS_PRESSED)
			{
				state = LED_STATE_FAST;
			}
			
			break;
		}
		
		case LED_STATE_SLOW:
		{
			if(NEXT_B_IS_PRESSED)
			{
				state = LED_STATE_MEDIUM;
			}
			else if (NEXT2_B_IS_PRESSED)
			{
				state = LED_STATE_FAST;
			}
			else if (PREVIOUS_B_IS_PRESSED)
			{
				state = LED_STATE_OFF;
			}
			else if (PREVIOUS2_B_IS_PRESSED)
			{
				state = LED_STATE_ON;
			}
			
			break;
		}
		
		case LED_STATE_MEDIUM:
		{
			if(NEXT_B_IS_PRESSED)
			{
				state = LED_STATE_FAST;
			}
			else if (NEXT2_B_IS_PRESSED)
			{
				state = LED_STATE_ON;
			}
			else if (PREVIOUS_B_IS_PRESSED)
			{
				state = LED_STATE_SLOW;
			}
			else if (PREVIOUS2_B_IS_PRESSED)
			{
				state = LED_STATE_OFF;
			}
			
			break;
		}
		
		case LED_STATE_FAST:
		{
			if(NEXT_B_IS_PRESSED)
			{
				state = LED_STATE_ON;
			}
			else if (NEXT2_B_IS_PRESSED)
			{
				state = LED_STATE_OFF;
			}
			else if (PREVIOUS_B_IS_PRESSED)
			{
				state = LED_STATE_MEDIUM;
			}
			else if (PREVIOUS2_B_IS_PRESSED)
			{
				state = LED_STATE_SLOW;
			}
			
			break;
		}
		
		case LED_STATE_ON:
		{
			if(NEXT_B_IS_PRESSED)
			{
				state = LED_STATE_OFF;
			}
			else if (NEXT2_B_IS_PRESSED)
			{
				state = LED_STATE_SLOW;
			}
			else if (PREVIOUS_B_IS_PRESSED)
			{
				state = LED_STATE_FAST;
			}
			else if (PREVIOUS2_B_IS_PRESSED)
			{
				state = LED_STATE_MEDIUM;
			}
			
			break;
		}
		
		// Om något skiter sig så resetar programmet.
		default:
		{
			fsm_reset();
			break;
		}
	}
	
	// Uppdaterar blinkhastigheten som lagras som speed_ms.
	if (state == LED_STATE_OFF) { speed_ms = 0; LEDS_OFF; }
	else if (state == LED_STATE_SLOW) speed_ms = 500;
	else if (state == LED_STATE_MEDIUM) speed_ms = 250;
	else if (state == LED_STATE_FAST) speed_ms = 50;
	else if (state == LED_STATE_ON) { speed_ms = 0; LEDS_ON; }
	return;
}
/************************************************************************************************
* fsm_set_output: Utför instruktionerna som ges av state.
************************************************************************************************/
void fsm_set_output(void)
{
	LEDS_OFF;
	if (state == LED_STATE_SLOW) blink(&speed_ms);
	else if (state == LED_STATE_MEDIUM) blink(&speed_ms);
	else if (state == LED_STATE_FAST) blink(&speed_ms);
	else if (state == LED_STATE_ON) LEDS_ON;
	return;
}

/************************************************************************************************
* delay_ms: Fördröjningen mellan att lamporna tänds.
************************************************************************************************/
static void delay_ms(const volatile uint16_t* blink_speed_ms)
{
	for(int i = 0; i < *blink_speed_ms; i++)
	{
		_delay_ms(1);
	}
}

/************************************************************************************************
* blink: Dioderna blinkar i sekvens.
************************************************************************************************/
static void blink(const volatile uint16_t* blink_speed_ms)
{
	LED1_ON;
	delay_ms(blink_speed_ms);
	
	LED1_OFF;
	LED2_ON;
	delay_ms(blink_speed_ms);
	
	LED2_OFF;
	LED3_ON;
	delay_ms(blink_speed_ms);
	
	LED3_OFF;
}