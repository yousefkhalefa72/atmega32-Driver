/* 
 * File:   Power_Management_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 8, 2024, 6:00 PM
 */

#ifndef Power_Management_INTERFACE_H
#define	Power_Management_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "Power_Management_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    Sleep_Idle_Mode = 0,
    Sleep_ADC_Noise_Red_Mode,
    Sleep_Power_down_Mode,
    Sleep_Power_save_Mode,
    Sleep_Standby_Mode = 6,
    Sleep_Extended_Standby_Mode
}sleep_mode_t;
/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MPM_Enable(sleep_mode_t mode);
Std_Return MPM_Disable();

void MPM_EnterSleep(void);

#endif	/* Power_Management_INTERFACE_H */






