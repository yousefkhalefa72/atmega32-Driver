/* 
 * File:   GIE_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 8:30 AM
 */

#ifndef GIE_INTERFACE_H
#define	GIE_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "GIE_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../01_DIO/DIO_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define MGIE_Enable()      (SET_BIT(SREG,SREG_I))
#define MGIE_Disable()     (CLR_BIT(SREG,SREG_I))
#define MGIE_Get_Status()  (READ_BIT(SREG,SREG_I))

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/


#endif	/* GIE_INTERFACE_H */

