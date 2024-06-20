/* 
 * File:   Timer0_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 10:42 AM
 */

#ifndef TIMER0_INTERFACE_H
#define	TIMER0_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Timer0_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define MTimer0_OV_CLEAR_FLAG()       (SET_BIT(TIFR,TOV0))
#define MTimer0_OV_READ_FLAG()        (READ_BIT(TIFR,TOV0))

#define MTimer0_OC_CLEAR_FLAG()       (SET_BIT(TIFR,OCF0))
#define MTimer0_OC_READ_FLAG()        (READ_BIT(TIFR,OCF0))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    T0_NO_PRESCALER = 1,
    T0_PRESCALER_8,
    T0_PRESCALER_64,
    T0_PRESCALER_256,
    T0_PRESCALER_1024,
    T0_FALLING_EDGE_on_T0,
    T0_RISING_EDGE_on_T0
}timer0_prescaler_t;

typedef enum
{
    T0_NORMAL = 0,
    T0_PWM_PHASE_CORRECT,
    T0_CTC,
    T0_FAST_PWM
}timer0_mode_t;

typedef enum
{
    OC0_DISCONNECTED = 0,
    OC0_NC_Toggle_on_compare,
    OC0_NC_Clear_on_compare,
    OC0_NC_Set_on_compare_match,

    OC0_FP_Clear_on_compare_Set_at_BOTTOM,
    OC0_FP_Set_on_compare_Clear_at_BOTTOM,
            
    OC0_PPC_Clear_on_up_compare_Set_at_down_compare,
    OC0_PPC_Clear_on_down_compare_Set_at_up_compare
}OC0_mode_t;

typedef uint8 timer0_preload_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MTimer0_Init(timer0_mode_t t0_mode,OC0_mode_t OC0_mode);
Std_Return MTimer0_DeInit();

Std_Return MTimer0_Star(timer0_prescaler_t prescaler);
Std_Return MTimer0_Stop();

Std_Return MTimer0_SetPreloadValue(timer0_preload_t PreLoadValue);
Std_Return MTimer0_SetOCR0Value(timer0_preload_t PreLoadValue);

Std_Return MTimer0_Read_Counts(uint8* counts);


#endif	/* TIMER0_INTERFACE_H */

