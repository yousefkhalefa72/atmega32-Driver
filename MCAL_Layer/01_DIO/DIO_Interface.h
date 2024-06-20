/* 
 * File:   DIO_Interface.h
 * Author: Yousef.Khalefa
 *
 * Created on March 8, 2024, 7:17 PM
 */

#ifndef DIO_INTERFACE_H
#define	DIO_INTERFACE_H

/* Section : Includes */
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "DIO_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */
#define PORT_DIRECTION_OUTPUT 0xFF
#define PORT_DIRECTION_INPUT  0x00

/* Section: Data Type Declarations */
typedef enum
{
    DIO_LOW  = 0,
    DIO_HIGH
}logic_t;

typedef enum
{
    DIO_DIRECTION_INPUT = 0,
    DIO_DIRECTION_OUTPUT
}direction_t;

typedef enum
{
    PIN0_INDEX = 0,
    PIN1_INDEX,
    PIN2_INDEX,
    PIN3_INDEX,
    PIN4_INDEX,
    PIN5_INDEX,
    PIN6_INDEX,
    PIN7_INDEX
}pin_index_t;

typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
}port_index_t;

typedef struct
{
    port_index_t port : 2;    
    pin_index_t pin : 3;        
    direction_t direction : 1; 
    logic_t logic : 1;          
}pin_t;

/* Section: Function Declarations */
#if DIO_PIN_CONFIGURATIONS==ENABLE
Std_Return MDIO_SetPinDirection(pin_t* pin);
Std_Return MDIO_GetPinDirection(pin_t* pin, direction_t* direction);
Std_Return MDIO_SetPinValue(pin_t* pin, logic_t logic);
Std_Return MDIO_GetPinValue(pin_t* pin, logic_t* logic);
Std_Return MDIO_TogglePinValue(pin_t *pin);
#endif

#if DIO_PORT_CONFIGURATIONS==ENABLE
Std_Return MDIO_SetPortDirection(port_index_t PortNumber, uint8 u8Direction);
Std_Return MDIO_GetPortDirection(port_index_t PortNumber, uint8* direction);
Std_Return MDIO_SetPortValue(port_index_t PortNumber, uint8 u8logic);
Std_Return MDIO_GetPortValue(port_index_t PortNumber, uint8* u8logic);
Std_Return MDIO_TogglePortValue(port_index_t PortNumber);
#endif


#endif	/* DIO_INTERFACE_H */

