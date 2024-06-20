/* 
 * File:   ADC_Program.c
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 9:34 AM
 */

#include "ADC_Interface.h"

static ADC_Adjust_t  G_ADC_format = right_adjust;

#if ADC_INTERRUPT==ENABLE
ADC_Result_t *result;
#endif

Std_Return MADC_Init(ADC_Prescaler_t Prescaler,ADC_Adjust_t format, ADC_RefVolt_t reference_volt)
{
    CLR_BIT(ADCSRA,ADEN); // Disable the ADC

    ADCSRA &= 0xF8;            // Clear clock 0b1111 1000
    ADCSRA |= Prescaler;      // Select clock 0b1111 1xxx

    ADC_InterruptFlagClear();
    #if ADC_INTERRUPT==ENABLE
    ADC_InterruptEnable();
    #endif
    
    if(left_adjust == format) // Select Result Format
        {G_ADC_format = left_adjust; SET_BIT(ADMUX,ADLAR);}
    else
        {G_ADC_format = right_adjust; CLR_BIT(ADMUX,ADLAR);}

    switch(reference_volt) // Select reference volt
    {
        case AREF:
            CLR_BIT(ADMUX,REFS0);CLR_BIT(ADMUX,REFS1);
            break;
        case AVCC:
            SET_BIT(ADMUX,REFS0);CLR_BIT(ADMUX,REFS1);
            break;
        case Internal_2_56V:
            SET_BIT(ADMUX,REFS0);SET_BIT(ADMUX,REFS1);
            break;
        default: 
            /* ERROR */ 
            break;   
    }
    return E_OK;
}

Std_Return MADC_DeInit()
{
    CLR_BIT(ADCSRA,ADEN);   // Disable the ADC 
    ADC_InterruptDisable(); // Disable ADC interrupt
    return E_OK;
}


Std_Return MADC_Conversion(ADC_Channel_t channel, ADC_Result_t *conversion_result)
{
    Std_Return ret = E_OK;
    if(NULL == conversion_result)
    {
        ret = E_NOK;
    }
    else
    {
        SET_BIT(ADCSRA,ADEN); // Enable the ADC 
        
        ADMUX &= 0xE0;         // Clear Channel
        ADMUX |= channel;      // Select Channel
        
        pin_t ADC_pin ={.port=PORTA_INDEX, .pin=channel, .direction=DIO_DIRECTION_INPUT};
        MDIO_SetPinDirection(&ADC_pin);
        
        ADC_InterruptFlagClear();     // clear flag
        
        SET_BIT(ADCSRA,ADSC);         // Start Conversion
        
#if  ADC_INTERRUPT==ENABLE
        result = conversion_result;
#else
        while(READ_BIT(ADCSRA,ADSC)); // while conversion
        
        if(right_adjust == G_ADC_format)
        {
            *conversion_result = (ADC_Result_t)(ADCL|(ADCH << 8));
        }
        else if(left_adjust == G_ADC_format)
        {
            *conversion_result = (ADC_Result_t)((ADCL>>6)|(ADCH << 2));
        }
        CLR_BIT(ADCSRA,ADEN); // disable the ADC 
#endif
    }
    return ret;
}

Std_Return MADC_ReadVolt(ADC_Channel_t channel, float32* volt, float32 vref)
{
    Std_Return ret = E_OK;
    ADC_Result_t ADC_Result_to_volt;
    ret = MADC_Conversion(channel,&ADC_Result_to_volt);
    if(ret == E_NOK)
    {
        return E_NOK;
    }
    else
    { 
        *volt = ((float32)vref/1023)*ADC_Result_to_volt;
    }
    return E_OK;
}


ISR(ADC_vect)
{
#if  ADC_INTERRUPT==ENABLE
    if(right_adjust == G_ADC_format)
    {
        *result = (ADC_Result_t)(ADCL|(ADCH << 8));
    }
    else if(left_adjust == G_ADC_format)
    {
        *result = (ADC_Result_t)((ADCL>>6)|(ADCH << 2));
    }
    CLR_BIT(ADCSRA,ADEN); // disable the ADC
#endif
}