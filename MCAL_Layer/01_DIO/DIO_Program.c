/* 
 * File:   DIO_Program.h
 * Author: Yousef.Khalefa
 * Created on 27 November, 2023, 11:56 AM
 */

#include "DIO_Interface.h"

/* Direction Control Registers */
volatile uint8 *ddr_registers[] = {&DDRA, &DDRB, &DDRC, &DDRD};
/* Write Data Registers */
volatile uint8 *port_registers[]  = {&PORTA , &PORTB , &PORTC , &PORTD};
/* Write Data Registers  */
volatile uint8 *pin_registers[] = {&PINA, &PINB, &PINC, &PIND};

#if DIO_PIN_CONFIGURATIONS==ENABLE
Std_Return MDIO_SetPinDirection(pin_t *pin)
{
    Std_Return ret = E_OK;
    if(NULL == pin)
    {
        ret = E_NOK;
    }
    else
    {
        switch(pin->direction)
        {
            case DIO_DIRECTION_OUTPUT:
                SET_BIT(*ddr_registers[pin->port], pin->pin);break;
            case DIO_DIRECTION_INPUT:
                CLR_BIT(*ddr_registers[pin->port], pin->pin);break;
            default :
                ret = E_NOK;break;
        }
        switch(pin->logic)
        {
            case DIO_LOW :
                CLR_BIT(*port_registers[pin->port], pin->pin);break;
            case DIO_HIGH :
                SET_BIT(*port_registers[pin->port], pin->pin);break;
            default :
                ret = E_NOK;break;
        }
    }
    return ret;
}

Std_Return MDIO_GetPinDirection(pin_t *pin, direction_t *direction)
{
    Std_Return ret = E_OK;
    if((NULL == pin)||(NULL == direction))
    {
        ret = E_NOK;
    }
    else
    {
        *direction = READ_BIT(*ddr_registers[pin->port], pin->pin);
    }
    return ret;
}

Std_Return MDIO_SetPinValue(pin_t *pin, logic_t logic)
{
    Std_Return ret = E_OK;
    if(NULL == pin)
    {
        ret = E_NOK;
    }
    else
    {
        switch(logic)
        {
            case DIO_LOW :
                CLR_BIT(*port_registers[pin->port], pin->pin);break;
            case DIO_HIGH :
                SET_BIT(*port_registers[pin->port], pin->pin);break;
            default :
                ret = E_NOK;break;
        }
    }
    return ret;
}

Std_Return MDIO_GetPinValue(pin_t *pin, logic_t *logic)
{
    Std_Return ret = E_OK;
    if((NULL == pin)||(NULL == logic))
    {
        ret = E_NOK;
    }
    else
    {
        *logic = READ_BIT(*pin_registers[pin->port], pin->pin);
    }
    return ret;
}

Std_Return MDIO_TogglePinValue(pin_t *pin)
{
    Std_Return ret = E_OK;
    if(NULL == pin)
    {
        ret = E_NOK;
    }
    else
    {
        TOGGLE_BIT(*port_registers[pin->port], pin->pin);
    }
    return ret;
}
#endif

#if DIO_PORT_CONFIGURATIONS==ENABLE
Std_Return MDIO_SetPortDirection(port_index_t PortNumber, uint8 u8Direction)
{
    Std_Return ret = E_OK;
    if(PortNumber > PORT_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else{
        *ddr_registers[PortNumber] = u8Direction;
    }
    return ret;
}

Std_Return MDIO_GetPortDirection(port_index_t PortNumber, uint8 *direction)
{
    Std_Return ret = E_OK;
    if((NULL == direction)||(PortNumber > PORT_MAX_NUMBER-1))
    {
        ret = E_NOK;
    }
    else
    {
        *direction = *ddr_registers[PortNumber];
    }
    return ret;
}

Std_Return MDIO_SetPortValue(port_index_t PortNumber, uint8 u8logic)
{
    Std_Return ret = E_OK;
    if(PortNumber > PORT_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
        *port_registers[PortNumber] = u8logic;
    }
    return ret;
}

Std_Return MDIO_GetPortValue(port_index_t PortNumber, uint8* u8logic)
{
    Std_Return ret = E_OK;
    if((NULL == u8logic)||(PortNumber > PORT_MAX_NUMBER-1))
    {
        ret = E_NOK;
    }
    else
    {
        *u8logic = *pin_registers[PortNumber];
    }
    return ret;
}

Std_Return MDIO_TogglePortValue(port_index_t PortNumber)
{
    Std_Return ret = E_OK;
    if(PortNumber > PORT_MAX_NUMBER-1)
    {
        ret = E_NOK;
    }
    else
    {
        *port_registers[PortNumber] ^= PORT_MASK;
    }
    return ret;
}
#endif

