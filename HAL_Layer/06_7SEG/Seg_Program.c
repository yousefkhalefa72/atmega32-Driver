/* 
 * File:   Seg_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 9, 2024, 12:02 PM
 */

#include "Seg_Interface.h"

static const uint8 COMCA_7SEG[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};/*g f e d c b a*/

static const uint8 COMCA_7SEG_CHAR[26]={0x77,0x7C,0x39,0x5E,0x7B,0x71,0x6F,0x74,0x30,0x1E,SEGMENT_COMMON_CATHODE_OFF,
                                        0x38,SEGMENT_COMMON_CATHODE_OFF,0x37,0x5C,0x73,0x67,SEGMENT_COMMON_CATHODE_OFF,
                                        0x6D,0x78,0x3E,SEGMENT_COMMON_CATHODE_OFF,SEGMENT_COMMON_CATHODE_OFF,SEGMENT_COMMON_CATHODE_OFF,
                                        0x6E,0x5B};/*g f e d c b a*/

Std_Return HSeven_seg_Pins_intialize(segment_Pins_t *seg)
{
    Std_Return ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOK;
    }
    else
    {    
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            for(uint8 i=0; i<7; ++i)
            {
                seg->pins[i].logic = ((SEGMENT_COMMON_ANODE_OFF >> i) & BIT_MASK);
                seg->pins[i].direction = DIO_DIRECTION_OUTPUT;
                ret = MDIO_SetPinDirection(&(seg->pins[i]));
            }
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            for(uint8 i=0; i<7; ++i)
            {
                seg->pins[i].logic = ((SEGMENT_COMMON_CATHODE_OFF >> i) & BIT_MASK);
                seg->pins[i].direction = DIO_DIRECTION_OUTPUT;
                ret = MDIO_SetPinDirection(&(seg->pins[i]));
            }
        }
    }
    return ret;
}

Std_Return HSeven_seg_Port_intialize(segment_Port_t *seg)
{
    Std_Return ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOK;
    }
    else
    {    
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            ret = MDIO_SetPortValue(seg->port, SEGMENT_COMMON_ANODE_OFF);
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            MDIO_SetPortValue(seg->port,SEGMENT_COMMON_CATHODE_OFF);
        }
        ret |= MDIO_SetPortDirection(seg->port,PORT_DIRECTION_OUTPUT);
    }
    return ret;
}

Std_Return HSeven_seg_BCD_intialize(BCD_segment_t *seg)
{
    Std_Return ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOK;
    }
    else
    {    
        for(int i=0; i<4; ++i)
        {
            seg->pins[i].direction = DIO_DIRECTION_OUTPUT;
            seg->pins[i].logic = ((SEGMENT_BCD_OFF >> i) & BIT_MASK);
            ret = MDIO_SetPinDirection(&(seg->pins[i]));
        }
    }
    return ret;
}

Std_Return HSeven_seg_Pins_write_number(segment_Pins_t *seg, uint8 number)
{
    Std_Return ret = E_OK;
    uint8 i=0;
    
    if((NULL == seg) || (number > 9))
    {
        ret = E_NOK;
    }
    else
    {    
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            for(i=0; i<7; ++i)
            {
                ret = MDIO_SetPinValue(&(seg->pins[i]),(~(COMCA_7SEG[number]) >> i) & BIT_MASK);
            }
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            for(i=0; i<7; ++i)
            {
                ret = MDIO_SetPinValue(&(seg->pins[i]),(COMCA_7SEG[number] >> i) & BIT_MASK);
            }
        }
    }
    return ret;
}

Std_Return HSeven_seg_Port_write_number(segment_Port_t *seg, uint8 number)
{   
    Std_Return ret = E_OK;
    if((NULL == seg) || (number > 9))
    {
        ret = E_NOK;
    }
    else
    {
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            ret = MDIO_SetPortValue(seg->port, ~COMCA_7SEG[number]);
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            ret = MDIO_SetPortValue(seg->port,COMCA_7SEG[number]);
        }
    }
    return ret;
}

Std_Return HSeven_seg_BCD_write_number(BCD_segment_t *seg, uint8 number)
{
    Std_Return ret = E_OK;
    if((NULL == seg) || (number > 9))
    {
        ret = E_NOK;
    }
    else
    {    
        for(uint8 i=0; i<4; ++i)
        {
            ret = MDIO_SetPinValue(&(seg->pins[i]),(number >> i) & BIT_MASK);
        }
    }
    return ret;
}

Std_Return HSeven_seg_Pins_write_char(segment_Pins_t *seg, uint8 _char)
{
    Std_Return ret = E_OK;
    uint8 i=0;
    _char -= 'a';
    
    if((NULL == seg) || (_char > 26))
    {
        ret = E_NOK;
    }
    else
    {    
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            for(i=0; i<7; ++i)
            {
                ret = MDIO_SetPinValue(&(seg->pins[i]),(~(COMCA_7SEG_CHAR[_char]) >> i) & BIT_MASK);
            }
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            for(i=0; i<7; ++i)
            {
                ret = MDIO_SetPinValue(&(seg->pins[i]),(COMCA_7SEG_CHAR[_char] >> i) & BIT_MASK);
            }
        }
    }
    return ret;
}

Std_Return HSeven_seg_Port_write_char(segment_Port_t *seg, uint8 _char)
{
    Std_Return ret = E_OK;
    _char -= 'a';
    if((NULL == seg) || (_char > 26))
    {
        ret = E_NOK;
    }
    else
    {
        if(seg->type == SEGMENT_COMMON_ANODE)
        {
            ret = MDIO_SetPortValue(seg->port, ~COMCA_7SEG_CHAR[_char]);
        }
        else if(seg->type == SEGMENT_COMMON_CATHODE)
        {
            ret = MDIO_SetPortValue(seg->port,COMCA_7SEG_CHAR[_char]);
        }
    }
    return ret;
}