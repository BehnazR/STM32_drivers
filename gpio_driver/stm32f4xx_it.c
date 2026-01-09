#include "gpio_exti.h"


void EXTI0_IRQHandler(void)       { gpio_exti_irq_handler(0); }
void EXTI1_IRQHandler(void)       { gpio_exti_irq_handler(1); }
void EXTI2_IRQHandler(void)       { gpio_exti_irq_handler(2); }
void EXTI3_IRQHandler(void)       { gpio_exti_irq_handler(3); }
void EXTI4_IRQHandler(void)       { gpio_exti_irq_handler(4); }

void EXTI9_5_IRQHandler(void)
{
    for (uint8_t i = 5; i <= 9; i++)
    	gpio_exti_irq_handler(i);
}

void EXTI15_10_IRQHandler(void)
{
    for (uint8_t i = 10; i <= 15; i++)
    	gpio_exti_irq_handler(i);
}
