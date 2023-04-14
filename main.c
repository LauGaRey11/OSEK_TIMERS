/*
 * Prueba OSEK
 *
 * Miembros del equipo:
 *		Laura García
 * 		Tahirí Ramos
 *
 * 07/02/2023
 *
 */
#include "OSEK.h"
#include "LED_RGB.h"
#include "PUSH_BUTTONS.h"
#include "bits.h"
#include "NVIC.h"
#include "GPIO.h"

Task_struct_t task_list[3];

int main (void)
{
	//TASK A
	task_list[0].PRIORITY = 0;
	task_list[0].SCHEDULE = FULL;
	task_list[0].AUTOSTART = TRUE;
	task_list[0].ACTIVATION = SUSPENDED;
	task_list[0].ptr_funct = task_A;

	//TASK B
	task_list[1].PRIORITY = 1;
	task_list[1].SCHEDULE = FULL;
	task_list[1].AUTOSTART = FALSE;
	task_list[1].ACTIVATION = SUSPENDED;
	task_list[1].ptr_funct = task_B;


	//TASK C
	task_list[2].PRIORITY = 2;
	task_list[2].SCHEDULE = FULL;
	task_list[2].AUTOSTART = FALSE;
	task_list[2].ACTIVATION = SUSPENDED;
	task_list[2].ptr_funct = task_C;


	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_4);

	init_RGB();
	gpio_init();
	while (1){
		os_init();
	}
}

