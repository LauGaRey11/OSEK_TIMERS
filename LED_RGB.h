/*
 * LED_RGB.h
 *
 *	Here we can find the declaration of functions and variable definitions for making work the K64 led RGB.
 *
 *  Created on: 31 ago 2022
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#ifndef RAMOS_UGALDE_T4_LED_RGB_H_
#define RAMOS_UGALDE_T4_LED_RGB_H_

#include "stdint.h"

#define BIT_BLUE  	1<<11
#define BIT_RED	  	1<<9
#define BIT_GREEN	1<<6

typedef enum
{
	RED,	//0
	BLUE,	//1
	GREEN,	//2
	WHITE,	//3
	NONE	//4
}RGB_colors_t;

//Enciende los leds para el color que queremos segun el caso

void init_RGB(void);

void set_color(RGB_colors_t);

void delay(uint32_t delay);

#endif /* RAMOS_UGALDE_T4_LED_RGB_H_ */
