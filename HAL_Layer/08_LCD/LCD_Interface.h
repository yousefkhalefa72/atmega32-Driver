/* 
 * File:   LCD_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 2:56 PM
 */

#ifndef LCD_INTERFACE_H
#define	LCD_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/01_DIO/DIO_Interface.h"
#include "LCD_Config.h"

/* ----------------- Macro Declarations -----------------*/
#define _LCD_CLEAR                                  0X01
#define _LCD_RETURN_HOME                            0x02

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    colum_1 = 0,
    colum_2,
    colum_3,
    colum_4,
    colum_5,
    colum_6,
    colum_7,
    colum_8,
    colum_9,
    colum_10,
    colum_11,
    colum_12,   
    colum_13,
    colum_14,
    colum_15,
    colum_16
}LCD_Colum_t;

typedef enum
{
    row_1 = 1,
    row_2,
#if ROW3_CONFIG == ENABLE
    row_3,
#endif
#if ROW4_CONFIG == ENABLE
    row_4
#endif
}LCD_Row_t;
typedef enum
{
    LCD_4Bits = 0,
    LCD_8Bits = 1
}LCD_Type_t;

typedef struct
{
    pin_t lcd_rs;
    pin_t lcd_en;
    pin_t lcd_data[8];
    LCD_Type_t type;
}lcd_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return HLCD_intialize(lcd_t *lcd);
Std_Return HLCD_set_cursor(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column);

Std_Return HLCD_send_command(lcd_t *lcd, uint8 command);

Std_Return HLCD_send_char(lcd_t *lcd, uint8 data);
Std_Return HLCD_send_char_pos(lcd_t *lcd,LCD_Row_t row, LCD_Colum_t column, uint8 data);

Std_Return HLCD_send_num(lcd_t *lcd, sint16 number);
Std_Return HLCD_send_num_pos(lcd_t *lcd,LCD_Row_t row, LCD_Colum_t column, sint16 number);

Std_Return HLCD_send_float(lcd_t *lcd, float32 num);
Std_Return HLCD_send_float_pos(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, float32 num);

Std_Return HLCD_send_string(lcd_t *lcd, uint8 *str);
Std_Return HLCD_send_string_pos(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, uint8 *str);

Std_Return HLCD_send_custom_char(lcd_t *lcd, LCD_Row_t row, LCD_Colum_t column, 
                                         uint8 _chr[], uint8 mem_pos);


#endif	/* LCD_INTERFACE_H */

