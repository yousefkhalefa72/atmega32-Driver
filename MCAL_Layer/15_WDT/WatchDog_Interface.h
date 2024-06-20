/* 
 * File:   WatchDog_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 8, 2024, 6:00 PM
 */

#ifndef WatchDog_INTERFACE_H
#define	WatchDog_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "WatchDog_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    WDT_16ms,
    WDT_32ms,
    WDT_65ms,
    WDT_130ms,
    WDT_260ms,
    WDT_520ms,
    WDT_1s,
    WDT_2s
}WDT_5v_time_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MWDT_WatchDog_Turn_On(WDT_5v_time_t time);
Std_Return MWDT_WatchDog_Turn_Off();

#endif	/* WatchDog_INTERFACE_H */






