/**
 ******************************************************************************
 * @file           : main.cpp
 * @author         : Jmiguel
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "adc.hpp"
#include "uart.hpp"

typedef uint32_t ui32;

void delay(volatile ui32 count)
{
    while (count--);
}

int main(void)
{
	// Initialize debug UART
	uart_init();

	int num_line = 0;

	while (true) {
		int num_temp = num_line;
		std::string msg = "Hello from STM32F411RE #0";

		for (const char& c : msg) {
			uart_write(c);
		}

		if (num_temp == 0) {
			uart_write('0');
		}
		else {
			std::string s =  std::to_string(num_temp);
			for (const char& c : s) {
				uart_write(c);
			}
		}

		// New line
		uart_write('\r');
		uart_write('\n');

		num_line++;

		delay(2000000);
	}
}
