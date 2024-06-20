#if 0 

 /* prescaller = you frecuancy / 50k : your frecuancy / 200k
               = 8 000 0000    / 50k : 8 000 000      / 200k 
               = 40 : 160 
    for sampling up to 15khz */

#include "ADC_Interface.h"

ADC_Result_t adc_result;
float32 adc0_volt;

MADC_Init(ADC_DIVF_64,right_adjust,AREF);
MADC_Conversion(ADC0,&adc_result);

MADC_ReadVolt(ADC0,&adc0_volt,5.0);

/* interuppt ISR used in driver don't use it in main*/
ISR(ADC_vect){} 
#endif
