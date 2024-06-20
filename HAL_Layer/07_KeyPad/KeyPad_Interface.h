/* 
 * File:   KeyPad_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 1:37 PM
 */

#ifndef KEYPAD_INTERFACE_H
#define	KEYPAD_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "KeyPad_Config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct
{
    pin_t keypad_row_pins[KEYPAD_ROWS];
    pin_t keypad_columns_pins[KEYPAD_COLUMNS]; 
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return Hkeypad_initialize(keypad_t *keypad);
Std_Return Hkeypad_get_value(keypad_t *keypad, uint8 *value);


#endif	/* KEYPAD_INTERFACE_H */

