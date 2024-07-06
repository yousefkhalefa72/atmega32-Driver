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
        buzzer->buzzer.direction = DIO_DIRECTION_OUTPUT;
        switch(buzzer->type)
        {
            case BUZZER_SOURCE:
                buzzer->buzzer.logic = buzzer->status;break;
            case BUZZER_SINK:
                buzzer->buzzer.logic = (buzzer->status ^ BIT_MASK);break;
        }
        MDIO_SetPinDirection(&(buzzer->buzzer));
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
            case BUZZER_SOURCE:
                buzzer->buzzer.logic = DIO_HIGH;buzzer->status = BUZZER_ON;
                MDIO_SetPinValue(&(buzzer->buzzer), DIO_HIGH);break;
            case BUZZER_SINK:
                buzzer->buzzer.logic = DIO_LOW;buzzer->status = BUZZER_ON;
                MDIO_SetPinValue(&(buzzer->buzzer), DIO_LOW);break;
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
            case BUZZER_SOURCE:
                buzzer->buzzer.logic = DIO_LOW;buzzer->status = BUZZER_OFF;
                MDIO_SetPinValue(&(buzzer->buzzer), DIO_LOW);break;
            case BUZZER_SINK:
                buzzer->buzzer.logic = DIO_HIGH;buzzer->status = BUZZER_OFF;
                MDIO_SetPinValue(&(buzzer->buzzer), DIO_HIGH);break;
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
        buzzer->buzzer.logic ^= BIT_MASK;
        buzzer->status ^= BIT_MASK;
        MDIO_TogglePinValue(&(buzzer->buzzer));
     }
    return ret;
}



