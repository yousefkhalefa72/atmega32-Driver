/*
 * File:   JoyStick_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 20, 2024, 12:22 PM
 */

#ifndef JoyStick_INTERFACE_H
#define	JoyStick_INTERFACE_H

/* Section : Includes */
#include "JoyStick_Config.h"
#include "../../MCAL_Layer/06_ADC/ADC_Interface.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct
{
	pin_t x_pin;
	pin_t y_pin;
}JoyStick_t;

/* Section: Function Declarations */
Std_Return HJoyStick_Init(JoyStick_t* joystick, ADC_RefVolt_t reference_volt);
Std_Return HJoyStick_DeInit();
Std_Return HJoyStick_Read(JoyStick_t* joystick, uint16* x_value, uint16* y_value);
Std_Return HJoyStick_Read_Angle(JoyStick_t* joystick, uint8* x_angle, uint8* y_angle);

#endif	/* JoyStick_INTERFACE_H */

