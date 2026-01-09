#include "gpio_exti.h"

/* One callback per EXTI line */
static gpio_exti_cb_t exti_callbacks[16] = {0};

/* Helper: get EXTI IRQ number from pin */
static IRQn_Type exti_get_irq(uint8_t pin)
{
    if (pin <= 4)        return (IRQn_Type)(EXTI0_IRQn + pin);
    else if (pin <= 9)   return EXTI9_5_IRQn;
    else                 return EXTI15_10_IRQn;
}

/* Helper: get GPIO port index for SYSCFG */
static uint8_t gpio_port_to_exti(GPIO_TypeDef *port)
{
    if (port == GPIOA) return 0;
    if (port == GPIOB) return 1;
    if (port == GPIOC) return 2;
    if (port == GPIOD) return 3;
    if (port == GPIOE) return 4;
    if (port == GPIOH) return 7;
    return 0;
}

/* Initialize EXTI for a GPIO pin */
void gpio_exti_init(const gpio_exti_config_t *cfg)
{
	// Validate input
	if (!cfg || cfg->pin > 15 || cfg->callback == NULL)
	    return;

	uint8_t pin = cfg->pin;

	// Enable clock access to SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Map GPIO to EXTI line
	uint8_t idx = pin / 4;
	uint8_t shift = (pin % 4) * 4;

	SYSCFG->EXTICR[idx] &= ~(0xFU << shift);
	SYSCFG->EXTICR[idx] |= (gpio_port_to_exti(cfg->port) << shift);

	// Disable interrupt during configuration
	EXTI->IMR &= ~(1U << pin);

	// Configure trigger
	EXTI->RTSR &= ~(1U << pin);
	EXTI->FTSR &= ~(1U << pin);

	if (cfg->trigger == GPIO_EXTI_RISING)
	    EXTI->RTSR |= (1U << pin);
	else if (cfg->trigger == GPIO_EXTI_FALLING)
	    EXTI->FTSR |= (1U << pin);
	else
	{
	    EXTI->RTSR |= (1U << pin);
	    EXTI->FTSR |= (1U << pin);
	}

	// Register callback
	exti_callbacks[pin] = cfg->callback;

	// Clear pending flag
	EXTI->PR = (1U << pin);

	// Enable EXTI line in NVIC
	IRQn_Type irq = exti_get_irq(pin);
	NVIC_SetPriority(irq, cfg->irq_priority);
	NVIC_EnableIRQ(irq);
}

/* Enable EXTI interrupt */
void gpio_exti_enable(uint8_t pin)
{
	if(pin <= 15)
		EXTI->IMR |= (1U << pin);
}

/* Disable EXTI interrupt */
void gpio_exti_disable(uint8_t pin)
{
	if(pin <= 15)
		EXTI->IMR &= ~(1U << pin);
}

/* Clear pending EXTI flag */
void gpio_exti_clear(uint8_t pin)
{
	if(pin <= 15)
		EXTI->PR = (1U << pin);
}

void gpio_exti_irq_handler(uint8_t pin)
{
	if (pin > 15)
	    return;

	if(EXTI->PR & (1U << pin))
	{
		EXTI->PR = (1U << pin);   // clear pending
		if(exti_callbacks[pin])
			exti_callbacks[pin]();
	}
}
