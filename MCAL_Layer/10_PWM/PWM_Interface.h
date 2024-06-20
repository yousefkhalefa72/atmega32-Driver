/* 
 * File:   PWM_Interface.h
 * Author: Yousef.Khalefa
 *
 * Created on May 15, 2024, 10:31 AM
 */

#ifndef PWM_INTERFACE_H
#define	PWM_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "PWM_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"
#include "../07_Timer0/Timer0_Interface.h"
#include "../08_Timer1/Timer1_Interface.h"
#include "../09_Timer2/Timer2_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    FAST_PWM,
    PHASE_CORRECT
}pwm_mode_t;

/* ----------------- Software Interfaces Declarations -----------------*/
#if PWM0_CONFIG==ENABLE
Std_Return MPWM0_Start(pwm_mode_t mode,timer0_prescaler_t prescaller, uint8 oc0_value);
Std_Return MPWM0_Start_duty(pwm_mode_t mode,timer0_prescaler_t prescaller, uint8 duty_cycle);
Std_Return MPWM0_Start_volt(pwm_mode_t mode,timer0_prescaler_t prescaller, float32 volt);
Std_Return MPWM0_Stop();
#endif

#if PWM1_CONFIG==ENABLE
Std_Return MPWM1_Start(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, uint16 oc1A_value, uint16 oc1B_value);
Std_Return MPWM1_Start_duty(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, uint8 A_duty_cycle, uint8 B_duty_cycle);
Std_Return MPWM1_Start_volt(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, float32 A_volt, float32 B_volt);
Std_Return MPWM1_Stop();
#endif

#if PWM2_CONFIG==ENABLE
Std_Return MPWM2_Start(pwm_mode_t mode, timer2_prescaler_t prescaller, uint8 oc2_value);
Std_Return MPWM2_Start_duty(pwm_mode_t mode, timer2_prescaler_t prescaller, uint8 duty_cycle);
Std_Return MPWM2_Start_volt(pwm_mode_t mode, timer2_prescaler_t prescaller, float32 volt);
Std_Return MPWM2_Stop();
#endif


#endif	/* PWM_INTERFACE_H */
