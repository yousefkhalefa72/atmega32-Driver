/* 
 * File:   Timer1_Interface.h
 * Author: Yousef.Khalefa
 *
 * Created on March 10, 2024, 11:06 PM
 */

#ifndef TIMER1_INTERFACE_H
#define	TIMER1_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Timer1_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define MTimer1_OV_CLEAR_FLAG()        (SET_BIT(TIFR,TOV1))
#define MTimer1_OV_READ_FLAG()         (READ_BIT(TIFR,TOV1))

#define MTimer1_OCA_CLEAR_FLAG()       (SET_BIT(TIFR,OCF1A))
#define MTimer1_OCA_READ_FLAG()        (READ_BIT(TIFR,OCF1A))

#define MTimer1_OCB_CLEAR_FLAG()       (SET_BIT(TIFR,OCF1B))
#define MTimer1_OCB_READ_FLAG()        (READ_BIT(TIFR,OCF1B))

#define MTimer1_IC_CLEAR_FLAG()        (SET_BIT(TIFR,ICF1))
#define MTimer1_IC_READ_FLAG()         (READ_BIT(TIFR,ICF1))

#define MTimer1_IC_Noise_Canceler_Enable()     (SET_BIT(TCCR1B,ICNC1))
#define MTimer1_IC_Noise_Canceler_Disable()    (CLR_BIT(TCCR1B,ICNC1))

#define MTimer1_IC_Rising_Edge_Select()        (SET_BIT(TCCR1B,ICES1))
#define MTimer1_IC_Falling_Edge_Select()       (CLR_BIT(TCCR1B,ICES1))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    T1_NO_PRESCALER = 1,
    T1_PRESCALER_8,
    T1_PRESCALER_64,
    T1_PRESCALER_256,
    T1_PRESCALER_1024,
    T1_FALLING_EDGE_on_T1,
    T1_RISING_EDGE_on_T1
}timer1_prescaler_t;

typedef enum
{
    T1_NORMAL = 0,
            
    T1_PWM_PHASE_CORRECT_8bit,
    T1_PWM_PHASE_CORRECT_9bit,
    T1_PWM_PHASE_CORRECT_10bit,
            
    T1_CTC_OCR1A,
            
    T1_FAST_PWM_8bit,
    T1_FAST_PWM_9bit,
    T1_FAST_PWM_10bit,
            
    T1_PHASE_FREQ_CORRECT_ICR1,
    T1_PHASE_FREQ_CORRECT_OCR1A,
          
    T1_PHASE_CORRECT_ICR1,
    T1_PHASE_CORRECT_OCR1A,
            
    T1_CTC_ICR1,
            
    T1_FAST_PWM_ICR1 = 14,
    T1_FAST_PWM_OCR1A,
}timer1_mode_t;

typedef enum
{
    OC1A_DISCONNECTED = 0,
    OC1A_NC_Toggle_on_compare,
    OC1A_NC_Clear_on_compare,
    OC1A_NC_Set_on_compare_match,

    OC1A_FP_Toggle_on_compare = 1,
    OC1A_FP_Clear_on_compare_Set_at_BOTTOM,
    OC1A_FP_Set_on_compare_Clear_at_BOTTOM,
            
    OC1A_PPC_Toggle_on_compare = 1,
    OC1A_PPC_Clear_on_up_compare_Set_at_down_compare,
    OC1A_PPC_Clear_on_down_compare_Set_at_up_compare
}OC1A_mode_t;

typedef enum
{
    OC1B_DISCONNECTED = 0,
    OC1B_NC_Toggle_on_compare,
    OC1B_NC_Clear_on_compare,
    OC1B_NC_Set_on_compare_match,

    OC1B_FP_Clear_on_compare_Set_at_BOTTOM = 2,
    OC1B_FP_Set_on_compare_Clear_at_BOTTOM,
            
    OC1B_PPC_Clear_on_up_compare_Set_at_down_compare = 2,
    OC1B_PPC_Clear_on_down_compare_Set_at_up_compare
}OC1B_mode_t;

typedef uint16 timer1_preload_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MTimer1_Init(timer1_mode_t t1_mode, OC1A_mode_t OC1A_mode, OC1B_mode_t OC1B_mode);
Std_Return MTimer1_DeInit();

Std_Return MTimer1_Star(timer1_prescaler_t prescaler);
Std_Return MTimer1_Stop();

Std_Return MTimer1_SetPreloadValue(timer1_preload_t PreLoadValue);
Std_Return MTimer1_SetOCR1AValue(timer1_preload_t PreLoadValue);
Std_Return MTimer1_SetOCR1BValue(timer1_preload_t PreLoadValue);

Std_Return MTimer1_Read_Counts(uint16* counts);

#endif	/* TIMER1_INTERFACE_H */

