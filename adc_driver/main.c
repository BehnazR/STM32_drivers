
#include <stdio.h>
#include "adc.h"

uint32_t sensor;

int main(void)
{

	// Initialize ADC1 on PA1 (pin 1, channel 1), 15-cycle sample time, prescaler /2
	adc_init(GPIOA, 1, 1, ADC_SMP_15CYCLES, ADC_PRESCALER_2);


	while(1)
	{
		adc_start(0); // Single conversion
		sensor = adc_read();

		// use value (0–4095 for 12-bit ADC)
	}
}
