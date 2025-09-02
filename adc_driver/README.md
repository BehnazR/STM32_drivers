# STM32F446 ADC1 Driver (Bare-Metal)

## Overview

This is a bare-metal ADC1 driver written in C for STM32F446 microcontroller (tested on Nucleo-F446RE).  
It supports single and continuous conversion modes, configurable prescaler and sampling time.

## Features

- Register-level implementation (no HAL/LL)
- Configurable:
  - ADC channel (0–18 depending on MCU)
  - Sampling time (3 to 480 cycles)
  - ADC prescaler (2, 4, 6, 8)
- Single or continuous conversion
- Blocking read function

## File Structure

```
stm32-adc-driver/
├── adc.c # Driver implementation
├── adc.h # Driver interface
├── main.c # Example usage
├── README.md # This file
└── LICENSE # MIT License
```

## Usage

1. Include `adc.c` and `adc.h` in your STM32 project.
2. Call `adc_init()` during initialization.
3. Strat conversion by calling `adc_start()`.
4. Use `adc_read()` to get the converted result.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
