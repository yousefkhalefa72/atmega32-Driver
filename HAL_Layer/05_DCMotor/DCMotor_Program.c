/* 
 * File:   DC_Motor_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 9, 2024, 11:50 AM
 */

#include "DCMotor_Interface.h"

Std_Return HDCMotor_initialize(dc_motor_t *motor)
{
    Std_Return ret = E_OK;
    if(NULL == motor)
    {
        ret = E_NOK;
    }
    else
    {    
        motor->pin[0].direction = DIO_DIRECTION_OUTPUT;
        motor->pin[1].direction = DIO_DIRECTION_OUTPUT;
        switch(motor->Status)
        {
            case MOTOR_OFF :
                motor->pin[0].logic = DIO_LOW;
                motor->pin[1].logic = DIO_LOW;
                break;
            case MOTOR_ON_RIGHT :
                motor->pin[0].logic = DIO_HIGH;
                motor->pin[1].logic = DIO_LOW;
                break;
            case MOTOR_ON_LEFT :
                motor->pin[0].logic = DIO_LOW;
                motor->pin[1].logic = DIO_HIGH;
                break;
            case MOTOR_BREAK :
                motor->pin[0].logic = DIO_HIGH;
                motor->pin[1].logic = DIO_HIGH;
                break;
        }
        ret = MDIO_SetPinDirection(&(motor->pin[0]));
        ret |= MDIO_SetPinDirection(&(motor->pin[1]));
    }
    return ret;
}

Std_Return HDCMotor_move_right(dc_motor_t *motor)
{
    Std_Return ret = E_OK;
    if(NULL == motor)
    {
        ret = E_NOK;
    }
    else
    {
        motor->Status = MOTOR_ON_RIGHT;
        ret = MDIO_SetPinValue(&(motor->pin[0]),DIO_HIGH);
        ret |= MDIO_SetPinValue(&(motor->pin[1]),DIO_LOW);
    }
    return ret;
}

Std_Return HDCMotor_move_left(dc_motor_t *motor)
{
    Std_Return ret = E_OK;
    if(NULL == motor)
    {
        ret = E_NOK;
    }
    else
    {
        motor->Status = MOTOR_ON_LEFT;
        ret = MDIO_SetPinValue(&(motor->pin[0]),DIO_LOW);
        ret |= MDIO_SetPinValue(&(motor->pin[1]),DIO_HIGH);
    }
    return ret;
}

Std_Return HDCMotor_stop(dc_motor_t *motor)
{
    Std_Return ret = E_OK;
    if(NULL == motor)
    {
        ret = E_NOK;
    }
    else
    {
        motor->Status = MOTOR_OFF;
        ret = MDIO_SetPinValue(&(motor->pin[0]),DIO_LOW);
        ret |= MDIO_SetPinValue(&(motor->pin[1]),DIO_LOW);
    }
    return ret;
}

