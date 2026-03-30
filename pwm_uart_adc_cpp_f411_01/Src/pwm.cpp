/*
 * pwm.cpp
 *
 *  Created on: Feb 12, 2026
 *      Author: jm-liberty
 */

#include <stdint.h>
#include <iostream>
#include <uart.hpp>

#define GPIOAEN  (1U << 0)
#define TIMER2EN (1u << 0)

void pwm_init() {
	// Enable clock GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// PA0 in Alternate Function
	// Clear bits
	GPIOA->MODER &= ~(3U << 0);
	// AF mode
	GPIOA->MODER |=  (2U << 0);

	// Select AF1 (TIM2) to PA0
	GPIOA->AFR[0] &= ~(0xF << 0);
	GPIOA->AFR[0] |=  (1U << 0);
}

void pwm_timer_init() {
	// Enable clock TIMER2
    RCC->APB1ENR |= TIMER2EN;

    // Pres-caler: low frequency
    TIM2->PSC = 16 - 1;
    // Resolution PWM (0–1000)
    TIM2->ARR = 1000;

    // PWM mode 1 in channel 1
    // OC1M = 110 (PWM mode 1)
    TIM2->CCMR1 |= (6U << 4);
    // OC1PE pre-load enable
    TIM2->CCMR1 |= (1U << 3);

    // Enable output CH1 (channel 1)
    TIM2->CCER  |= (1U << 0);
    // Auto-reload pre-load enable
    TIM2->CR1   |= (1U << 7);

    // Duty init = 0
    TIM2->CCR1 = 0;

    // Turn on timer
    TIM2->CR1 |= (1U << 0);
}



