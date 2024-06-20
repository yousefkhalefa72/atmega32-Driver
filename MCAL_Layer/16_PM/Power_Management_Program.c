/* 
 * File:   Power_Management_Program.c
 * Author: Yousef.Khalefa
 * Created on June 8, 2024, 6:00 PM
 */

#include "Power_Management_Interface.h"

Std_Return MPM_Enable(sleep_mode_t mode) 
{
    // Enable sleep mode
    MCUCR |= (1 << SE) | (mode << SM0);
    return E_OK;
}

Std_Return MPM_Disable()
{
    MCUCR &= 0x0f;
    return E_NOK;
}

void MPM_EnterSleep(void)
{
    asm volatile ("sleep");
}