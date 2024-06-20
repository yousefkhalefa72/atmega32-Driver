/* 
 * File:   Timer2_Program.c
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 11:06 PM
 */

#include "Timer2_Interface.h"

#define MTimer2_OFF()                 (TCCR2 &= ~(0b00000111))

Std_Return MTimer2_Init(timer2_mode_t t2_mode,OC2_mode_t OC2_mode)
{
    Std_Return ret = E_OK;

    MTimer2_OFF(); // stop timer2

    switch(t2_mode)
    {
        case T2_NORMAL:
            CLR_BIT(TCCR2,WGM21);CLR_BIT(TCCR2,WGM20);
            switch(OC2_mode)
            {
                case OC2_DISCONNECTED:
                    CLR_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_NC_Toggle_on_compare:
                    CLR_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                case OC2_NC_Clear_on_compare:
                    SET_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_NC_Set_on_compare_match:
                    SET_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                default :ret = E_NOK;break;
            }break;
        case T2_PWM_PHASE_CORRECT:
            CLR_BIT(TCCR2,WGM21);SET_BIT(TCCR2,WGM20);
            switch(OC2_mode)
            {
                case OC2_DISCONNECTED:
                    CLR_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_PPC_Clear_on_up_compare_Set_at_down_compare:
                    SET_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_PPC_Clear_on_down_compare_Set_at_up_compare:
                    SET_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                default :ret = E_NOK;break;
            }break;
        case T2_CTC:
            SET_BIT(TCCR2,WGM21);CLR_BIT(TCCR2,WGM20);
            switch(OC2_mode)
            {
                case OC2_DISCONNECTED:
                    CLR_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_NC_Toggle_on_compare:
                    CLR_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                case OC2_NC_Clear_on_compare:
                    SET_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_NC_Set_on_compare_match:
                    SET_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                default :ret = E_NOK;break;
            }break;
        case T2_FAST_PWM:
            SET_BIT(TCCR2,WGM21);SET_BIT(TCCR2,WGM20);
            switch(OC2_mode)
            {
                case OC2_DISCONNECTED:
                    CLR_BIT(TCCR2,COM21);CLR_BIT(TCCR2,COM20);break;
                case OC2_FP_Clear_on_compare_Set_at_BOTTOM:
                    SET_BIT(TCCR2,COM21);CLR_BIT(TCCR0,COM20);break;
                case OC2_FP_Set_on_compare_Clear_at_BOTTOM:
                    SET_BIT(TCCR2,COM21);SET_BIT(TCCR2,COM20);break;
                default :ret = E_NOK;break;
            }break;
        default:ret = E_NOK;break;
    }
    #if TIMER2_OV_INTERRUPT==ENABLE
    MTimer2_OV_CLEAR_FLAG();
    SET_BIT(TIMSK,TOIE2); //Timer2 Overflow Interrupt Enable
    #endif
    #if TIMER2_OC_INTERRUPT==ENABLE
    MTimer2_OC_CLEAR_FLAG();
    SET_BIT(TIMSK,OCIE2); //Out_Compare_Match Interrupt Enable
    #endif
    return ret;
}

Std_Return MTimer2_DeInit()
{
    MTimer2_OFF(); // stop timer2
    #if TIMER2_OV_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,TOIE2); //Timer2 Overflow Interrupt Disable
    #endif
    #if TIMER2_OC_INTERRUPT==ENABLE
    CLR_BIT(TIMSK,OCIE2); //Out_Compare_Match Interrupt Disable
    #endif
    return E_OK;
}

Std_Return MTimer2_Star(timer2_prescaler_t prescaler)
{
	MTimer2_OFF(); //0b1111 1000 clear timer2 Prescaler
    TCCR2 |= prescaler; // set Prescaler of timer2

    return E_OK;
}

Std_Return MTimer2_Stop()
{
	MTimer2_OFF(); //timer2 Prescaler
    return E_OK;
}

Std_Return MTimer2_SetPreloadValue(timer2_preload_t PreLoadValue)
{
    TCNT2 = PreLoadValue;
    return E_OK;
}

Std_Return MTimer2_SetOCR2Value(timer2_preload_t PreLoadValue)
{
    OCR2 = PreLoadValue;
    return E_OK;
}

Std_Return MTimer2_Read_Counts(uint8* counts)
{  
    Std_Return ret = E_OK;
    if(counts == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        *counts = TCNT2;
    }
    return ret;;
}
