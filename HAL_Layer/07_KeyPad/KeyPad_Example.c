#if 0

#include "KeyPad_Interface.h"

/* Make sure you connect colums with pull down res */
/* config keypad in  KeyPad_Config.h               */
keypad_t keypad1={.keypad_row_pins[0].port=PORTC_INDEX,.keypad_row_pins[0].pin=PIN0_INDEX,
                  .keypad_row_pins[1].port=PORTC_INDEX,.keypad_row_pins[1].pin=PIN1_INDEX,
                  .keypad_row_pins[2].port=PORTC_INDEX,.keypad_row_pins[2].pin=PIN2_INDEX,
                  .keypad_row_pins[3].port=PORTC_INDEX,.keypad_row_pins[3].pin=PIN3_INDEX,
                  .keypad_columns_pins[0].port=PORTD_INDEX,.keypad_columns_pins[0].pin=PIN4_INDEX,
                  .keypad_columns_pins[1].port=PORTD_INDEX,.keypad_columns_pins[1].pin=PIN5_INDEX,
                  .keypad_columns_pins[2].port=PORTD_INDEX,.keypad_columns_pins[2].pin=PIN6_INDEX,
                  .keypad_columns_pins[3].port=PORTD_INDEX,.keypad_columns_pins[3].pin=PIN7_INDEX};
uint8 keypad_var = 0; 

Hkeypad_initialize(&keypad1);

/* method one -> polling to get value */
while(keypad_var == 0)
{
    Hkeypad_get_value(&keypad1,&keypad_var);
}
/* now you sure you have your value in keypad_var*/

/* method two -> get value if pressed */
Hkeypad_get_value(&keypad1,&keypad_var);
if(keypad_var == '7')
{
    /* if the pressed key is 7*/
}

/* method three -> get any value if pressed */
Hkeypad_get_value(&keypad1,&keypad_var);
if(keypad_var != 0)
{
    keypad_var -= '0';
    /* now you have pressed key as integer number */
}

#endif
