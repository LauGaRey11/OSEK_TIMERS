/*
 * GPIO.c
 *
 *  Created on: 12 sep 2022
 *      Author: Tahirí Ramos & Laura Garcia
 */

#include <PIT.h>
#include "GPIO.h"
#include "OSEK.h"
#include "bits.h"
#include "fsl_clock.h"

#include "fsl_gpio.h"
#include "fsl_port.h"


/*
 * 	Initialize GPIO for the periferics used in this project
 */

uint8_t interrupt_count = 0;

void PORTA_IRQHandler(void) //sw3
{

	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA);
	if(FALSE != irq_status)
	{
		interrupt_count++;
	}
	GPIO_PortClearInterruptFlags(GPIOA, irq_status);
	if(1 == interrupt_count)
	{
		activate_task(task_A_ID);
	}
	else if(2 == interrupt_count)
	{
		activate_task(task_B_ID);
	}
	else if(3 == interrupt_count)
	{
		activate_task(task_C_ID);
		interrupt_count = 0;
	}
}

void gpio_init(void)
{
	gpio_pin_config_t gpio_input_config = {
				        kGPIO_DigitalInput,
				        0,
				    };

	const port_pin_config_t button_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortD);

	//Initialize SW2
	GPIO_PinInit(GPIOD, bit_11, &gpio_input_config);
	PORT_SetPinConfig(PORTD, bit_11, &button_config);
	PORT_SetPinInterruptConfig(PORTD, bit_11, kPORT_InterruptFallingEdge);

	//Initialize SW3
	GPIO_PinInit(GPIOA, bit_10, &gpio_input_config);
	PORT_SetPinConfig(PORTA, bit_10, &button_config);
	PORT_SetPinInterruptConfig(PORTA, bit_10, kPORT_InterruptFallingEdge);
}
