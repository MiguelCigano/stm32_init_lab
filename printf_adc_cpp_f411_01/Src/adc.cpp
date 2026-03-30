/*
 * adc.cpp
 *
 *  Created on: February 2, 2026
 *      Author: jm-liberty
 */


#include "adc.hpp"

#define GPIOAEN  	  	(1U << 0)
#define ADC1EN	      	(1U << 8)

#define CR2_ADCON		(1U << 0)
#define CR2_CONT		(1U << 1)
#define CR2_SWSTART     (1U << 30)

#define SR_EOC			(1U << 1)

typedef uint32_t ui32;

void pal_adc_init() {
	// Configure the ADC GPIO pin
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA1 mode like analog mode
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	// Configure the ADC Module
	// Enable clock access to the ADC module (ADC Clock)
	RCC->APB2ENR |= ADC1EN;

	// Sampling time channel 1 (PA1)
	// Max sample time for stability
	ADC1->SMPR2 |= (7U << 3);

	// Set conversion sequence length
	ADC1->SQR1 = 0;

	// Set conversion sequence start
	ADC1->SQR3 = 1;

	// Enable ADC module
	ADC1->CR2 |= CR2_ADCON;

	for (volatile int i = 0; i < 1000; i++);
}

void start_conversation() {
	// Enable continuos conversion
	ADC1->CR2 |= CR2_CONT;

	// Start ADC conversion
	ADC1->CR2 |= CR2_SWSTART;
}

ui32 adc_read() {
	// Wait for conversion to be complete
	while (!(ADC1->SR & SR_EOC)) {
		// TODO
	}

	// Read converted value
	return (ADC1->DR);
}





