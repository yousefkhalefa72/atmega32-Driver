/* 
 * File:   LED_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 8, 2024, 8:20 PM
 */
 

#ifndef LED_INTERFACE_H
#define	LED_INTERFACE_H

/* Section : Includes */
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "LED_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum
{
    LED_OFF = 0,
    LED_ON
}Led_status_t;

typedef enum
{
    Source_Led = 0,
    Sink_Led
}led_type_t;

typedef struct
{
    pin_t pin;
    led_type_t type :1;
    Led_status_t status :1;
}led_t;

/* Section: Function Declarations */
Std_Return HLED_initialize(led_t *led);

Std_Return HLED_turn_on(led_t *led);
Std_Return HLED_turn_off(led_t *led);
Std_Return HLED_toggle(led_t *led);

#endif	/* LED_INTERFACE_H */

