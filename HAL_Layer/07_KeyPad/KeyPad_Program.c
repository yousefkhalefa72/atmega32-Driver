/* 
 * File:   KeyPad_Program.c
 * Author: Yousef.Khalefa
 * 
 * Created on March 9, 2024, 1:37 PM
 */

#include "KeyPad_Interface.h"

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {{R1C1, R1C2, R1C3, R1C4, R1C5, R1C6},
                                                              {R2C1, R2C2, R2C3, R2C4, R2C5, R2C6},
                                                              {R3C1, R3C2, R3C3, R3C4, R3C5, R3C6},
                                                              {R4C1, R4C2, R4C3, R4C4, R4C5, R4C6}
#if KEYPAD_ROWS > 4
                                                              ,{R5C1, R5C2, R5C3, R5C4, R5C5, R5C6}
#elif KEYPAD_ROWS > 5
                                                              };
#endif
#if KEYPAD_ROWS > 5
                                                              ,{R6C1, R6C2, R6C3, R6C4, R6C5, R6C6}};
#else
                                                              };
#endif

Std_Return Hkeypad_initialize(keypad_t *keypad)
{
    Std_Return ret = E_OK;
    
    if(NULL == keypad)
    {
        ret = E_NOK;
    }
    else
    {    
        for(uint8 rows_counter=0; rows_counter<KEYPAD_ROWS; rows_counter++)
        {
            keypad->keypad_row_pins[rows_counter].direction = DIO_DIRECTION_OUTPUT;
            ret = MDIO_SetPinDirection(&(keypad->keypad_row_pins[rows_counter]));
        }
        
        for(uint8 columns_counter=0; columns_counter<KEYPAD_COLUMNS; columns_counter++)
        {
            keypad->keypad_columns_pins[columns_counter].direction = DIO_DIRECTION_INPUT;
            ret = MDIO_SetPinDirection(&(keypad->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

Std_Return Hkeypad_get_value(keypad_t *keypad, uint8 *value)
{
    Std_Return ret = E_OK;
    uint8 logic = ZERO;
    
    if((NULL == keypad) || (NULL == value))
    {
        ret = E_NOK;
    }
    else
    {    
        for(uint8 counter=0; counter<KEYPAD_ROWS; counter++)
        {
            ret |= MDIO_SetPinValue(&(keypad->keypad_row_pins[counter]),DIO_LOW);
        }

        for(uint8 row=0; row<KEYPAD_ROWS; row++)
        {
            ret |= MDIO_SetPinValue(&(keypad->keypad_row_pins[row]), DIO_HIGH);
//            MCAL_Delay_ms(10); /* for bouncing */
             
            for(uint8 column=0; column<KEYPAD_COLUMNS; column++)
            {
                ret |= MDIO_GetPinValue(&(keypad->keypad_columns_pins[column]), &logic);
                if(DIO_HIGH == logic)
                {
                    *value = btn_values[row][column];
                    return ret;
                }
            }
            ret |= MDIO_SetPinValue(&(keypad->keypad_row_pins[row]), DIO_LOW);
        }
    }
    return ret;
}

