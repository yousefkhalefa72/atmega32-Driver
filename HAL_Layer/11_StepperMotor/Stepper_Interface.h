/* 
 * File:   Stepper_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#ifndef STEPPER_INTERFACE_H
#define	STEPPER_INTERFACE_H

/* Section : Includes */
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "../../MCAL_Layer/07_Timer0/Timer0_Interface.h"
#include "Stepper_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct
{
    pin_t blue_coil ;
    pin_t pink_coil ;
    pin_t yellow_coil ;
    pin_t orange_coil ;
}stepper_t;

typedef enum
{
    stepper_0d,
    stepper_45d,
    stepper_90d,
    stepper_135d,
    stepper_180d,
    stepper_225d,
    stepper_270d,
    stepper_315d,
}degree_t;

/* Section: Function Declarations */
Std_Return HStepper_init(stepper_t *motor);
Std_Return HStepper_Rotate(stepper_t *motor,degree_t degree);
#if T0_for_STEPPER == ENABLE
/* NOT accurate due to simulation and force timer0 in CTC with 1 ms for another program */
Std_Return HStepper_Speed_t0(stepper_t *motor,float32 RPS); 
#endif

#endif	/* STEPPER_INTERFACE_H */

