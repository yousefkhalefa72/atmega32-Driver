/* 
 * File:   SPI_Program.c
 * Author: Yousef.Khalefa
 * Created on June 8, 2024, 7:49 PM
 */

#include "SPI_Interface.h"

uint8 *SPI_BUF ;
Std_Return MSPI_Master_Init(SPI_Clock_Rate_t rate, SPI_CLK_Mode_t mode)
{
    SPCR = 0; /* clear SPI control REG */
    
    pin_t SPI_MOSI = {.port=PORTB_INDEX,.pin=PIN5_INDEX,.direction=DIO_DIRECTION_OUTPUT,.logic=DIO_LOW};
    pin_t SPI_MISO = {.port=PORTB_INDEX,.pin=PIN6_INDEX,.direction=DIO_DIRECTION_INPUT};
    pin_t SPI_CLK = {.port=PORTB_INDEX,.pin=PIN7_INDEX,.direction=DIO_DIRECTION_OUTPUT,.logic=DIO_LOW};
    
    /* Set MOSI and SCK output, MISO input */
    MDIO_SetPinDirection(&SPI_MOSI);
    MDIO_SetPinDirection(&SPI_MISO);
    MDIO_SetPinDirection(&SPI_CLK);

    /* master mode */
    SPI_MASTER_MODE();
    
    /* select clk mode */
    SPCR |= (mode << 2) & 0x0C;
    
    /* set clock rate */
    if(rate > 3) 
        SET_BIT(SPSR,SPI2X);
    else 
        CLR_BIT(SPSR,SPI2X);
    SPCR |= (rate & 0x03);
    
    /* Enable SPI*/
    SPI_ENABLE();
    
    return E_OK;
}

Std_Return MSPI_Slave_Init( SPI_CLK_Mode_t mode)
{
    SPCR = 0; /* clear SPI control REG */
    
    pin_t SPI_MOSI = {.port=PORTB_INDEX,.pin=PIN5_INDEX,.direction=DIO_DIRECTION_INPUT};
    pin_t SPI_MISO = {.port=PORTB_INDEX,.pin=PIN6_INDEX,.direction=DIO_DIRECTION_OUTPUT,.logic=DIO_LOW};
    pin_t SPI_CLK = {.port=PORTB_INDEX,.pin=PIN7_INDEX,.direction=DIO_DIRECTION_INPUT};
    
    /* Set MISO output, all others input */
    MDIO_SetPinDirection(&SPI_MOSI);
    MDIO_SetPinDirection(&SPI_MISO);
    MDIO_SetPinDirection(&SPI_CLK);

    /* master mode */
    SPI_SLAVE_MODE();
    
    /* select clk mode */
    SPCR |= (mode << 2) & 0x0C;
    

    
    /* Enable SPI*/
    SPI_ENABLE();
    
    return E_OK;
}
Std_Return MSPI_DeInit()
{
    SPCR = 0; /* clear SPI control REG */
    return E_OK;
}

Std_Return MSPI_Send_Byte(uint8 data)
{
    /* Start transmission */
    SPDR = data;
    /* Wait for last transmission complete */
    while(!(SPSR & (1<<SPIF)));
    
    return E_OK;
}

Std_Return MSPI_Read_Byte(uint8 *data)
{
#if SPI_COM_INTERRUPT == ENABLE
    SPI_BUF = data;
    SPI_INTERRUPT_ENABLE();
#else
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)));
    /* Return data register */
    *data = SPDR;
#endif
    return E_OK;
}

Std_Return MSPI_Transcieve(uint8 tx_data, uint8* rx_data)
{
    /*Send Data*/
	SPDR = tx_data;
	/*Wait Till Transfer Finished*/
	while(!(SPSR & (1<<SPIF)));
    *rx_data = SPDR;
    
	return E_OK;
}

Std_Return MSPI_Slave_Select(pin_t *slave_pin)
{
    slave_pin->direction = DIO_DIRECTION_OUTPUT;
    slave_pin->logic = DIO_LOW;
    
    return MDIO_SetPinDirection(slave_pin);
}

Std_Return MSPI_Slave_Deselect(pin_t *slave_pin)
{
    slave_pin->direction = DIO_DIRECTION_OUTPUT;
    slave_pin->logic = DIO_HIGH;
    
    return MDIO_SetPinDirection(slave_pin);
}

#if SPI_COM_INTERRUPT == ENABLE
ISR(SPI_STC_vect)
{
    *SPI_BUF = SPDR;
    SPI_INTERRUPT_DISABLE();
}
#endif