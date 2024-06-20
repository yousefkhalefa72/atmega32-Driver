/* 
 * File:   WatchDog_Program.c
 * Author: Yousef.Khalefa
 * Created on June 8, 2024, 6:00 PM
 */

#include "WatchDog_Interface.h"


Std_Return MWDT_WatchDog_Turn_On(WDT_5v_time_t time)
{
    if (time > WDT_2s) 
    {
        return E_NOK;
    }
    else
    {
        WDTCR = (1 << WDE) | (time & 0x07); ;

        return E_OK;
    }    
}

Std_Return MWDT_WatchDog_Turn_Off()
{
    /* Write logical one to WDTOE and WDE */
    WDTCR |= (1<<WDTOE) | (1<<WDE);
    /* Turn off WDT */
    WDTCR = 0x00;

    return E_OK;
}