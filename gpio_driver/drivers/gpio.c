#include "gpio.h"

/* Enable GPIO clock */
static void gpio_enable_clock(GPIO_TypeDef *port)
{
    if (port == GPIOA) RCC->AHB1ENR |= (1 << 0);
    else if (port == GPIOB) RCC->AHB1ENR |= (1 << 1);
    else if (port == GPIOC) RCC->AHB1ENR |= (1 << 2);
    else if (port == GPIOD) RCC->AHB1ENR |= (1 << 3);
    else if (port == GPIOE) RCC->AHB1ENR |= (1 << 4);
    else if (port == GPIOH) RCC->AHB1ENR |= (1 << 7);
}

void gpio_init(gpio_pin_config_t* cfg)
{
	gpio_enable_clock(cfg->port);

	uint8_t pin = cfg->pin;

	// Mode
	cfg->port->MODER &= ~(0x3U << 2*pin);
	cfg->port->MODER |= ((cfg->mode & 0x3U) << 2*pin);

	// Output-only
	if (cfg->mode == GPIO_MODE_OUTPUT || cfg->mode == GPIO_MODE_ALT)
	{
		// Output type
		cfg->port->OTYPER &= ~(0x1U << pin);
		cfg->port->OTYPER |= ((cfg->otype & 0x1U) << pin);

		// Speed
		cfg->port->OSPEEDR &= ~(0x3U << 2*pin);
		cfg->port->OSPEEDR |= ((cfg->speed & 0x3U) << 2*pin);
	}

	// Pull-up/Pull-down
	cfg->port->PUPDR &= ~(0x3U << 2*pin);
	cfg->port->PUPDR |= ((cfg->pupd & 0x3U) << 2*pin);

	// Alternate function (if needed)
	if (cfg->mode == GPIO_MODE_ALT)
	{
		uint8_t afr_idx = 0;
		uint8_t afr_pos = pin;
		if(pin > 7)
		{
			afr_idx = 1;
			afr_pos = pin - 8;
		}
		cfg->port->AFR[afr_idx] &= ~(0xFU << 4*afr_pos);
		cfg->port->AFR[afr_idx] |= ((cfg->alt_func & 0xFU) << 4*afr_pos);
	}
}

uint8_t gpio_read(gpio_pin_config_t* cfg)
{
	return ((cfg->port->IDR >> cfg->pin) & 0x1U);
}

void gpio_write(gpio_pin_config_t* cfg, gpio_write_t state)
{
	if(state == GPIO_HIGH)
	{
		cfg->port->BSRR = (0x1U << cfg->pin);
	}
	else
	{
		cfg->port->BSRR = (0x1U << (cfg->pin + 16));
	}
}

void gpio_toggle(gpio_pin_config_t* cfg)
{
	if (cfg->port->ODR & (1U << cfg->pin))
	    cfg->port->BSRR = (1U << (cfg->pin + 16));
	else
	    cfg->port->BSRR = (1U << cfg->pin);
}
