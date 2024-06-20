/* 
 * File:   Timer1_Program.C
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 11:06 PM
 */

#include "Timer1_Interface.h"


#define MTimer1_OFF()                 (TCCR1B &= ~(0b00000111))

Std_Return MTimer1_Init(timer1_mode_t t1_mode, OC1A_mode_t OC1A_mode, OC1B_mode_t OC1B_mode)
{
    MTimer1_OFF(); // stop timer1
            
    /* clear timer1 mode*/
    TCCR1A &= ~(0b11110011);
    TCCR1B &= ~(0b00011000); 
    
    /* select timer mode */
    TCCR1A |= t1_mode & 0x03;
    TCCR1B |= (t1_mode << 1) & 0x18; 
    
    /* select OC1 mode */
    TCCR1A |= OC1A_mode << 6 ;
    TCCR1A |= OC1B_mode << 4 ;
            
    
    #if TIMER1_OV_INTERRUPT==ENABLE
    MTimer1_OV_CLEAR_FLAG();
    SET_BIT(TIMSK,TOIE1); //Timer0 Overflow Interrupt Enable
    #endif
    #if TIMER1_OCA_INTERRUPT==ENABLE
    MTimer1_OCA_CLEAR_FLAG();
    SET_BIT(TIMSK,OCIE1A); //Out_Compare_Match Interrupt Enable
    #endif
    #if TIMER1_OCB_INTERRUPT==ENABLE
    MTimer1_OCB_CLEAR_FLAG();
    SET_BIT(TIMSK,OCIE1B); //Out_Compare_Match Interrupt Enable
    #endif
    #if TIMER1_IC_INTERRUPT==ENABLE
    MTimer1_IC_CLEAR_FLAG();
    SET_BIT(TIMSK,TICIE1); //Out_Compare_Match Interrupt Enable
    #endif

    return E_OK;
}

Std_Return MTimer1_DeInit()
{
    MTimer1_OFF(); // stop timer1
    #if TIMER1_OV_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,TOIE1); //Timer1 Overflow Interrupt Disable
    #endif
    #if TIMER1_OCA_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,OCIE1A); //Out_Compare_Match Interrupt Disable
    #endif
    #if TIMER1_OCB_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,OCIE1B); //Out_Compare_Match Interrupt Disable
    #endif
    #if TIMER1_IC_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,TICIE1); //Input capture Interrupt Disable
    #endif
    return E_OK;
}
Std_Return MTimer1_Star(timer1_prescaler_t prescaler)
{
	MTimer1_OFF(); //0b1111 1000 clear timer1 Prescaler
    TCCR1B |= prescaler; // set Prescaler of timer1

    return E_OK;
}

Std_Return MTimer1_Stop()
{
	MTimer1_OFF(); //timer1 Prescaler
    return E_OK;
}

Std_Return MTimer1_SetPreloadValue(timer1_preload_t PreLoadValue)
{
    TCNT1 = PreLoadValue;
    return E_OK;
}

Std_Return MTimer1_SetOCR1AValue(timer1_preload_t PreLoadValue)
{
    OCR1A = PreLoadValue;
    return E_OK;
}

Std_Return MTimer1_SetOCR1BValue(timer1_preload_t PreLoadValue)
{
    OCR1B = PreLoadValue;
    return E_OK; 
}

Std_Return MTimer1_Read_Counts(uint16* counts)
{
    Std_Return ret = E_OK;
    if(counts == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        *counts = TCNT1;
    }
    return ret;;
}