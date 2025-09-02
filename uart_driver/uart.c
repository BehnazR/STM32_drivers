#include "uart.h"

/* ---------------------------- Macros & Definitions ---------------------------- */

// RCC AHB1 and APB1 peripheral enable bits
#define GPIOAEN				(1U<<0)
#define USARTEN				(1U<<17)	// USART2

// USART CR1 bit masks
#define RC1_TE				(1U<<3)		// Transmitter enable
#define RC1_RE				(1U<<2)		// Receiver enable
#define RC1_UE				(1U<<13)	// UART enable

// USART SR (status register) flags
#define RS_TXE				(1U<<7)		//  Transmit data register empty
#define RS_RXNE				(1U<<5)		//  Receive data register not empty

// Clock assumptions
#define SYS_CLK				16000000	// System clock frequency (16 MHz)
#define APB1_CLK			SYS_CLK		// APB1 bus clock

/* ---------------------------- Static Helper Function ---------------------------- */

/**
 * @brief Sets baud rate register for a given USART.
 * @note  This is an internal helper. Not exposed in header.
 */
static void usart_set_baudrate(USART_TypeDef *UARTTX, uint32_t PeriphClk, uint32_t BaudRate)
{
	UARTTX->BRR = ((PeriphClk + BaudRate/2U)/BaudRate);
}

/* ---------------------------- Public API Implementation ---------------------------- */

/**
 * @brief  Initializes USART2 peripheral for TX and RX (PA2 and PA3).
 * @param  baudrate Desired baud rate (e.g., 9600, 115200)
 * @note   Uses alternate function AF7 on GPIOA pins.
 */
void usart2_init(int baudrate)
{
	/*** Configure UART GPIO pins ***/

	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 mode to alternate function mode (10)
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |=  (1U<<5);
	// Set PA3 mode to alternate function mode (10)
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |=  (1U<<7);

	// Set PA2 alternate function type to USART_TX (AF7 = 0111)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);
	// Set PA3 alternate function type to USART_RX (AF7 = 0111)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);

	/*** Configure UART module ***/

	// Enable clock access to USART2
	RCC->APB1ENR |= USARTEN;

	// Configure baudrate
	usart_set_baudrate(USART2, APB1_CLK, baudrate);

	// Enable transmitter and receiver
	USART2->CR1 = RC1_TE | RC1_RE;

	// Enable UART module
	USART2->CR1 |= RC1_UE;
}

/**
 * @brief  Reads one character from USART2.
 * @retval Received character
 * @note   Blocking until data is received
 */
char usart2_read(void)
{
	while(!(USART2->SR & RS_RXNE)) {} // Wait until data is received

	return USART2->DR;
}

/**
 * @brief  Sends one character over USART2.
 * @param  ch Character to send
 * @note   Blocking until TX buffer is ready
 */
void usart2_write(char ch)
{
	while(!(USART2->SR & RS_TXE)) {} // Wait until transmit buffer is empty

	USART2->DR = ch; // Only 8 bit of data register is available
}
