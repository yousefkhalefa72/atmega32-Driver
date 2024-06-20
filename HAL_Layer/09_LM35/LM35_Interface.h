/* 
 * File:   LM35_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#ifndef LM35_INTERFACE_H
#define	LM35_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "LM35_Config.h"
#include "../../MCAL_Layer/06_ADC/ADC_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HLM35_Init(ADC_RefVolt_t reference_volt);
Std_Return HLM35_DeInit();
Std_Return HLM35_Read(ADC_Channel_t channel, float32 *result);

#endif	/* LM35_INTERFACE_H */

