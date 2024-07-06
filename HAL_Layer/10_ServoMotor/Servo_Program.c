/* 
 * File:   Servo_Interface.c
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#include "Servo_Interface.h"

Std_Return HServo_OC1A_SetServoAngle(sint16 angle) 
{
    // valid range
    if (angle < SERVO_MIN_ANGLE)
        angle = SERVO_MIN_ANGLE;
    if (angle > SERVO_MAX_ANGLE)
        angle = SERVO_MAX_ANGLE;

    // Calculate pulse width in microseconds
    uint16_t pulse_width = SERVO_MAX_PULSE_WIDTH + ((sint32)(angle-SERVO_MAX_ANGLE)*(SERVO_MAX_PULSE_WIDTH-SERVO_MIN_PULSE_WIDTH))/(SERVO_MAX_ANGLE-SERVO_MIN_ANGLE);
    
    return MPWM1_Start(PWM_FAST_PWM,T1_PRESCALER_8,SERVO_PERIOD,pulse_width,0);
}

Std_Return HServo_OC1B_SetServoAngle(sint16 angle) 
{
    // valid range
    if (angle < SERVO_MIN_ANGLE)
        angle = SERVO_MIN_ANGLE;
    if (angle > SERVO_MAX_ANGLE)
        angle = SERVO_MAX_ANGLE;

    // Calculate pulse width in microseconds
    uint16_t pulse_width = SERVO_MAX_PULSE_WIDTH + ((sint32)(angle-SERVO_MAX_ANGLE)*(SERVO_MAX_PULSE_WIDTH-SERVO_MIN_PULSE_WIDTH))/(SERVO_MAX_ANGLE-SERVO_MIN_ANGLE);

    return MPWM1_Start(PWM_FAST_PWM,T1_PRESCALER_8,SERVO_PERIOD,0,pulse_width);
}
