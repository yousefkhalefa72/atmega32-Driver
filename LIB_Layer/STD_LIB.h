/* 
 * File:   STD_LIB.h
 * Author: Yousef.Khalefa
 *
 * Created on March 8, 2024, 7:19 PM
 */

#ifndef STD_LIB_H
#define	STD_LIB_H

/* Section : Includes */
#include "STD_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Section: Macro Declarations */
#define BIT_MASK       (uint8)0x01
#define PORT_MASK      (uint8)0xFF

/* Section: Macro Functions Declarations */
#define SET_BIT(REG, BIT_POSN)     (REG |= (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG, BIT_POSN)     (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)  (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)

#define HBYTE(u16_REG)             (uint8)(u16_REG >> 8)

/* Section: Data Type Declarations */

/* Section: Function Declarations */
Std_Return LIB_uint8_to_string(uint8 source, uint8* dist);
Std_Return LIB_uint16_to_string(uint16 source, uint8* dist);
Std_Return LIB_uint32_to_string(uint32 source, uint8* dist);

Std_Return LIB_uint16_to_float_5v(uint16 source, float32* dist);
Std_Return LIB_uint16_to_float_2_56v(uint16 source, float32* dist);
#endif	/* STD_LIB_H */

