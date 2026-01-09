
#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"
#include <stdint.h>

/* GPIO pin modes */
typedef enum{
	GPIO_MODE_INPUT  = 0x0,
	GPIO_MODE_OUTPUT = 0x1,
	GPIO_MODE_ALT    = 0x2,
	GPIO_MODE_ANALOG = 0x3
} gpio_mode_t;

/* Output Type */
typedef enum{
	GPIO_OTYPE_PP = 0x0,	// Push-pull
	GPIO_OTYPE_OD = 0x1		// Open-drain
} gpio_otype_t;

/* Output speed */
typedef enum{
	GPIO_SPEED_LOW  	= 0x0,
	GPIO_SPEED_MEDIUM 	= 0x1,
	GPIO_SPEED_FAST    	= 0x2,
	GPIO_SPEED_HIGH 	= 0x3
} gpio_ospeed_t;

/* Pull-up/Pull-down */
typedef enum {
    GPIO_NOPULL 	= 0x00,
    GPIO_PULLUP 	= 0x01,
    GPIO_PULLDOWN 	= 0x02
} gpio_pupd_t;

/* Pin configuration structure */
typedef struct {
    GPIO_TypeDef *port;
    uint8_t pin;
    gpio_mode_t mode;
    gpio_otype_t otype;
    gpio_ospeed_t speed;
    gpio_pupd_t pupd;
    uint8_t alt_func;  // If using alternate function
} gpio_pin_config_t;

typedef enum {
	GPIO_HIGH = 0x1,
	GPIO_LOW  = 0x0
} gpio_write_t;

/* API */
void gpio_init(gpio_pin_config_t* cfg);
uint8_t gpio_read(gpio_pin_config_t* cfg);
void gpio_write(gpio_pin_config_t* cfg, gpio_write_t state);
void gpio_toggle(gpio_pin_config_t* cfg);

#endif /* GPIO_H_ */
