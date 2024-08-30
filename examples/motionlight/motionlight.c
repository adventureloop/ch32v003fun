#include "ch32v003fun.h"
#include <stdio.h>

/* 
 * Motion light for the entrance and hall way. 
 *
 * Needs to be able to sleep, be woken by interrupts from the pir and/or a
 * radar person detector and maybe an ultrasound module and pwm to control
 * brightness of some attached leds.
 *
 * Needs to be attached to a ldr and maybe a pot to control an ambient lighting
 * switch.
 *
 * Ideally idle and active power consumption will be so low as to be difficult
 * to measure.
 *
 * First steps:
 * 	[?] get debugging to work
 * 	[x] blink an led
 * 	[ ] pwm an led
 * 	[ ] rolling pwm an led with a timer interrupt
 * 	[ ] read analog
 * 	[ ] take a pin interupt
 * 	[ ] sleep
 *	[ ] clock down uc
 */

uint8_t last = 0;
uint32_t count;

void handle_debug_input(int n, uint8_t *data)
{
	count += n;
	last = data[0];
}

int main()
{
	SystemInit();

	int value = 1;

	// Enable GPIOD and TIM2
	RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM2;

#if 1
	// Reset TIM2 to init state
	RCC->APB2PRSTR |= RCC_APB2Periph_TIM2;	
	RCC->APB2PRSTR &= ~RCC_APB2Periph_TIM2;	

	TIM2->PSC = 0x0000;
	TIM2->ATRLR = 255;
	TIM2->SWEVGR |= TIM_UG;			// init counter
	TIM2->CCER |= TIM_CC1E | (TIM_CC1P & 0xFF);

	
	// PD4 is CH1 on timer 2

#endif
	// Configure PD4 as push pull
	GPIOD->CFGLR &= ~(0xf << (4*4));
	GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << (4*4);

	// Configure PD6 as push pull
	GPIOD->CFGLR &= ~(0xf << (4*6));
	GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << (4*6);

	while (1) {
		printf("+%u\n", count++);

		// Turn gpio off, I don't understand this
		//GPIOD->BSHR = (value<<(16+4)) | (!value<<(16+6));
		GPIOD->BSHR = (!value<<(16+6));

		Delay_Ms(100);
		
		for (int i = 0; i < 10000; i++)
			poll_input();

		printf("-%u[%c]\n", count++, last);

		// Turn gpio on
		//GPIOD->BSHR = (value<<4) | (!value<<6);
		GPIOD->BSHR = (!value<<6);
		value = !value;

		Delay_Ms(100);
	}
}
