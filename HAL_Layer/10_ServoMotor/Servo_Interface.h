/* 
 * File:   Servo_Config.h
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#ifndef SERVO_INTERFACE_H
#define	SERVO_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Servo_Config.h"
#include "../../MCAL_Layer/10_PWM/PWM_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HServo_OC1A_SetServoAngle(sint16 angle);
Std_Return HServo_OC1B_SetServoAngle(sint16 angle);

#endif	/* SERVO_INTERFACE_H */

