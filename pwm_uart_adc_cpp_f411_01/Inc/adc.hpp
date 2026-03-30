/*
 * adc.hpp
 *
 *  Created on: Feb 2, 2026
 *      Author: jm-liberty
 */

#ifndef ADC_HPP_
#define ADC_HPP_

#include <stdint.h>
#include "stm32f4xx.h"

typedef uint32_t ui32;

void pal_adc_init(void);
void start_conversation(void);
ui32 adc_read(void);

#endif /* ADC_HPP_ */
