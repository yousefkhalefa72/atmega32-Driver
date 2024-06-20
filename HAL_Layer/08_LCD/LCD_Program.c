/* 
 * File:   LCD_Program.c
 * Author: Yousef_Khalefa
 * 
 * Created on March 9, 2024, 2:56 PM
 */

#include "LCD_Interface.h"

static Std_Return HLCD_send_4bits(lcd_t *lcd, uint8 _data_command);
static Std_Return HLCD_send_enable_signal(lcd_t *lcd);

Std_Return HLCD_intialize(lcd_t *lcd)
{
    Std_Return ret = E_OK;
    uint8 counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {    
        lcd->lcd_rs.direction = DIO_DIRECTION_OUTPUT;
        lcd->lcd_en.direction = DIO_DIRECTION_OUTPUT;
        ret = MDIO_SetPinDirection(&(lcd->lcd_rs));
        ret |= MDIO_SetPinDirection(&(lcd->lcd_en));
        MCAL_Delay_ms(40);
        
        switch(lcd->type)
        {
            case LCD_4Bits:
                for(counter=0; counter<4; counter++)
                {
                    lcd->lcd_data[counter].direction = DIO_DIRECTION_OUTPUT;
                    ret |= MDIO_SetPinDirection(&(lcd->lcd_data[counter]));
                }
                /* 7  6  5      4         3          2        1 0   
                 * 0  0  1 DL=0:4_bit N=0:1_line F=0:5*7 dots x x
                 * 0  0  1 DL=1:8_bit N=1:2_line F=1:5*10dots x x  */
                
                ret |= HLCD_send_command(lcd, 0b00100010);
                ret |= HLCD_send_4bits(lcd, 0b11111111);
                ret |= HLCD_send_enable_signal(lcd);
                break;
            case LCD_8Bits:
                for(counter=0; counter<8; counter++)
                {
                    lcd->lcd_data[counter].direction = DIO_DIRECTION_OUTPUT;
                    ret |= MDIO_SetPinDirection(&(lcd->lcd_data[counter]));
                }
                /* 7  6  5      4         3          2        1 0   
                 * 0  0  1 DL=0:4_bit N=0:1_line F=0:5*7 dots x x
                 * 0  0  1 DL=1:8_bit N=1:2_line F=1:5*10dots x x  */
                ret |= HLCD_send_command(lcd, 0b00111000);
                break;
        } 
        MCAL_Delay_ms(1);
        /* 7  6  5  4  3          2        1           0   
         * 0  0  0  0  1 D=0:display_of C=0:Cursor_of B=0:Blink_of
         * 0  0  0  0  1 D=1:display_on C=1:Cursor_on B=1:Blink_on  */
        ret |= HLCD_send_command(lcd, 0b00001100 |(Cursor_CONFIG << 1)|(Blink_CONFIG) );
        MCAL_Delay_ms(1);
        /* clear display */
        ret |= HLCD_send_command(lcd, 0b00000001);
        MCAL_Delay_ms(2);
        /* 7  6  5  4  3 2        1           0   
         * 0  0  0  0  0 1 0:decrement 0:not shift
         * 0  0  0  0  0 1 1:increment 1:shift  */
        ret |= HLCD_send_command(lcd, 0b00000110);
    }
    return ret;
}

Std_Return HLCD_send_command(lcd_t *lcd, uint8 command)
{
    Std_Return ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
        ret = MDIO_SetPinValue(&(lcd->lcd_rs), DIO_LOW);
        switch(lcd->type)
        {
            case LCD_4Bits:
                /* Send the Command through the (4-Pins" Data lines */
                ret |= HLCD_send_4bits(lcd, command >> 4);
                /* Send the Enable Signal on the "E" Pin */
                ret |= HLCD_send_enable_signal(lcd);
                /* Send the Command through the (4-Pins" Data lines */
                ret |= HLCD_send_4bits(lcd, command);
                break;
            case LCD_8Bits:
                /* Send the Command through the (8-Pins" Data lines */
                for(uint8 l_pin_counter=0; l_pin_counter<8; ++l_pin_counter)
                {
                    ret |= MDIO_SetPinValue(&(lcd->lcd_data[l_pin_counter]), (command >> l_pin_counter)&BIT_MASK);
                }
                break;
        }  
        /* Send the Enable Signal on the "E" Pin */
        ret |= HLCD_send_enable_signal(lcd);
    }
    return ret;
}

Std_Return HLCD_send_char(lcd_t *lcd, uint8 data)
{
    Std_Return ret = E_OK;
    uint8 l_pin_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
        ret = MDIO_SetPinValue(&(lcd->lcd_rs), DIO_HIGH);
        switch(lcd->type)
        {
            case LCD_4Bits:
                /* Send the Data through the (4-Pins" Data lines */
                ret |= HLCD_send_4bits(lcd, data >> 4);
                /* Send the Enable Signal on the "E" Pin */
                ret |= HLCD_send_enable_signal(lcd);
                /* Send the Data through the (4-Pins" Data lines */
                ret |= HLCD_send_4bits(lcd, data);
                break;
            case LCD_8Bits:
                /* Send the Data through the (8-Pins" Data lines */
                for(l_pin_counter=0; l_pin_counter<8; ++l_pin_counter)
                {
                    ret |= MDIO_SetPinValue(&(lcd->lcd_data[l_pin_counter]), (data >> l_pin_counter)&BIT_MASK);
                }
                break;
        }
        /* Send the Enable Signal on the "E" Pin */
        ret |= HLCD_send_enable_signal(lcd);
    }
    return ret;
}

