/* 
 * File:   EEPROM_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 9:26 AM
 */

#ifndef EEPROM_INTERFACE_H
#define	EEPROM_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "EEPROM_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../00_Device_Config/Device_Config.h"
#include "../02_GIE/GIE_Interface.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MEEPROM_WriteByte(uint16 Address_10bit, uint8 Data);
Std_Return MEEPROM_WriteString(uint16 Address_10bit, uint8* Data);
Std_Return MEEPROM_ReadByte(uint16 Address_10bit, uint8 *Data);
Std_Return MEEPROM_ReadString(uint16 Address_10bit, uint8 *Data, uint8 size);

#endif	/* EEPROM_INTERFACE_H */

