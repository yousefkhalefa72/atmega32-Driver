#if 0

#include "UART_Interface.h"

    
MUART_Init(UART_BOUD_RATE_9600,UART_8_BITS);

MUART_Transmit_Byte('A');
MUART_Transmit_Byte('\r');

uint8 str[8] = "YOUSEF\r";
MUART_Transmit_String(str);

uint8 data = 0;
MUART_Receive(&data);

#endif