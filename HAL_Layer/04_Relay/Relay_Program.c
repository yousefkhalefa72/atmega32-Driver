/* 
 * File:   Relay_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 9, 2024, 11:40 AM
 */

#include "Relay_Interface.h"

Std_Return HRelay_Initialize(relay_t *relay)
{
    Std_Return ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOK;
    }
    else{
        relay->pin.direction = DIO_DIRECTION_OUTPUT;
        relay->pin.logic = relay->status;
        ret = MDIO_SetPinDirection(&(relay->pin));
    }
    return ret;
}

Std_Return HRelay_turn_on(relay_t *relay)
{
    Std_Return ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOK;
    }
    else
    {
        ret = MDIO_SetPinValue(&(relay->pin), DIO_HIGH);
    }
    return ret;
}

Std_Return HRelay_turn_off(relay_t *relay)
{
    Std_Return ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOK;
    }
    else
    {
        ret = MDIO_SetPinValue(&(relay->pin), DIO_LOW);
    }
    return ret;
}

Std_Return HRelay_toggle(relay_t *relay)
{
    Std_Return ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOK;
    }
    else
    {
        ret = MDIO_TogglePinValue(&(relay->pin));
    }
    return ret;
}


