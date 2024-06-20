/* 
 * File:   Stepper_Config.h
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#ifndef STEPPER_CONFIG_H
#define	STEPPER_CONFIG_H

/* Section : Includes */

/* Section: Macro Declarations */
#define T0_for_STEPPER          DISABLE
        
/* 10 millsec for 1 step
   80 millsec for 1 rev
   the max RPS is 12.5 */
#define STEPPER_MAX_RPS         12.5
#define TIME_ERROR_MS           15

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

#endif	/* STEPPER_CONFIG_H */

