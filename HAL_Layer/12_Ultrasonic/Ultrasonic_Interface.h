/* 
 * File:   Ultrasonic_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 9:18 AM
 */

#ifndef ULTRASONIC_INTERFACE_H
#define	ULTRASONIC_INTERFACE_H

/* Section : Includes */
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "../../MCAL_Layer/07_Timer0/Timer0_Interface.h"
#include "../../MCAL_Layer/11_ICU/ICU_Interface.h"
#include "Ultrasonic_Config.h"

/* Section: Macro Declarations */
#define SOUND_SPEED_CM_SECOND       34000

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct
{
    pin_t Trigger_Pin;
    pin_t Echo_Pin; 
}ultrasonic_t;

/* Section: Function Declarations */
Std_Return HUltrasonic_Init(ultrasonic_t *ultrasonic);
#if ULTRASONIC_BY_T0==ENABLE
Std_Return HUltrasonic_t0_Calculate_Distance(ultrasonic_t *ultrasonic, float32 *Distance);
#endif
#if ULTRASONIC_BY_ICU==ENABLE
Std_Return HUltrasonic_ICU_Calculate_Distance(ultrasonic_t *ultrasonic, float32 *dist);
#endif


#endif	/* ULTRASONIC_INTERFACE_H */



