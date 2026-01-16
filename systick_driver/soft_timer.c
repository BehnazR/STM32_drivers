#include "soft_timer.h"

void soft_timer_init(timer_t* timer, uint32_t period_ms)
{
	timer->start_tick = 0;
	timer->period = period_ms;
	timer->active = false;
	timer->periodic = false;
}

void soft_timer_start(timer_t* timer)
{
	__disable_irq();
	timer->start_tick = systick_now();
	timer->active = true;
	timer->periodic = false;
	__enable_irq();
}

void soft_timer_start_periodic(timer_t* timer)
{
	__disable_irq();
	timer->start_tick = systick_now();
	timer->active = true;
	timer->periodic = true;
	__enable_irq();
}

void soft_timer_stop(timer_t* timer)
{
	__disable_irq();
	timer->active = false;
	__enable_irq();
}

bool soft_timer_expired(timer_t* timer)
{
	if(!timer->active) return false;

	if(systick_elapsed(timer->start_tick) >= timer->period)
	{
		__disable_irq();
		if(timer->periodic)
			timer->start_tick = systick_now();
		else
			timer->active = false;
		__enable_irq();

		return true;
	}
	return false;
}

bool soft_timer_running(timer_t* timer)
{
	return timer->active;
}




