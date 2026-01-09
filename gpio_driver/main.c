
#include "gpio.h"
#include "gpio_exti.h"

#define LED_PIN		5
#define BUTTON_PIN 13

static gpio_pin_config_t led = {
		.port = GPIOA,
		.pin = LED_PIN,
		.mode = GPIO_MODE_OUTPUT,
		.otype = GPIO_OTYPE_PP,
		.pupd = GPIO_NOPULL,
		.speed = GPIO_SPEED_HIGH,
		.alt_func = 0
};

static gpio_pin_config_t button = {
		.port = GPIOC,
		.pin = BUTTON_PIN,
		.mode = GPIO_MODE_INPUT,
		.otype = GPIO_OTYPE_PP,
		.pupd = GPIO_PULLUP,	// internal pull-up; PC13 also has external pull-up
		.speed = GPIO_SPEED_HIGH,
		.alt_func = 0
};

/* Callback function for button */
void button_cb (void)
{
	gpio_toggle(&led);
}

int main(void)
{
	/* LED and button example using GPIO driver with interrupt */

	gpio_init(&led);
	gpio_init(&button);

	gpio_exti_config_t btn_exti = {
			.port = GPIOC,
			.pin = BUTTON_PIN,
			.trigger = GPIO_EXTI_FALLING,
			.callback = button_cb,
			.irq_priority = 5
	};
	gpio_exti_init(&btn_exti);
	gpio_exti_enable(btn_exti.pin);

	while(1)
	{
	}
}
