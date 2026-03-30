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
void uart_write(int ch);

#endif /* UART_HPP_ */
