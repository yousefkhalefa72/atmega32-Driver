/* 
 * File:   Device_Config.h
 * Author: Yousef.Khalefa
 * Created on March 8, 2024, 7:08 PM
 */

#ifndef DEVICE_CONFIG_H
#define	DEVICE_CONFIG_H

/* Section: Macro Declarations */
#define F_CPU       8000000UL

#define PIN_MAX_NUMBER          8
#define PORT_MAX_NUMBER         4

/* Section : Includes */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Compiler.h"

/* Section: Macro Functions Declarations */
#define MCAL_Delay_ms(time)    (_delay_ms(time))
#define MCAL_Delay_us(time)    (_delay_us(time))

/* Section: Data Type Declarations */

/* Section: Function Declarations */

#endif	/* DEVICE_CONFIG_H */

