/* 
 * File:   DCMotor_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 11:50 AM
 */

#ifndef DCMOTOR_INTERFACE_H
#define	DCMOTOR_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "DCMotor_Config.h"
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    MOTOR_OFF = 0,
    MOTOR_ON_RIGHT = 1,
    MOTOR_ON_LEFT = 2,
    MOTOR_BREAK = 3
}Motor_status_t;

typedef struct
{
    pin_t pin[2];
    Motor_status_t Status   :4;
}dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HDCMotor_initialize(dc_motor_t *motor);

Std_Return HDCMotor_move_right(dc_motor_t *motor);
Std_Return HDCMotor_move_left(dc_motor_t *motor);
Std_Return HDCMotor_stop(dc_motor_t *motor);

#endif	/* DCMOTOR_INTERFACE_H */

