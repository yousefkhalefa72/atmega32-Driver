/* 
 * File:   ESP8266_Program.c
 * Author: Yousef_Khalefa
 * Created on June 20, 2024, 12:22 PM
 */

#include "ESP8266_Interface.h"


Std_Return HESP8266_Init() 
{
    return MUART_Init(UART_BOUD_RATE_9600,UART_8_BITS);
}

Std_Return HESP8266_SendCommand(uint8* command) 
{
    Std_Return ret = E_OK;
    while (*command) 
    {
        ret &= MUART_Transmit_String(command);
        command++;
    }
    ret &= MUART_Transmit_Byte('\r');
    ret &= MUART_Transmit_Byte('\n');
    
    return ret; 
}

Std_Return HESP8266_ReadResponse(uint8* data) 
{
    return MUART_Receive(data);
}
