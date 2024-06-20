/* 
 * File:   ICU_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#ifndef ICU_INTERFACE_H
#define	ICU_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "ICU_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../02_GIE/GIE_Interface.h"
#include "../04_INTI/INTI_Interface.h"
#include "../03_EXTI/EXTI_Interface.h"
#include "../08_Timer1/Timer1_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MICU_EXTI0_T1_Read(uint32* Freq, uint8* Duty);
Std_Return MICU_T1_Read(uint32* Freq, uint8* Duty);

#endif	/* ICU_INTERFACE_H */
