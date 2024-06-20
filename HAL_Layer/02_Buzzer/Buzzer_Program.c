/* 
 * File:   Buzzer_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 8, 2024, 8:20 PM
 */

#include "Buzzer_Interface.h"

Std_Return HBuzzer_initialize(buzzer_t *buzzer)
{
    Std_Return ret = E_OK;
    if(NULL == buzzer)
    {
        ret = E_NOK;
    }
    else
    {
        buzzer->pin.direction = DIO_DIRECTION_OUTPUT;
        switch(buzzer->type)
        {
            case Source_Buzzer:
                buzzer->pin.logic = buzzer->status;break;
            case Sink_Buzzer:
                buzzer->pin.logic = (buzzer->status ^ BIT_MASK);break;
        }
        MDIO_SetPinDirection(&(buzzer->pin));
    }
    return ret;
}

Std_Return HBuzzer_turn_on(buzzer_t *buzzer)
{
    Std_Return ret = E_OK;
     if(NULL == buzzer)
     {
         ret = E_NOK;
     }
     else
     {
        switch(buzzer->type)
        {
            case Source_Buzzer:
                buzzer->pin.logic = DIO_HIGH;buzzer->status = BUZZER_ON;
                MDIO_SetPinValue(&(buzzer->pin), DIO_HIGH);break;
            case Sink_Buzzer:
                buzzer->pin.logic = DIO_LOW;buzzer->status = BUZZER_ON;
                MDIO_SetPinValue(&(buzzer->pin), DIO_LOW);break;
        }
     }
    return ret;
}

Std_Return HBuzzer_turn_off(buzzer_t *buzzer)
{
    Std_Return ret = E_OK;
     if(NULL == buzzer)
     {
         ret = E_NOK;
     }
     else
     {
        switch(buzzer->type)
        {
            case Source_Buzzer:
                buzzer->pin.logic = DIO_LOW;buzzer->status = BUZZER_OFF;
                MDIO_SetPinValue(&(buzzer->pin), DIO_LOW);break;
            case Sink_Buzzer:
                buzzer->pin.logic = DIO_HIGH;buzzer->status = BUZZER_OFF;
                MDIO_SetPinValue(&(buzzer->pin), DIO_HIGH);break;
        }
     }
    return ret;
}

Std_Return HBuzzer_toggle(buzzer_t *buzzer)
{
    Std_Return ret = E_OK;
     if(NULL == buzzer)
     {
         ret = E_NOK;
     }
     else
     {
        buzzer->pin.logic ^= BIT_MASK;
        buzzer->status ^= BIT_MASK;
        MDIO_TogglePinValue(&(buzzer->pin));
     }
    return ret;
}



