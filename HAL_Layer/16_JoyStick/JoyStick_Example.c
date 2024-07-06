#if 0

#include "JoyStick_Interface.h"

JoyStick_t joy1 = {.x_pin.port = PORTA_INDEX, .x_pin.pin = PIN0_INDEX,
				   .y_pin.port = PORTA_INDEX, .y_pin.pin = PIN1_INDEX};

uint16 x_value;
uint16 y_value;

uint8 x_angle;
uint8 y_angle;

HJoyStick_Init(&joy1, ADC_AVCC);
/* method 1*/
HJoyStick_Read(&joy1, &x_value, &y_value);
/* method 2*/
HJoyStick_Read_Angle(&joy1, &x_angle, &y_angle);

#endif
