/* 
 * File:   PCA9685_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 28, 2024, 1:04 PM
 */

#ifndef PCA9685_INTERFACE_H
#define	PCA9685_INTERFACE_H

/* Section : Includes */
#include "PCA9685_Config.h"
#include "../../MCAL_Layer/14_TWI/TWI_Interface.h"
#include "../10_ServoMotor/Servo_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */
Std_Return HPCA9685_write(uint8 reg, uint8 data);
Std_Return HPCA9685_init();
Std_Return HPCA9685_set_pwm(uint8 channel, uint16 on_12bit);
Std_Return HPCA9685_set_servo_angle(uint8 channel, sint16 angle);

#endif	/* PCA9685_INTERFACE_H */

