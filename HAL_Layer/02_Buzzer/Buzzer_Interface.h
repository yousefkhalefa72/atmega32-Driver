/* 
 * File:   Buzzer_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 8, 2024, 8:39 PM
 */


#ifndef BUZZER_INTERFACE_H
#define	BUZZER_INTERFACE_H

/* Section : Includes */
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "Buzzer_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum
{
    BUZZER_OFF = 0,
    BUZZER_ON
}buzzer_status_t;

typedef enum
{
    Source_Buzzer = 0,
    Sink_Buzzer = 1
}buzzer_type_t;

typedef struct
{
    pin_t pin;
    buzzer_type_t type :1;
    buzzer_status_t status :1;
}buzzer_t;

/* Section: Function Declarations */
Std_Return HBuzzer_initialize(buzzer_t *buzzer);

Std_Return HBuzzer_turn_on(buzzer_t *buzzer);
Std_Return HBuzzer_turn_off(buzzer_t *buzzer);
Std_Return HBuzzer_toggle(buzzer_t *buzzer);

#endif	/* BUZZER_INTERFACE_H */

