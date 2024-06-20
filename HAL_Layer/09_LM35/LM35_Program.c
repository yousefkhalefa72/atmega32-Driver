/* 
 * File:   LM35_Interface.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 12, 2024, 11:58 AM
 */

#include "LM35_Interface.h"

Std_Return HLM35_Init(ADC_RefVolt_t reference_volt)
{
    return MADC_Init(ADC_DIVF_128,right_adjust,reference_volt);
}
Std_Return HLM35_DeInit()
{
    MADC_DeInit();
    return E_OK;
}

Std_Return HLM35_Read(ADC_Channel_t channel, float32 *result)
{
    ADC_Result_t conversion_result;
    uint16 u16Temp_m;
    
    MADC_Conversion(channel, &conversion_result);
    
    u16Temp_m=(float32)(((uint32)conversion_result * 5000UL) / 1024UL);
    /* 5000(mv) / 1024(10-Bit) => 4.88 */
    
    u16Temp_m /= 10; // The sensitivity of LM35 is 10 mV/degree
    
    *result = (float32)(u16Temp_m ); //temp in degree
    return E_OK;
}

        
