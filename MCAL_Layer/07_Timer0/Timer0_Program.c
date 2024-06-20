/* 
 * File:   Timer0_Program.c
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 10:42 AM
 */

#include "Timer0_Interface.h"

#define MTimer0_OFF()                 (TCCR0 &= ~(0b00000111))

Std_Return MTimer0_Init(timer0_mode_t t0_mode,OC0_mode_t OC0_mode)
{
    Std_Return ret = E_OK;

    MTimer0_OFF(); // stop timer0
    switch(t0_mode)
    {
        case T0_NORMAL:
            CLR_BIT(TCCR0,WGM01);CLR_BIT(TCCR0,WGM00);
            switch(OC0_mode)
            {
                case OC0_DISCONNECTED:
                    CLR_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_NC_Toggle_on_compare:
                    CLR_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                case OC0_NC_Clear_on_compare:
                    SET_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_NC_Set_on_compare_match:
                    SET_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                default :ret = E_NOK;break;
            }break;
        case T0_PWM_PHASE_CORRECT:
            CLR_BIT(TCCR0,WGM01);SET_BIT(TCCR0,WGM00);
            switch(OC0_mode)
            {
                case OC0_DISCONNECTED:
                    CLR_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_PPC_Clear_on_up_compare_Set_at_down_compare:
                    SET_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_PPC_Clear_on_down_compare_Set_at_up_compare:
                    SET_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                default :ret = E_NOK;break;
            }break;
        case T0_CTC:
            SET_BIT(TCCR0,WGM01);CLR_BIT(TCCR0,WGM00);
            switch(OC0_mode)
            {
                case OC0_DISCONNECTED:
                    CLR_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_NC_Toggle_on_compare:
                    CLR_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                case OC0_NC_Clear_on_compare:
                    SET_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_NC_Set_on_compare_match:
                    SET_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                default :ret = E_NOK;break;
            }break;
        case T0_FAST_PWM:
            SET_BIT(TCCR0,WGM01);SET_BIT(TCCR0,WGM00);
            switch(OC0_mode)
            {
                case OC0_DISCONNECTED:
                    CLR_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_FP_Clear_on_compare_Set_at_BOTTOM:
                    SET_BIT(TCCR0,COM01);CLR_BIT(TCCR0,COM00);break;
                case OC0_FP_Set_on_compare_Clear_at_BOTTOM:
                    SET_BIT(TCCR0,COM01);SET_BIT(TCCR0,COM00);break;
                default :ret = E_NOK;break;
            }break;
        default:ret = E_NOK;break;
    }
    #if TIMER0_OV_INTERRUPT==ENABLE
    MTimer0_OV_CLEAR_FLAG();
    SET_BIT(TIMSK,TOIE0); //Timer0 Overflow Interrupt Enable
    #endif
    #if TIMER0_OC_INTERRUPT==ENABLE
    MTimer0_OC_CLEAR_FLAG();
    SET_BIT(TIMSK,OCIE0); //Out_Compare_Match Interrupt Enable
    #endif
    return ret;
}

Std_Return MTimer0_DeInit()
{
    MTimer0_OFF(); // stop timer0
    #if TIMER0_OV_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,TOIE0); //Timer0 Overflow Interrupt Disable
    #endif
    #if TIMER0_OC_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,OCIE0); //Out_Compare_Match Interrupt Disable
    #endif
    return E_OK;
}

Std_Return MTimer0_Star(timer0_prescaler_t prescaler)
{
	MTimer0_OFF(); //0b1111 1000 clear timer0 Prescaler
    TCCR0 |= prescaler; // set Prescaler of timer0

    return E_OK;
}

Std_Return MTimer0_Stop()
{
	MTimer0_OFF(); //timer0 Prescaler
    return E_OK;
}

Std_Return MTimer0_SetPreloadValue(timer0_preload_t PreLoadValue)
{
    TCNT0 = PreLoadValue;
    return E_OK;
}

Std_Return MTimer0_SetOCR0Value(timer0_preload_t PreLoadValue)
{
    OCR0 = PreLoadValue;
    return E_OK;
}

Std_Return MTimer0_Read_Counts(uint8* counts)
{  
    Std_Return ret = E_OK;
    if(counts == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        *counts = TCNT0;
    }
    return ret;
}
