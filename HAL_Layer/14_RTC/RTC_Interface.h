/* 
 * File:   RTC_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 6:33 PM
 */

#ifndef RTC_INTERFACE_H
#define	RTC_INTERFACE_H

/* Section : Includes */
#include "RTC_Config.h"
#include "../../MCAL_Layer/14_TWI/TWI_Interface.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct
{
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 date;
    uint8 month;
    uint8 year;
}RTC_t;

/* Section: Function Declarations */
Std_Return HRTC_Set_Time(uint8 sec, uint8 min, uint8 hour);
Std_Return HRTC_Set_Date(uint8 data, uint8 month, uint8 year);

Std_Return HRTC_Get_Time();
Std_Return HRTC_Get_Date();

#endif	/* RTC_INTERFACE_H */

