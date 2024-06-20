/* 
 * File:   UART_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#ifndef UART_INTERFACE_H
#define	UART_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "UART_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/
#define UART_BOUD_RATE_2400     2400
#define UART_BOUD_RATE_4800     4800
#define UART_BOUD_RATE_9600     9600
#define UART_BOUD_RATE_14_4K    14400
#define UART_BOUD_RATE_19_2K    19200
#define UART_BOUD_RATE_28_8K    28800
#define UART_BOUD_RATE_38_4K    38400
#define UART_BOUD_RATE_57_6K    57600
#define UART_BOUD_RATE_76_8K    76800
#define UART_BOUD_RATE_115_2K   115200
#define UART_BOUD_RATE_230_4K   230400
#define UART_BOUD_RATE_250K     250000
#define UART_BOUD_RATE_0_5M     500000
#define UART_BOUD_RATE_1M       1000000

/* ----------------- Macro Functions Declarations -----------------*/
#define UART_FRAME_ERROR_STATUS     (READ_BIT(UCSRA,FE))
#define UART_DATA_OVRUN_STATUS      (READ_BIT(UCSRA,DOR))
#define UART_Parity_Error_STATUS    (READ_BIT(UCSRA,PE))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    UART_5_BITS,
    UART_6_BITS,
    UART_7_BITS,   
    UART_8_BITS,
    UART_9_BITS
}UART_Character_Size_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MUART_Init(uint32 Boud_Rate,UART_Character_Size_t Character_Size);
Std_Return MUART_DeInit();

Std_Return MUART_Transmit_Byte(uint8 data);
Std_Return MUART_Transmit_String(uint8 *data);

Std_Return MUART_Receive(uint8 *data);

#endif	/* UART_INTERFACE_H */