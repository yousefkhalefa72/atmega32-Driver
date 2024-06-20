/* 
 * File:   SPI_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#ifndef SPI_INTERFACE_H
#define	SPI_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../01_DIO/DIO_Interface.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/
                                                 
/* ----------------- Macro Functions Declarations -----------------*/
#define SPI_INTERRUPT_FLAG_READ()           (READ_BIT(SPSR,SPIF))
#define SPI_COLLISION_FLAG_READ()           (READ_BIT(SPSR,WCOL))

#define SPI_INTERRUPT_ENABLE()              (SET_BIT(SPCR,SPIE))
#define SPI_INTERRUPT_DISABLE()             (CLR_BIT(SPCR,SPIE))

#define SPI_ENABLE()                        (SET_BIT(SPCR,SPE))
#define SPI_DISABLE()                       (CLR_BIT(SPCR,SPE))

#define SPI_MASTER_MODE()                   (SET_BIT(SPCR,MSTR))
#define SPI_SLAVE_MODE()                    (CLR_BIT(SPCR,MSTR))

#define SPI_IDLE_HIGH()                     (SET_BIT(SPCR,CPOL))
#define SPI_IDLE_LOW()                      (CLR_BIT(SPCR,CPOL))

#define SPI_SAMPLE_ON_TRAILING()            (SET_BIT(SPCR,CPHA))
#define SPI_SAMPLE_ON_LEADING()             (CLR_BIT(SPCR,CPHA))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    SPI_PRESCALER_4 = 0,
    SPI_PRESCALER_16,
    SPI_PRESCALER_64,
    SPI_PRESCALER_128,
    SPI_PRESCALER_2_DS,
    SPI_PRESCALER_8_DS,
    SPI_PRESCALER_32_DS,
    SPI_PRESCALER_64_DS
}SPI_Clock_Rate_t;

typedef enum
{
    SPI_IDLE_LOW_SAMPLE_RISING,
    SPI_IDLE_LOW_SAMPLE_FALLING,
    SPI_IDLE_HIGH_SAMPLE_FALLING,
    SPI_IDLE_HIGH_SAMPLE_RISING
}SPI_CLK_Mode_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MSPI_Master_Init(SPI_Clock_Rate_t rate, SPI_CLK_Mode_t mode);
Std_Return MSPI_Slave_Init(SPI_CLK_Mode_t mode);
Std_Return MSPI_DeInit();

Std_Return MSPI_Send_Byte(uint8 data);
Std_Return MSPI_Read_Byte(uint8 *data);

Std_Return MSPI_Transcieve(uint8 tx_data,uint8* rx_data);

Std_Return MSPI_Slave_Select(pin_t *slave_pin);
Std_Return MSPI_Slave_Deselect(pin_t *slave_pin);


#endif	/* SPi_INTERFACE_H */
