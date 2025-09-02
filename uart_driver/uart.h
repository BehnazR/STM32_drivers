/**
 * @file    uart.h
 * @brief   Bare-metal UART driver for USART2 on STM32F446 microcontroller
 * @author  Behnaz Rezvani
 * @version 1.0
 * @date    July 2025
 *
 * @details This header provides an interface for initializing USART2 and
 *          performing blocking UART transmission and reception.
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void usart2_init(int baudrate);
void usart2_write(char ch);
char usart2_read(void);

#endif /* UART_H_ */
