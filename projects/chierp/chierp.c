#include "ch32v003fun.h"
#include <stdio.h>

/* 
 * chieeeeeeeeeeeeeeeeeeeeeeeeeerp
 */

int main()
{
	SystemInit();

	uint8_t value = 1;
	uint8_t delay;

	// Enable GPIO
	RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;

	// Configure PD4 as push pull
	GPIOD->CFGLR &= ~(0xf << (4*4));
	GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << (4*4);

	// Configure PD6 as push pull
	GPIOD->CFGLR &= ~(0xf << (4*6));
	GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << (4*6);

	while (1) {

#if 1
		GPIOD->BSHR = (value<<4) | (!value<<6) |
			(!value<<(16+4)) | (value<<(16+6));
		Delay_Ms(delay++);
		value = !value;
#else
		// toggle gpio
		GPIOD->BSHR = (value<<4) | (!value<<6);
		Delay_Ms(100);

#endif
	}
}
