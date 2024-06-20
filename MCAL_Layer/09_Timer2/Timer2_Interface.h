/* 
 * File:   Timer2_Interface.h
 * Author: Yousef.Khalefa
 *
 * Created on March 10, 2024, 11:06 PM
 */

 /* tick = (prescaler * counts)/frecuancy 
    ISR(TIMER2_COMP_vect){}
    ISR(TIMER2_OVF_vect){} */

#ifndef TIMER2_INTERFACE_H
#define	TIMER2_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Timer2_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define MTimer2_OV_CLEAR_FLAG()       (SET_BIT(TIFR,TOV2))
#define MTimer2_OV_READ_FLAG()        (READ_BIT(TIFR,TOV2))

#define MTimer2_OC_CLEAR_FLAG()       (SET_BIT(TIFR,OCF2))
#define MTimer2_OC_READ_FLAG()        (READ_BIT(TIFR,OCF2))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    T2_NO_PRESCALER = 1,
    T2_PRESCALER_8,
    T2_PRESCALER_32,
    T2_PRESCALER_64,
    T2_PRESCALER_128,
    T2_PRESCALER_256,
    T2_PRESCALER_1024,
}timer2_prescaler_t;

typedef enum
{
    T2_NORMAL = 0,
    T2_PWM_PHASE_CORRECT,
    T2_CTC,
    T2_FAST_PWM
}timer2_mode_t;

typedef enum
{
    OC2_DISCONNECTED = 0,
    OC2_NC_Toggle_on_compare,
    OC2_NC_Clear_on_compare,
    OC2_NC_Set_on_compare_match,

    OC2_FP_Clear_on_compare_Set_at_BOTTOM,
    OC2_FP_Set_on_compare_Clear_at_BOTTOM,
            
    OC2_PPC_Clear_on_up_compare_Set_at_down_compare,
    OC2_PPC_Clear_on_down_compare_Set_at_up_compare
}OC2_mode_t;

typedef uint8 timer2_preload_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MTimer2_Init(timer2_mode_t t2_mode,OC2_mode_t OC2_mode);
Std_Return MTimer2_DeInit();

Std_Return MTimer2_Star(timer2_prescaler_t prescaler);
Std_Return MTimer2_Stop();

Std_Return MTimer2_SetPreloadValue(timer2_preload_t PreLoadValue);
Std_Return MTimer2_SetOCR2Value(timer2_preload_t PreLoadValue);

Std_Return MTimer2_Read_Counts(uint8* counts);

#endif	/* TIMER2_INTERFACE_H */

