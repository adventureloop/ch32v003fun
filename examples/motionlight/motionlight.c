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
 */

int main()
{
	SystemInit();

	// Enable GPIOs
	funGpioInitAll();
	
	funPinMode( PD0, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PD4, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PD6, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PC0, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );

	while(1)
	{
		funDigitalWrite( PD0, FUN_HIGH );
		funDigitalWrite( PD4, FUN_HIGH );
		funDigitalWrite( PD6, FUN_HIGH );
		funDigitalWrite( PC0, FUN_HIGH );
		Delay_Ms( 250 );
		funDigitalWrite( PD0, FUN_LOW );
		funDigitalWrite( PD4, FUN_LOW );
		funDigitalWrite( PD6, FUN_LOW );
		funDigitalWrite( PC0, FUN_LOW );
		Delay_Ms( 250 );
	}
}
