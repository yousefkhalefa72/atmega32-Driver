/* 
 * File:   EXTI_Program.C
 * Author: Yousef.Khalefa
 *
 * Created on March 10, 2024, 8:47 AM
 */

#include "EXTI_Interface.h"

Std_Return MEXTI_SenseControl(EXTI_NUM_t ExtiNumber,Sense_Control_t Control)
{
    Std_Return ret = E_OK;
	switch(ExtiNumber)
	{
        case EXT_INT0:
            switch(Control)
            {
                case LOW_LEVEL:
                    CLR_BIT(MCUCR,ISC01);CLR_BIT(MCUCR,ISC00);break;
                case ANY_LOGICAL_CHANGE:
                    CLR_BIT(MCUCR,ISC01);SET_BIT(MCUCR,ISC00);break;
                case FALLING_EDGE:
                    SET_BIT(MCUCR,ISC01);CLR_BIT(MCUCR,ISC00);break;
                case RISING_EDGE:
                    SET_BIT(MCUCR,ISC01);SET_BIT(MCUCR,ISC00);break;
            }break;
        case EXT_INT1:
            switch(Control)
            {
                case LOW_LEVEL:
                    CLR_BIT(MCUCR,ISC11);CLR_BIT(MCUCR,ISC10);break;
                case ANY_LOGICAL_CHANGE:
                    CLR_BIT(MCUCR,ISC11);SET_BIT(MCUCR,ISC10);break;
                case FALLING_EDGE:
                    SET_BIT(MCUCR,ISC11);CLR_BIT(MCUCR,ISC10);break;
                case RISING_EDGE:
                    SET_BIT(MCUCR,ISC11);SET_BIT(MCUCR,ISC10);break;
            }break;
        case EXT_INT2:
            switch(Control)
            {
                case LOW_LEVEL:case ANY_LOGICAL_CHANGE:
                    /* Sense_control_of_INT2_Error */
                    ret = E_NOK;
                    break;
                case FALLING_EDGE:
                    CLR_BIT(MCUCSR,ISC2);break;
                case RISING_EDGE:
                    SET_BIT(MCUCSR,ISC2);break;
            }break;
        default:
            ret = E_NOK;break;
	}
    return ret;
}

Std_Return MEXTI_Enable(EXTI_NUM_t ExtiNumber)
{
    Std_Return ret = E_OK;
	switch(ExtiNumber)
	{
        case EXT_INT0:SET_BIT(GICR,INT0);break;
        case EXT_INT1:SET_BIT(GICR,INT1);break;
        case EXT_INT2:SET_BIT(GICR,INT2);break;
        default:ret = E_NOK;break;
	}
    return ret;
}
Std_Return MEXTI_Disable(EXTI_NUM_t ExtiNumber)
{
    Std_Return ret = E_OK;
	switch(ExtiNumber)
	{
        case EXT_INT0:CLR_BIT(GICR,INT0);break;
        case EXT_INT1:CLR_BIT(GICR,INT1);break;
        case EXT_INT2:CLR_BIT(GICR,INT2);break;
        default:ret = E_NOK;break;
	}
    return ret;
}

