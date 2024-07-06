/*
 * File:   JoyStick_Program.c
 * Author: Yousef.Khalefa
 * Created on June 20, 2024, 12:22 PM
 */

#include "JoyStick_Interface.h"


/* Section: Function Declarations */
Std_Return HJoyStick_Init(JoyStick_t* joystick, ADC_RefVolt_t reference_volt)
{
	joystick->x_pin.port=PORTA_INDEX;
	joystick->x_pin.direction=DIO_DIRECTION_INPUT;
	joystick->y_pin.port=PORTA_INDEX;
	joystick->y_pin.direction=DIO_DIRECTION_INPUT;
    return MADC_Init(ADC_DIVF_128,ADC_right_adjust,reference_volt);
}

Std_Return HJoyStick_DeInit()
{
    MADC_DeInit();
    return E_OK;
}

Std_Return HJoyStick_Read(JoyStick_t* joystick, uint16* x_value, uint16* y_value)
{
	Std_Return ret = E_OK;
    ret = MADC_Conversion(joystick->x_pin.pin, x_value);
    ret &= MADC_Conversion(joystick->y_pin.pin, y_value);

    return ret;
}

Std_Return HJoyStick_Read_Angle(JoyStick_t* joystick, uint8* x_angle, uint8* y_angle)
{
	Std_Return ret = E_OK;
	uint16 x_value;
	uint16 y_value;

	ret = MADC_Conversion(joystick->x_pin.pin, &x_value);
    ret &= MADC_Conversion(joystick->y_pin.pin, &y_value);

    *x_angle  = (float32)x_value*180 / 1023;
    *y_angle  = (float32)y_value*180 / 1023;

    return ret;
}
