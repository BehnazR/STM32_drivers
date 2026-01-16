#include "systick.h"

#define GPIOAEN				(1U<<0)
#define LED_PIN				5

#define SYS_CORE_CLK		16000000
#define DELAY_MS			1000

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(3U << (2 * LED_PIN));
	GPIOA->MODER |=  (1U << (2 * LED_PIN));

	systick_init_1ms(SYS_CORE_CLK);
	uint32_t start = systick_now();

	while(1)
	{
		if (systick_elapsed(start) > DELAY_MS)
		{
			GPIOA->ODR ^= (1U << LED_PIN);
			start = systick_now();
		}
	}
}
