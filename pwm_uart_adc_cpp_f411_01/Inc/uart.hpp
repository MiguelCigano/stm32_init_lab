/*
 * uart.hpp
 *
 *  Created on: Feb 2, 2026
 *      Author: jm-liberty
 */

#ifndef UART_HPP_
#define UART_HPP_

#include "stm32f4xx.h"

void uart_init(void);
void uart_write_nbyte(int ch);
void uart_write_string(const char* s);

void uart_write(const char* data, size_t len);
template<size_t N>
void uart_write(const char (&array_)[N]) {
	uart_write((array_), N-1);
}

#endif /* UART_HPP_ */
