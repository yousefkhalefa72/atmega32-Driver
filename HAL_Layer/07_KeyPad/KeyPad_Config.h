/* 
 * File:   KeyPad_Config.h
 * Author: Yousef.Khalefa
 * Created on March 9, 2024, 1:37 PM
 */

#ifndef KEYPAD_CONFIG_H
#define	KEYPAD_CONFIG_H

/* ----------------- Includes -----------------*/

/* ----------------- Macro Declarations -----------------*/
// max number for rows is 6
// max number for columns is 6

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4 

// for unused row or column better but it by NULL
#define R1C1 '7'
    #define R1C2 '8'
        #define R1C3 '9'
            #define R1C4 '/'
                #define R1C5 0
                    #define R1C6 0
#define R2C1 '4'
    #define R2C2 '5'
        #define R2C3 '6'
            #define R2C4 '*'
                #define R2C5 0
                    #define R2C6 0

#define R3C1 '1'
    #define R3C2 '2'
        #define R3C3 '3'
            #define R3C4 '-'
                #define R3C5 0
                    #define R3C6 0
#define R4C1 '#'
    #define R4C2 '0'
        #define R4C3 '='
            #define R4C4 '+'
                #define R4C5 0
                    #define R4C6 0
#define R5C1 NULL
    #define R5C2 NULL
        #define R5C3 NULL
            #define R5C4 NULL
                #define R5C5 NULL
                    #define R5C6 NULL
#define R6C1 NULL
    #define R6C2 NULL
        #define R6C3 NULL
            #define R6C4 NULL
                #define R6C5 NULL
                    #define R6C6 NULL

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* KEYPAD_CONFIG_H */

