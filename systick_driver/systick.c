#include "systick.h"

#define CTRL_ENABLE				(1U<<0)
#define CTRL_TICKINT			(1U<<1)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)

#define SYSTICK_MAX_RELOAD   	0xFFFFFFUL

volatile uint32_t ms_tick = 0;

/* Initialize SysTick for 1 ms interrupts */
void systick_init_1ms(uint32_t sysclk_hz)
{
	uint32_t reload = (sysclk_hz / 1000UL) - 1;
	if(reload > SYSTICK_MAX_RELOAD)
	{
		while(1); // Configuration error
	}

	// disable first
	SysTick->CTRL = 0;

	// Reload with number of clocks per ms
	SysTick->LOAD = reload;

	// Clear SysTick current value register
	SysTick->VAL = 0;

	// Select internal CLK (HCLK) and enable SysTick and its interrupt
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE | CTRL_TICKINT;
}

uint32_t systick_now(void)
{
	uint32_t tick;

	__disable_irq();
	tick = ms_tick;
	__enable_irq();

	return tick;
}

uint32_t systick_elapsed(uint32_t start)
{
	return (ms_tick - start);
}

void systick_delay_ms(uint32_t ms)
{
    uint32_t start = systick_now();
    while ((systick_now() - start) < ms)
    {
        __WFI();   // Sleep until next interrupt
    }
}

void SysTick_Handler(void)
{
	ms_tick++;
}


