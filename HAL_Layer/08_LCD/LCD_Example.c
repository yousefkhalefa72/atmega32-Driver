#if 0

#include "LCD_Interface.h"

/* GND -> Vss , RW , C */
/* 5v -> Vdd , A , Vee with pot */
    
/* 8 bit LCD init*/
lcd_t lcd1 = {.lcd_data[0].port=PORTD_INDEX,.lcd_data[0].pin=PIN0_INDEX,
              .lcd_data[1].port=PORTD_INDEX,.lcd_data[1].pin=PIN1_INDEX,
              .lcd_data[2].port=PORTD_INDEX,.lcd_data[2].pin=PIN2_INDEX,
              .lcd_data[3].port=PORTD_INDEX,.lcd_data[3].pin=PIN3_INDEX,
              .lcd_data[4].port=PORTD_INDEX,.lcd_data[4].pin=PIN4_INDEX,
              .lcd_data[5].port=PORTD_INDEX,.lcd_data[5].pin=PIN5_INDEX,
              .lcd_data[6].port=PORTD_INDEX,.lcd_data[6].pin=PIN6_INDEX,
              .lcd_data[7].port=PORTD_INDEX,.lcd_data[7].pin=PIN7_INDEX,
              .lcd_rs.port=PORTC_INDEX,.lcd_rs.pin=PIN0_INDEX,
              .lcd_en.port=PORTC_INDEX,.lcd_en.pin=PIN1_INDEX,
              .type=LCD_8Bits};
    
/* 4 bit LCD init*/
lcd_t lcd1 = {.lcd_data[0].port=PORTD_INDEX,.lcd_data[0].pin=PIN0_INDEX,
              .lcd_data[1].port=PORTD_INDEX,.lcd_data[1].pin=PIN1_INDEX,
              .lcd_data[2].port=PORTD_INDEX,.lcd_data[2].pin=PIN2_INDEX,
              .lcd_data[3].port=PORTD_INDEX,.lcd_data[3].pin=PIN3_INDEX,
              .lcd_rs.port=PORTC_INDEX,.lcd_rs.pin=PIN0_INDEX,
              .lcd_en.port=PORTC_INDEX,.lcd_en.pin=PIN1_INDEX,
              .type=LCD_4Bits};

HLCD_intialize(&lcd1);

HLCD_send_char(&lcd1,'a');
HLCD_send_char_pos(&lcd1,row_1,colum_5,':');

HLCD_set_cursor(&lcd1,row_2,colum_1);
uint8 yousef[7]="yousef";
HLCD_send_string(&lcd1,yousef);

HLCD_send_num_pos(&lcd1,row_1,colum_10,-1156);

HLCD_send_float_pos(&lcd1,row_2,colum_8,2024.25);

#endif
