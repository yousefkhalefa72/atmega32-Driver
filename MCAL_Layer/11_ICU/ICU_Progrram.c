/* 
 * File:   ICU_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#include "ICU_Interface.h"

#define ICU_RISING_EDGE()       (SET_BIT(TCCR1B,ICES1))
#define ICU_FALLING_EDGE()      (CLR_BIT(TCCR1B,ICES1))

Std_Return MICU_EXTI0_T1_Read(uint32* Freq, uint8* Duty)
{    
    if((Freq == NULL) || (Duty == NULL))
    {
        return E_NOK;
    }
    else
    {
        uint8 GIE_Status = MGIE_Get_Status();
        MGIE_Disable();
        
        uint16 Ton = 0, Toff = 0;

        MTimer1_Stop();
        MEXTI_Disable(EXT_INT0);

        MTimer1_Init(T1_NORMAL,OC1A_DISCONNECTED,OC1B_DISCONNECTED);
        MTimer1_SetPreloadValue(0);
                                                    //  ------------
        MEXTI_SenseControl(EXT_INT0,RISING_EDGE);   //  ^

        MTimer1_Star(T1_NO_PRESCALER);

        MEXTI_Enable(EXT_INT0);

        while(MEXTI_INT0_Read_Flag()==0);
        MEXTI_INT0_Clear_Flag();

        MTimer1_SetPreloadValue(0);                     // 
        MEXTI_SenseControl(EXT_INT0,FALLING_EDGE);      //

        while(MEXTI_INT0_Read_Flag()==0);
        MEXTI_INT0_Clear_Flag();

        MTimer1_Read_Counts(&Ton);
        MTimer1_SetPreloadValue(0);
        MEXTI_SenseControl(EXT_INT0,RISING_EDGE);

        while(MEXTI_INT0_Read_Flag()==0);
        MEXTI_INT0_Clear_Flag();

        MTimer1_Read_Counts(&Toff);
        MEXTI_Disable(EXT_INT0);
        
        if(GIE_Status == 1)MGIE_Enable();
        
        #warning "be careful when using this func you must be sure there is an signal on INT0 or it will polling the code"
        if(Ton > 0 && Toff > 0)
        {
            *Duty = (Ton*100) / (Ton + Toff);
            *Freq = ((uint32)F_CPU)/(Ton+Toff);
            return E_OK;
        }
        else
        {
            return E_NOK;
        }
    }
}

Std_Return MICU_T1_Read(uint32* Freq, uint8* Duty)
{
    if((Freq == NULL) || (Duty == NULL))
    {
        return E_NOK;
    }
    uint8 GIE_Status = MGIE_Get_Status();
    MGIE_Disable();

	uint32 T1,T2,T3,high,period;
		
    MTimer1_Init(T1_NORMAL,OC1A_DISCONNECTED,OC1B_DISCONNECTED);
    MTimer1_SetPreloadValue(0);

    /* Clear ICF (Input Capture flag) flag */
    MTimer1_IC_CLEAR_FLAG();

    ICU_RISING_EDGE(); /* Rising edge */
    MTimer1_Star(T1_NO_PRESCALER); /* no prescaler */

    while( MTimer1_IC_READ_FLAG() == 0 );
    T1 = ICR1;  		/* Take value of capture register */
    MTimer1_IC_CLEAR_FLAG();  	/* Clear ICF flag */

    ICU_FALLING_EDGE(); /* Falling edge */

    while( MTimer1_IC_READ_FLAG() == 0 );
    T2 = ICR1;  		/* Take value of capture register */
    MTimer1_IC_CLEAR_FLAG();  	/* Clear ICF flag */

    ICU_RISING_EDGE();
    while ((TIFR&(1<<ICF1)) == 0);
    T3 = ICR1;  		/* Take value of capture register */
    MTimer1_IC_CLEAR_FLAG();  	/* Clear ICF flag */

    MTimer1_Stop();     /* Stop the timer */
    
    if(GIE_Status == 1)MGIE_Enable();
    
    if(T1<T2 && T2<T3)
    {
        high=T2-T1;
        period=T3-T1;

        *Freq = F_CPU/period; 

        *Duty =((float) high /(float)period)*100;
        return E_OK;
	}
    return E_NOK;
}
