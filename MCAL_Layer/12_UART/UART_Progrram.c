/* 
 * File:   UART_Program.c
 * Author: Yousef_Khalefa
 * Created on June 2, 2024, 5:59 PM
 */

#include "UART_Interface.h"

#define UART_RX_Complete_Interrupt_Enable()           (SET_BIT(UCSRB,RXCIE))
#define UART_RX_Complete_Interrupt_Disable()          (CLR_BIT(UCSRB,RXCIE))
#define UART_RX_Complete_Interrupt_Flag()             (READ_BIT(UCSRA,RXC))

#define UART_TX_Complete_Interrupt_Enable()           (SET_BIT(UCSRB,TXCIE))
#define UART_TX_Complete_Interrupt_Disable()          (CLR_BIT(UCSRB,TXCIE))
#define UART_TX_Complete_Interrupt_Flag()             (READ_BIT(UCSRA,TXC))

#define UART_Data_Reg_Empty_Interrupt_Enable()        (SET_BIT(UCSRB,UDRIE))
#define UART_Data_Reg_Empty_Interrupt_Disable()       (CLR_BIT(UCSRB,UDRIE))
#define UART_Data_Reg_Empty_Interrupt_Flag()          (READ_BIT(UCSRA,UDRE))

#define UART_Receiver_Enable()                        (SET_BIT(UCSRB,RXEN))
#define UART_Receiver_Disable()                       (CLR_BIT(UCSRB,RXEN))

#define UART_Transmitter_Enable()                     (SET_BIT(UCSRB,TXEN))
#define UART_Transmitter_Disable()                    (CLR_BIT(UCSRB,TXEN))

#define UART_SYNCHRONOUS_MODE_SELECT()                (SET_BIT(UCSRC,UMSEL))
#define UART_ASYNCHRONOUS_MODE_SELECT()               (CLR_BIT(UCSRC,UMSEL))

#define UART_STOP_1_BIT()                             (CLR_BIT(UCSRC,USBS))
#define UART_STOP_2_BIT()                             (SET_BIT(UCSRC,USBS))

#define UART_CLK_POL_TOR_ROF()                        (CLR_BIT(UCSRC,UCPOL))
#define UART_CLK_POL_TOF_ROR()                        (SET_BIT(UCSRC,UCPOL))

#define UART_PARITY_NONE()                            (UCSRC &= 0b11001111)
#define UART_PARITY_ODD()                             (UCSRC |= 0b00110000)
#define UART_PARITY_EVEN()                            (do{CLR_BIT(UCSRC,UPM0);\
                                                          SET_BIT(UCSRC,UPM1);\
                                                          }while(0))

static uint8 UART_tx_buf;

Std_Return MUART_Init(uint32 Boud_Rate,UART_Character_Size_t Character_Size)
{
    Std_Return ret = E_OK;
     
    uint16 Boud_Rate_Value = (F_CPU/(16.0*Boud_Rate))-1;
    UBRRH = (uint8)(Boud_Rate_Value>>8);
    UBRRL = (uint8)Boud_Rate_Value;

    UART_Receiver_Enable();
    UART_Transmitter_Enable();
    
    UART_ASYNCHRONOUS_MODE_SELECT();

    UART_PARITY_NONE();
    UART_STOP_1_BIT();

    switch(Character_Size)
    {
        case UART_5_BITS:
            CLR_BIT(UCSRB,UCSZ2);CLR_BIT(UCSRC,UCSZ1);CLR_BIT(UCSRC,UCSZ0);break;
        case UART_6_BITS:
            CLR_BIT(UCSRB,UCSZ2);CLR_BIT(UCSRC,UCSZ1);SET_BIT(UCSRC,UCSZ0);
            break;
        case UART_7_BITS:
            CLR_BIT(UCSRB,UCSZ2);SET_BIT(UCSRC,UCSZ1);CLR_BIT(UCSRC,UCSZ0);
            break;
        case UART_8_BITS:
            CLR_BIT(UCSRB,UCSZ2);SET_BIT(UCSRC,UCSZ1);SET_BIT(UCSRC,UCSZ0);
            break;
        case UART_9_BITS:
            SET_BIT(UCSRB,UCSZ2);SET_BIT(UCSRC,UCSZ1);SET_BIT(UCSRC,UCSZ0);
            break;
        default:
            ret = E_NOK;
            break;       
    }
    return ret;
}

Std_Return MUART_DeInit()
{
#if UART_TX_COM_INTERRUPT==ENABLE
    UART_TX_Complete_Interrupt_Disable();
#endif
#if UART_RX_COM_INTERRUPT==ENABLE
    UART_TX_Complete_Interrupt_Disable();
#endif
#if UART_DATA_REG_INTERRUPT==ENABLE
    UART_Data_Reg_Empty_Interrupt_Disable();
#endif
    
    UART_Receiver_Disable();
    UART_Transmitter_Disable();
    return E_OK;
}

Std_Return MUART_Transmit_Byte(uint8 data)
{
#if UART_DATA_REG_INTERRUPT==ENABLE
    UART_tx_buf = data;
    UART_Data_Reg_Empty_Interrupt_Enable();
#else
    /* Wait for empty transmit buffer */
    while(UART_Data_Reg_Empty_Interrupt_Flag() == 0);
    /* Put data into buffer, sends the data */
    UDR = data;
#endif
    return E_OK;
}

Std_Return MUART_Transmit_String(uint8 *data)
{
    while(*data)
    {
        /* Wait for empty transmit buffer */
        while(UART_Data_Reg_Empty_Interrupt_Flag() == 0);
        /* Put data into buffer, sends the data */
        UDR = *data++;
    }
    return E_OK;
}

Std_Return MUART_Receive(uint8 *data)
{
     /* Wait for data to be received */
    while(UART_RX_Complete_Interrupt_Flag() == 0);
    /* Get received data from buffer */
    *data = UDR;
    
    return E_OK;
}


ISR(USART_UDRE_vect)
{
    UART_Data_Reg_Empty_Interrupt_Disable();
    UDR = UART_tx_buf;
}