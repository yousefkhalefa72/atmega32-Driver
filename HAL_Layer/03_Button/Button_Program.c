/* 
 * File:   Button_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 9, 2024, 11:16 AM
 */

#include "Button_Interface.h"

Std_Return HButton_Initialize(button_t *btn)
{
    Std_Return ret = E_OK;
    if(NULL == btn)
    {
        ret = E_NOK;
    } 
    else
    {
        btn->pin.direction = DIO_DIRECTION_INPUT;
        ret = MDIO_SetPinDirection(&(btn->pin));
    }
    return ret;
}

Std_Return HButton_Internal_PullUp(button_t *btn)
{
    Std_Return ret = E_OK;
    if(NULL == btn)
    {
        ret = E_NOK;
    } 
    else
    {
        MDIO_SetPinValue(&(btn->pin),DIO_HIGH);
    }
    return ret;
    
}

Std_Return HButton_state(button_t *btn, button_state_t *btn_state)
{
    Std_Return ret = E_OK;
    logic_t Pin_Status = DIO_LOW;
    if((NULL == btn)||(NULL == btn_state))
    {
        ret = E_NOK;
    }
    else
    {
        MDIO_GetPinValue(&(btn->pin),&Pin_Status);
      
        if(btn->type == BUTTON_ACTIVE_HIGH)
        { 
            if(Pin_Status == DIO_HIGH)
            {
                *btn_state=BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->type)
        {
            if(DIO_HIGH == Pin_Status)
            {
                *btn_state = BUTTON_RELEASED;
            }
            else
            {
                *btn_state = BUTTON_PRESSED;
            }
        }
    }
    return ret;
}