Std_Return HLCD_send_char_pos(lcd_t *lcd,LCD_Row_t row, LCD_Colum_t column, uint8 data)
{
    Std_Return ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {    
        ret = HLCD_set_cursor(lcd, row, column);
        ret |= HLCD_send_char(lcd, data);
    }
    return ret;
}

Std_Return HLCD_send_num(lcd_t *lcd, sint16 number)
{
    Std_Return ret = E_OK;
    uint16 local_num = 1;
	if (number == 0)
	{
		return HLCD_send_char(lcd,'0');
	}
	if (number<0)
	{
		HLCD_send_char(lcd,'-');
		number *=-1;
	}
	while (number!=0)
	{
		local_num = ((local_num * 10)+(number % 10));
		number = number /10;
	}
	while (local_num!=1)
	{
		ret &= HLCD_send_char(lcd,(local_num%10)+'0');
		local_num=local_num/10;
	}
    return E_OK;
}

Std_Return HLCD_send_num_pos(lcd_t *lcd,LCD_Row_t row, LCD_Colum_t column, sint16 number)
{
    Std_Return ret = E_OK;
    ret = HLCD_set_cursor(lcd,row,column);
    ret &= HLCD_send_num(lcd,number);
    return ret;
}

Std_Return HLCD_send_string(lcd_t *lcd, uint8 *str)
{
    Std_Return ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {    
        while(*str)
        {
            ret &= HLCD_send_char(lcd, *str++);
        }
    }
    return ret;
}

Std_Return HLCD_send_string_pos(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, uint8 *str)
{
    Std_Return ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {    
        ret |= HLCD_set_cursor(lcd, row, column);
        ret |= HLCD_send_string(lcd, str);
    }
    return ret;
}

Std_Return HLCD_send_float(lcd_t *lcd, float32 num) 
{
    if (num<0)
	{
		HLCD_send_char(lcd,'-');
		num *=-1;
	}
    uint8 buffer[16]; // Buffer to store the formatted string
    sprintf((char*)buffer, "%.2f", num); // Format the float number with 2 decimal places
    return HLCD_send_string(lcd,buffer); // Print the formatted string on LCD
}

Std_Return HLCD_send_float_pos(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, float32 num) 
{
    Std_Return ret = E_OK;
    ret = HLCD_set_cursor(lcd,row,column);
    ret &= HLCD_send_float(lcd,num);
    return ret;
}

Std_Return HLCD_send_custom_char(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, 
                                         uint8 _chr[], uint8 mem_pos)
{
    Std_Return ret = E_OK;
    uint8 lcd_counter = ZERO;
    if(NULL == lcd)
    {
        ret = E_NOK;
    }
    else
    {    
        ret = HLCD_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter)
        {
            ret |= HLCD_send_char(lcd, _chr[lcd_counter]);
        }
        ret |= HLCD_send_char_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

static Std_Return HLCD_send_4bits(lcd_t *lcd, uint8 _data_command)
{
    Std_Return ret = E_OK;
    ret = MDIO_SetPinValue(&(lcd->lcd_data[0]), (_data_command >> 0) &BIT_MASK);
    ret |= MDIO_SetPinValue(&(lcd->lcd_data[1]), (_data_command >> 1)&BIT_MASK);
    ret |= MDIO_SetPinValue(&(lcd->lcd_data[2]), (_data_command >> 2)&BIT_MASK);
    ret |= MDIO_SetPinValue(&(lcd->lcd_data[3]), (_data_command >> 3)&BIT_MASK);
    return ret;
}

static Std_Return HLCD_send_enable_signal(lcd_t *lcd)
{
    Std_Return ret = E_OK;
    ret |= MDIO_SetPinValue(&(lcd->lcd_en), DIO_HIGH);
    MCAL_Delay_ms(1);
    ret |= MDIO_SetPinValue(&(lcd->lcd_en), DIO_LOW);
    MCAL_Delay_ms(1);
    return ret;
}

Std_Return HLCD_set_cursor(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column)
{
    Std_Return ret = E_OK;
    switch(row)
    {
        case row_1 : ret = HLCD_send_command(lcd, (0x80 + column)); break; /* 0x00 -> Decimal : 0  */
        case row_2 : ret = HLCD_send_command(lcd, (0xC0 + column)); break; /* 0x40 -> Decimal : 64 */
#if ROW3_CONFIG == ENABLE
        case row_3 : ret = HLCD_send_command(lcd, (0x94 + coulmn)); break; /* 0x14 -> Decimal : 20 */
#endif
#if ROW4_CONFIG == ENABLE
        case row_4 : ret = HLCD_send_command(lcd, (0xd4 + coulmn)); break; /* 0x54 -> Decimal : 84 */
#endif
        default : ret = E_NOK;break;
    }
    return ret;
}



