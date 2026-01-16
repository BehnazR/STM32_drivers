# SysTick & Software Timer Driver (Bare-Metal)

A lightweight, deterministic timing framework for ARM Cortex-M microcontrollers based on the SysTick peripheral.  
This repository provides both a **1-millisecond hardware time base** and a **software timer layer** built on top of it for application-level timing needs such as debouncing, timeouts, and periodic events.

---

## Overview

This driver consists of two tightly integrated layers:

### 1. SysTick Time Base  
The SysTick driver configures the ARM Cortex-M SysTick peripheral to generate an interrupt every **1 millisecond**.  
Each interrupt increments a global millisecond counter that acts as a **monotonic system clock**.

This provides:
- A precise millisecond time base
- Low CPU overhead
- No dependency on RTOS

### 2. Software Timers  
The software timer layer builds on the SysTick time base and provides:
- One-shot timers
- Periodic timers
- Non-blocking timeouts
- Event timing (e.g. button debouncing)

Each software timer stores:
- The tick at which it started
- A timeout duration (ms)
- Active and periodic state

---

### Typical Use Cases

This driver is designed for real-time embedded applications, including:

- Button debouncing  
- LED blinking  
- Communication timeouts  
- Sensor sampling intervals  
- State machine timing  
- Power-saving delays  

All without blocking the CPU or requiring an RTOS.

---

## Hardware Requirements

- MCU: **STM32F446** (or any Cortex-M4 with SysTick)  
- SysTick clock source: **HCLK (CPU clock)**  

SysTick is configured to generate an interrupt every **1 millisecond**.

---

## Initialization

Each timer must be initialized before use:

```c
timer_t debounce;
soft_timer_init(&debounce, 50);   // 50 ms debounce timer
```

SysTick itself must be initialized once at system startup:

```c
systick_init_1ms(SystemCoreClock);
```

You must pass the **CPU clock frequency (HCLK)** in Hz.

The driver validates that the SysTick reload value fits in the 24-bit SysTick counter.  
If the configuration is invalid, the firmware enters a safe fail-stop state.

---
## Architecture

The timing stack is layered as follows:

```
Application (buttons, LEDs, UART)
        │
Software Timers (soft_timer.c)
        │
SysTick Driver (systick.c)
        │
ARM Cortex-M SysTick hardware
```

The SysTick driver owns the hardware.  
The software timer layer consumes time but does **not** control the SysTick peripheral.

---

## Example: Button Debouncing

```c
timer_t debounce;

void EXTI15_10_IRQHandler(void)
{
    if (!soft_timer_running(&debounce))
    {
        soft_timer_start(&debounce);
    }
}

int main(void)
{
    systick_init_1ms(SystemCoreClock);
    soft_timer_init(&debounce, 50);   // 50 ms debounce

    while (1)
    {
        if (soft_timer_expired(&debounce))
        {
            handle_button_press();
        }
    }
}
```

---

## License
This project is licensed under the MIT License.


