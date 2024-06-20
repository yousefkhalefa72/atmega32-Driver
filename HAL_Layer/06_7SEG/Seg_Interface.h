/* 
 * File:   Seg_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 12:02 PM
 */

#ifndef SEG_INTERFACE_H
#define	SEG_INTERFACE_H

/* Section : Includes */
#include "Seg_Config.h"
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"


/* Section: Macro Declarations */
#define SEGMENT_COMMON_ANODE_OFF    0xff
#define SEGMENT_COMMON_CATHODE_OFF  0x00
#define SEGMENT_BCD_OFF             0x0f

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct
{
    pin_t pins[7];
    segment_type_t  type;
}segment_Pins_t;

typedef struct
{
    port_index_t    port  : 2;
    segment_type_t  type;
}segment_Port_t;

typedef struct
{
    pin_t pins[4];
}BCD_segment_t;

/* Section: Function Declarations */
Std_Return HSeven_seg_Pins_intialize(segment_Pins_t *seg);
Std_Return HSeven_seg_Port_intialize(segment_Port_t *seg);
Std_Return HSeven_seg_BCD_intialize(BCD_segment_t *seg);

Std_Return HSeven_seg_Pins_write_number(segment_Pins_t *seg, uint8 number);
Std_Return HSeven_seg_Port_write_number(segment_Port_t *seg, uint8 number);
Std_Return HSeven_seg_BCD_write_number(BCD_segment_t *seg, uint8 number);

Std_Return HSeven_seg_Pins_write_char(segment_Pins_t *seg, uint8 _char);
Std_Return HSeven_seg_Port_write_char(segment_Port_t *seg, uint8 _char);

#endif	/* SEG_INTERFACE_H */

