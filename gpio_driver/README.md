# STM32 Bare-Metal GPIO & EXTI Driver

## Overview


This project implements a bare-metal GPIO and EXTI (external interrupt) driver for STM32F4 microcontrollers, written directly at the register level using CMSIS definitions (no HAL, no LL).

The goal of this project is to demonstrate low-level firmware design, interrupt handling, and clean driver architecture.

---

## Features


### GPIO Driver

- GPIO clock enable (AHB1)

- Pin configuration:

  - Mode: Input / Output / Alternate / Analog

  - Output type: Push-pull / Open-drain

  - Output speed configuration

  - Pull-up / Pull-down configuration

  - Alternate function selection (AFR)

- GPIO operations:

  - Read pin state (IDR)

  - Atomic write using BSRR

  - Atomic toggle

### EXTI Driver

- GPIO-to-EXTI line mapping via SYSCFG

- Interrupt trigger configuration:

  - Rising edge

  - Falling edge

  - Both edges

- NVIC configuration (IRQ selection & priority)

- Shared IRQ handling for EXTI0–4, EXTI5–9, EXTI10–15

- Callback-based interrupt dispatch

- Proper write-1-to-clear EXTI pending handling

---

## Design Notes

- GPIO and EXTI functionality are implemented as **separate driver modules**
- Interrupt service routines are kept minimal and delegate logic to the driver
- Callback-based EXTI handling avoids application logic inside ISRs
- Atomic GPIO operations prevent read-modify-write issues

---

## File Structure
```
├── drivers/
│ ├── gpio.h
│ ├── gpio.c
│ ├── gpio_exti.h
│ └── gpio_exti.c
│
├── stm32f4xx_it.c # Interrupt service routines
├── main.c # Application example
├── startup_stm32f4xx.s
└── README.md
```
---

## Target Hardware

- **MCU:** STM32F4 series (e.g., STM32F401, STM32F411, STM32F446)
- **Toolchain:** ARM GCC
- **Headers:** CMSIS (`stm32f4xx.h`)

---

## Testing

Tested on real hardware using:

- GPIO output toggle verification via LED

- EXTI interrupt generation using a user button

- Verified correct trigger behavior and interrupt dispatch

---

## License

This project is licensed under the MIT License.