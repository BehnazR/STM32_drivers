
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"
#include <stdint.h>

void systick_init_1ms(uint32_t sysclk_hz);
uint32_t systick_now(void);
uint32_t systick_elapsed(uint32_t start);
void systick_delay_ms(uint32_t ms);

#endif /* SYSTICK_H_ */
