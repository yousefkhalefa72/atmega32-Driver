/* 
 * File:   LED_Program.c
 * Author: Yousef.Khalefa
 * Created on March 8, 2024, 8:20 PM
 */

#include "LED_Interface.h"

Std_Return HLED_initialize(led_t *led)
{
    Std_Return ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOK;
    }
    else
    {
        led->led.direction = DIO_DIRECTION_OUTPUT;
        switch(led->type)
        {
            case LED_SOURCE:
                led->led.logic = led->status;break;
            case LED_SINK:
                led->led.logic = (led->status ^ BIT_MASK);break;
        }
        MDIO_SetPinDirection(&(led->led));
    }
    return ret;
}

Std_Return HLED_turn_on(led_t *led)
{
    Std_Return ret = E_OK;
     if(NULL == led)
     {
         ret = E_NOK;
     }
     else
     {
        switch(led->type)
        {
            case LED_SOURCE:
                led->led.logic = DIO_HIGH;led->status = LED_ON;
                MDIO_SetPinValue(&(led->led), DIO_HIGH);break;
            case LED_SINK:
                led->led.logic = DIO_LOW;led->status = LED_ON;
                MDIO_SetPinValue(&(led->led), DIO_LOW);break;
        }
     }
    return ret;
}

Std_Return HLED_turn_off(led_t *led)
{
    Std_Return ret = E_OK;
     if(NULL == led)
     {
         ret = E_NOK;
     }
     else
     {
        switch(led->type)
        {
            case LED_SOURCE:
                led->led.logic = DIO_LOW;led->status = LED_OFF;
                MDIO_SetPinValue(&(led->led), DIO_LOW);break;
            case LED_SINK:
                led->led.logic = DIO_HIGH;led->status = LED_OFF;
                MDIO_SetPinValue(&(led->led), DIO_HIGH);break;
        }
     }
    return ret;
}

Std_Return HLED_toggle(led_t *led)
{
    Std_Return ret = E_OK;
     if(NULL == led)
     {
         ret = E_NOK;
     }
     else
     {
        led->led.logic ^= BIT_MASK;
        led->status ^= BIT_MASK;
        MDIO_TogglePinValue(&(led->led));
     }
    return ret;
}


