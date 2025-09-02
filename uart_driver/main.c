
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

int main(void)
{
	usart2_init(115200); // BaudRate = 115200
	while(1)
	{
		char key = usart2_read();
		usart2_write(key);
	}
}
