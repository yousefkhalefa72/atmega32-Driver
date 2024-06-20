/* 
 * File:   Relay_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 11:40 AM
 */

#ifndef RELAY_INTERFACE_H
#define	RELAY_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Relay_Config.h"
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON = 1
}Relay_status_t;

typedef struct
{
    pin_t pin;
    Relay_status_t status : 1;
}relay_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HRelay_Initialize(relay_t *relay);
Std_Return HRelay_turn_on(relay_t *relay);
Std_Return HRelay_turn_off(relay_t *relay);
Std_Return HRelay_toggle(relay_t *relay);

#endif	/* RELAY_INTERFACE_H */

