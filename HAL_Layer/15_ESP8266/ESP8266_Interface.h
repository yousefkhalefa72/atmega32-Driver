/* 
 * File:   ESP8266_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 20, 2024, 12:22 PM
 */

#ifndef ESP8266_INTERFACE_H
#define	ESP8266_INTERFACE_H

/* Section : Includes */
#include "ESP8266_Config.h"
#include "../../MCAL_Layer/12_UART/UART_Interface.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */
Std_Return HESP8266_Init();
Std_Return HESP8266_SendCommand(uint8* command);
Std_Return HESP8266_ReadResponse(uint8* data);

#endif	/* ESP8266_INTERFACE_H */

