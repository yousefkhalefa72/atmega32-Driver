/* 
 * File:   ADC_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 9:34 AM
 */

#ifndef ADC_INTERFACE_H
#define	ADC_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "ADC_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../01_DIO/DIO_Interface.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define ADC_InterruptEnable()           (SET_BIT(ADCSRA,ADIE))
#define ADC_InterruptDisable()          (CLR_BIT(ADCSRA,ADIE))
#define ADC_InterruptFlagClear()        (SET_BIT(ADCSRA,ADIF))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    ADC0 = 0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,
}ADC_Channel_t;

typedef enum
{
    AREF = 0,
    AVCC,
    Internal_2_56V = 3,
}ADC_RefVolt_t;

typedef enum
{
    ADC_DIVF_2 = 0,
    ADC_DIVF_4 = 2,
    ADC_DIVF_8,
    ADC_DIVF_16,
    ADC_DIVF_32,
    ADC_DIVF_64,
    ADC_DIVF_128
}ADC_Prescaler_t;

typedef enum
{
    right_adjust = 0,
    left_adjust
}ADC_Adjust_t;

typedef uint16 ADC_Result_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MADC_Init(ADC_Prescaler_t Prescaler,ADC_Adjust_t format, ADC_RefVolt_t reference_volt);
Std_Return MADC_DeInit();
Std_Return MADC_Conversion(ADC_Channel_t channel, ADC_Result_t *conversion_result);
Std_Return MADC_ReadVolt(ADC_Channel_t channel, float32* volt, float32 vref);

#endif	/* ADC_INTERFACE_H */

