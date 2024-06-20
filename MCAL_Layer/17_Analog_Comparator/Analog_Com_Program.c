/* 
 * File:   Analog_Com_Program
 * Author: Yousef_Khalefa
 * Created on June 20, 2024, 10:53 AM
 */

#include "Analog_Com_Interface.h"

Std_Return MAnalogComparator_Init(ANACOMP_neg_Input_t input_pin, ANACOMP_ICU_Trigger_t ICU_Status)
{
    Std_Return ret = E_OK;
    
#if ANALOG_COMP_INTERRUPT==ENABLE
    MANA_COMP_INTERRUPT_DISABLE();
    MANA_COMP_CLEAR_INT_FLAG();
#endif

    if(input_pin > NEG_IN_AIN1)
    {
        input_pin = NEG_IN_AIN1;
        ret = E_NOK;
    }
    
    if(input_pin == NEG_IN_AIN1)
        CLR_BIT(SFIOR,ACME);
    else
    {
        SET_BIT(SFIOR,ACME);
        ADMUX &= 0xE0;         // Clear Channel
        ADMUX |= input_pin;      // Select Channel
    }

    if(ICU_Status == OUT_TRIGGER_ICU)
        SET_BIT(ACSR,ACIC);
    else
        CLR_BIT(ACSR,ACIC);

#if ANALOG_COMP_INTERRUPT==ENABLE
    MANA_COMP_INTERRUPT_ENABLE();
#endif
    return ret;
}

Std_Return MAnalogComparator_SetInterruptMode(ANA_COMP_INTMode_t mode) 
{
    Std_Return ret = E_NOK;
    if((mode > 3) || (mode == 1))
    {
        ret = E_NOK;
    }
    else
    {
        switch(mode)
        {
            case INT_ON_TOGGLE:
                CLR_BIT(ACSR,ACIS1);
                CLR_BIT(ACSR,ACIS0);break;
                        
            case INT_ON_RISING_EDGE:
                SET_BIT(ACSR,ACIS1);
                SET_BIT(ACSR,ACIS0);break;
                        
            case INT_ON_FALLING_EDGE:
                SET_BIT(ACSR,ACIS1);
                CLR_BIT(ACSR,ACIS0);break;
                        
            default : ret = E_NOK; break;
        }
    }
    return ret;
}