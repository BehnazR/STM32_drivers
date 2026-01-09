
#ifndef GPIO_EXTI_H_
#define GPIO_EXTI_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stddef.h>

/* EXTI trigger selection */
typedef enum {
    GPIO_EXTI_RISING,
    GPIO_EXTI_FALLING,
    GPIO_EXTI_BOTH
} gpio_exti_trigger_t;

/* EXTI callback type */
typedef void (*gpio_exti_cb_t)(void);

/* EXTI configuration structure */
typedef struct {
    GPIO_TypeDef *port;
    uint8_t pin;
    gpio_exti_trigger_t trigger;
    uint8_t irq_priority;      // NVIC priority
    gpio_exti_cb_t callback;   // User ISR callback
} gpio_exti_config_t;

/* API */
void gpio_exti_init(const gpio_exti_config_t *cfg);
void gpio_exti_enable(uint8_t pin);
void gpio_exti_disable(uint8_t pin);
void gpio_exti_clear(uint8_t pin);

void gpio_exti_irq_handler(uint8_t pin);

#endif /* GPIO_EXTI_H_ */
