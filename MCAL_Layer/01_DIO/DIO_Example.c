#if 0
#include "DIO_Interface.h"

uint8 porta_dir;
uint8 porta_value;

/* make port direction -> output */
MDIO_SetPortDirection(PORTA_INDEX,0xFF);

/* read port direction */
MDIO_GetPortDirection(PORTA_INDEX,&porta_dir);

/* make port output -> HIGH */
MDIO_SetPortValue(PORTA_INDEX,0xFF);

/* toggle port output -> LOW */
MDIO_TogglePortValue(PORTA_INDEX);

/* toggle port output -> HIGH */
MDIO_TogglePortValue(PORTA_INDEX);

/* make port output LOW */
MDIO_SetPortValue(PORTA_INDEX,0x00);

/* make port direction -> output */
MDIO_SetPortDirection(PORTA_INDEX,0x00);

/* read port input */
MDIO_GetPortValue(PORTA_INDEX,&porta_value);

pin_t pinA0 ={.port=PORTA_INDEX, .pin=PIN0_INDEX, .direction=DIO_DIRECTION_OUTPUT, .logic=DIO_LOW};
direction_t pinA0_dir;
logic_t pinA0_logic;

/* init pin -> output */
MDIO_SetPinDirection(&pinA0);

/* Read pin direction */
MDIO_GetPinDirection(&pinA0,&pinA0_dir);

/* make pin output -> HIGH */
MDIO_SetPinValue(&pinA0,DIO_HIGH);

/* toggle pin output -> LOW */
MDIO_TogglePinValue(&pinA0);

/* toggle pin output -> HIGH */
MDIO_TogglePinValue(&pinA0);

/* make pin output -> LOW */
MDIO_SetPinValue(&pinA0,DIO_LOW);

/* change direction of pin to input */
pinA0.direction = DIO_DIRECTION_INPUT;

/* init pin -> output */
MDIO_SetPinDirection(&pinA0);

/* read pin input */
MDIO_GetPinValue(&pinA0,&pinA0_logic);

#endif
