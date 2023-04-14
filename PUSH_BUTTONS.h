/*
 * PUSH_BUTTONS.h
 *
 * 	This file contains the declarations of functions that we are going to use to manipulate the usage of the push buttons
 * 	integrated in the K64 and externals in case of having them.
 * 	Also we will find some variable definitions and some variable structures that we'll need.
 *
 *  Created on: 31 ago 2022
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#ifndef EQUIPO_6_T5_PUSH_BUTTONS_H_
#define EQUIPO_6_T5_PUSH_BUTTONS_H_

#include "stdint.h"
#include "LED_RGB.h"

#define LOGIC_ONE 0X1

#define PCR_PTD11 (*((volatile uint32_t *)0x4004C02C ))
#define PCR_PTA10 (*((volatile uint32_t *)0x40049028))

#define GPIO_D_PDOR (*((volatile uint32_t *)0x400FF100))
#define GPIO_D_PDDR (*((volatile uint32_t *)0x400FF0D4))

typedef enum
{
		SW2,	//0
		SW3,	//1
}SW_select_t;

/*
 * Returns the status of the SW we are asking for. If the sw is pushed will return 0 and if it is
 * not pushed will return a number diferent to 0.
 */
uint8_t sw_status(SW_select_t);

#endif /* EQUIPO_6_T5_PUSH_BUTTONS_H_ */
