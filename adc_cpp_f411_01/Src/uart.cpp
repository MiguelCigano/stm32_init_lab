/*
 * uart.cpp
 *
 *  Created on: Feb 2, 2026
 *      Author: jm-liberty
 */

#include <stdint.h>
#include <uart.hpp>

#define GPIOAEN 			(1U <<  0)
#define UART2EN				(1U << 17)

#define DBG_UART_BAUDRATE	115200
#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ
#define CR1_TE				(1U <<  3)
#define CR1_UE				(1U << 13)
#define SR_TXE				(1U <<  7)

typedef uint32_t ui32;
typedef uint16_t ui16;

static void uart_set_baudrate(ui32 periph_clk, ui32 baudrate);
void uart_write(int ch);

int __io_putchar(int ch) {
	uart_write(ch);
	return ch;
}

void uart_init() {
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	///
	// RCC->APB1ENR |= UART2EN;
	// volatile int tmp = RCC->AHB1ENR; // delay dummy read

	// Set the mode of PA2 to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |=	 (1U << 5);

	// Set alternate function type to AF7 (UART2_TX)
	GPIOA->AFR[0] |=  (1U <<  8);
	GPIOA->AFR[0] |=  (1U <<  9);
	GPIOA->AFR[0] |=  (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	// PA3 as Alternate Function (USART2_RX) ///
	// GPIOA->MODER &= ~(1U << 6);
	// GPIOA->MODER |=  (1U << 7);

	// GPIOA->AFR[0] |=  (1U << 12);
	// GPIOA->AFR[0] |=  (1U << 13);
	// GPIOA->AFR[0] |=  (1U << 14);
	// GPIOA->AFR[0] &= ~(1U << 15);


	// Set output type to push-pull ///
	// GPIOA->OTYPER &= ~(1U << 2);

	// Set very high speed ///
	// GPIOA->OSPEEDR |= (1U << 4);
	// GPIOA->OSPEEDR |= (1U << 5);

	// No pull-up / pull-down ///
	// GPIOA->PUPDR &= ~(1U << 4);
	// GPIOA->PUPDR &= ~(1U << 5);


	// Enable clock access to UART2
	RCC->APB1ENR |=	UART2EN;

	// Configure uart_baudrate
	uart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);

	// Configure transfer direction
	USART2->CR1 = CR1_TE;

	// Enable UART Module
	USART2->CR1 |= CR1_UE;
}

void uart_write(int ch) {
	// Make sure transmit data register is empty
	while (!(USART2->SR & SR_TXE)) {
		// TODO
	}

	// Write to transmit data register
	USART2->DR = (ch & 0xFF);
}

static ui16 compute_uart_bd(ui32 periph_clk, ui32 baudrate) {
	return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void uart_set_baudrate(ui32 periph_clk, ui32 baudrate) {
	USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}

