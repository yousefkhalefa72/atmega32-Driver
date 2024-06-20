/* 
 * File:   STD_Types.h
 * Author: Yousef.Khalefa
 *
 * Created on March 8, 2024, 7:19 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/* Section : Includes */
#include "../MCAL_Layer/00_Device_Config/Compiler.h"

/* Section: Data Type Declarations */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;

typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;

typedef float               float32;
typedef double              float64;

typedef unsigned char       Std_Return;

/* Section: Macro Declarations */
#define ENABLE              0x01
#define DISABLE             0x00

#define STD_HIGH            0x01
#define STD_LOW             0x00

#define STD_ON              0x01
#define STD_OFF             0x00

#define STD_ACTIVE          0x01
#define STD_IDLE            0x00

#define E_OK                (Std_Return)0x01
#define E_NOK               (Std_Return)0x00

#define ZERO                0

/* Section: Macro Functions Declarations */

/* Section: Function Declarations */

#endif	/* STD_TYPES_H */

