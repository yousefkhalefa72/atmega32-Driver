/* 
 * File:   EEPROM_Interface.h
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 6:26 PM
 */

#ifndef EEPROM_INTERFACE_H
#define	EEPROM_INTERFACE_H

/* Section : Includes */
#include "EEPROM_Config.h"
#include "../../MCAL_Layer/14_TWI/TWI_Interface.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */
Std_Return HEEPROM_Write_Byte(uint16 address_11bit,uint8 data);
Std_Return HEEPROM_Read_Byte(uint16 address_11bit,uint8 *data);

#endif	/* EEPROM_INTERFACE_H */

