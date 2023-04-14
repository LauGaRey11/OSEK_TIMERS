/*
 * PUSH_BUTTONS.c
 *
 * Contains the definitions of all the functions declared in the PUSH_BUTTONS header file.
 *
 *  Created on: 31 ago 2022
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#include "bits.h"
#include "PUSH_BUTTONS.h"
#include "fsl_gpio.h"

uint8_t sw_status(SW_select_t sw_num)
{
	switch(sw_num)
	{
		case SW2:
		// returns the value of the SW2, if it is pushed in = 0 other wise is != 0
		return (boolean_t) ((~GPIO_PinRead(GPIOD, bit_11)) & LOGIC_ONE);
		break;
		case SW3:
			// returns the value of the SW3, if it is pushed in = 0 other wise is != 0
			return (boolean_t) ((~GPIO_PinRead(GPIOA, bit_10)) & LOGIC_ONE);
		break;
		default:
			return FALSE;
		break;
	}
}
