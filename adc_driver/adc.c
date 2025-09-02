#include "adc.h"

/* ------------------------------------ Macros---------------------------------------- */

// RCC AHB1 (for GPIOs) and APB2 (for ADC1) peripheral enable bits
#define GPIOAEN				(1U<<0)
#define GPIOBEN				(1U<<1)
#define GPIOCEN				(1U<<2)
#define GPIODEN				(1U<<3)
#define GPIOEEN				(1U<<4)
#define GPIOFEN				(1U<<5)
#define ADC1EN				(1U<<8)

// Default configuration
#define ADC_SEQ_LEN_1		(0x00)

// ADC control register and status register bit masks
#define CR2_ADON			(1U<<0)
#define CR2_CONT			(1U<<1)
#define CR2_SWSTART			(1U<<30)
#define SR_EOC				(1U<<1)

/* ---------------------------- Public API Implementation ---------------------------- */

/**
 * @brief  Initializes ADC1 on a given GPIO pin/channel.
 * @param  port: GPIO port (e.g., GPIOA)
 * @param  pin: Pin number (0-15)
 * @param  channel: ADC channel number (0–18 depending on STM32F446)
 * @param  sampling_time: One of ADC_SamplingTime_t
 * @param  prescaler: One of ADC_Prescaler_t
 */
void adc_init(GPIO_TypeDef *port, uint8_t pin, uint8_t channel,
              ADC_SamplingTime_t sampling_time, ADC_Prescaler_t prescaler)
{
	/*** Configure ADC GPIO pin ***/

	// Enable clock access to GPIOx
	if(port == GPIOA) RCC->AHB1ENR |= GPIOAEN;
	else if(port == GPIOB) RCC->AHB1ENR |= GPIOBEN;
	else if(port == GPIOC) RCC->AHB1ENR |= GPIOCEN;
	else if(port == GPIOD) RCC->AHB1ENR |= GPIODEN;
	else if(port == GPIOE) RCC->AHB1ENR |= GPIOEEN;
	else if(port == GPIOF) RCC->AHB1ENR |= GPIOFEN;


	// Set pin mode to analog mode (11)
	port->MODER |= (3U<<(2*pin));

	/*** Configure ADC module ***/

	// Enable clock access to ADC1
	RCC->APB2ENR |= ADC1EN;

	// Set ADC prescaler (common config register)
	ADC->CCR &= ~(3U << 16); // clear the old prescaler
	ADC->CCR |= ((prescaler & 0x3) << 16);

	// Set sampling time for selected channel
	if(channel <= 9)
	{
		ADC1->SMPR2 &= ~(7U << (channel*3)); // clears the old sampling time
		ADC1->SMPR2 |= ((sampling_time & 0x7) << (channel*3));
	}
	else
	{
		uint8_t ch = channel - 10;
		ADC1->SMPR1 &= ~(7U << (ch*3));
		ADC1->SMPR1 |= ((sampling_time & 0x7) << (ch*3));
	}

	// Conversion sequence start
	ADC1->SQR3 = channel;

	// Conversion sequence length = 1
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	// Enable ADC module
	ADC1->CR2 |= CR2_ADON;
}

/**
 * @brief  Starts the conversion process.
 * @param  continuous: 0 = single conversion, 1 = continuous mode
 */
void adc_start(uint8_t continuous)
{

	if(continuous)
		ADC1->CR2 |= CR2_CONT;
	else
		ADC1->CR2 &= ~CR2_CONT;

	ADC1->CR2 |= CR2_SWSTART;
}

/**
 * @brief  Reads the conversion result (blocking).
 * @retval 12-bit converted analog value
 */
uint16_t adc_read(void)
{
	// Wait for the conversion to finish
	while(!(ADC1->SR & SR_EOC)) {}

	// Read conversion result
	uint16_t result = ADC1->DR;

	// EOC clears automatically after read, but force a dummy read for safety
	(void)ADC1->SR;

	return result;
}
