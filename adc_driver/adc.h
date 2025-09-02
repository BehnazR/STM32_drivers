/**
 * @file    adc.h
 * @brief   Bare-metal ADC driver for ADC1 on STM32F446 microcontroller
 * @author  Behnaz Rezvani
 * @version 1.0
 * @date    August 2025
 *
 * @details This header provides an interface for initializing and using
 *          ADC1 in single or continuous conversion mode.
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f4xx.h"

/* ---------------------------- User Config Types ---------------------------- */

/**
 * @brief ADC Prescaler values (PCLK2 division factor)
 */
typedef enum {
    ADC_PRESCALER_2 = 0,
    ADC_PRESCALER_4 = 1,
    ADC_PRESCALER_6 = 2,
    ADC_PRESCALER_8 = 3
} ADC_Prescaler_t;

/**
 * @brief ADC sampling times (per channel)
 * Each corresponds to ADC cycles: 3, 15, 28, 56, 84, 112, 144, 480
 */
typedef enum {
    ADC_SMP_3CYCLES   = 0,
    ADC_SMP_15CYCLES  = 1,
    ADC_SMP_28CYCLES  = 2,
    ADC_SMP_56CYCLES  = 3,
    ADC_SMP_84CYCLES  = 4,
    ADC_SMP_112CYCLES = 5,
    ADC_SMP_144CYCLES = 6,
    ADC_SMP_480CYCLES = 7
} ADC_SamplingTime_t;
/* -------------------------------------------------------------------------- */

void adc_init(GPIO_TypeDef *port, uint8_t pin, uint8_t channel,
              ADC_SamplingTime_t sampling_time, ADC_Prescaler_t prescaler);
void adc_start(uint8_t continuous);
uint16_t adc_read(void);

#endif /* ADC_H_ */
