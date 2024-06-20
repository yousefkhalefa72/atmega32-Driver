/* 
 * File:   Button_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 11:16 AM
 */

#ifndef BUTTON_INTERFACE_H
#define	BUTTON_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "Button_Config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_type_t;

typedef struct
{
    pin_t pin ;
    button_type_t type : 1;
}button_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HButton_Initialize(button_t *btn);
Std_Return HButton_Internal_PullUp(button_t *btn);
Std_Return HButton_state(button_t *btn, button_state_t *state);


#endif	/* BUTTON_INTERFACE_H */

