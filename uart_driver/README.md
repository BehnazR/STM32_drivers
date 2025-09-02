# STM32F446 USART2 Driver (Bare-Metal)

## Overview

This is a bare-metal UART driver written in C for the STM32F446 microcontroller.
It directly configures the USART2 peripheral using register-level access,
without using HAL or any vendor libraries.

- TX: PA2 (AF7)
- RX: PA3 (AF7)
- Peripheral: USART2
- Clock: 16 MHz internal clock (assumed default)

## Features

- Register-level initialization of USART2
- Blocking character send and receive
- No external dependencies

## File Structure

```
stm32-uart-driver/
├── uart.c # Driver implementation
├── uart.h # Driver interface
├── main.c # Example usage
├── README.md # This file
└── LICENSE # MIT License
```


## Usage

1. Include `uart.c` and `uart.h` in your STM32 project.
2. Call `usart2_init(baudrate);` during initialization.
3. Use `usart2_write()` to send characters.

## Requirements

- STM32F446 microcontroller (or compatible STM32F4 variant)
- 16 MHz system clock
- USART2 peripheral routed to PA2/PA3

## License

This project is licensed under the MIT License. See the LICENSE file for details.
