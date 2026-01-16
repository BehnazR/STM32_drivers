
#ifndef SOFT_TIMER_H_
#define SOFT_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include "systick.h"

typedef struct{
	uint32_t start_tick;
	uint32_t period;
	bool active;
	bool periodic;
}timer_t;

timer_t soft_timer_create(uint32_t delay_ms);
void soft_timer_start(timer_t* timer);
void soft_timer_stop(timer_t* timer);
bool soft_timer_expired(timer_t* timer);
bool soft_timer_running(timer_t* timer);

#endif /* SOFT_TIMER_H_ */
