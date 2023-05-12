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
//#include "GPIO.h"

extern Task_struct_t task_list[3];
extern Alarm_struct_t alarm_time[3];

void task_A (void)
{
	set_color(RED);
	delay(1000000);
	activate_task(task_B_ID);

	set_color(RED);
	delay(1000000);
}

void task_B (void)
{
	//led azul
	set_color(BLUE);
	delay(1000000);
	chained_task (task_C_ID);
}

void task_C (void)
{
	//led verde
	set_color(GREEN);
	delay(1000000);
	terminate_task();
}

int main (void)
{
	//TASK A
	task_list[0].PRIORITY = 0;
	task_list[0].SCHEDULE = FULL;
	task_list[0].AUTOSTART = TRUE;
	task_list[0].ACTIVATION = SUSPENDED;
	task_list[0].ptr_funct = task_A;
	alarm_time[0].SET_ALARM = 3000U;
	alarm_time[0].INITIAL_TIME = alarm_time[0].SET_ALARM;


	//TASK B
	task_list[1].PRIORITY = 1;
	task_list[1].SCHEDULE = FULL;
	task_list[1].AUTOSTART = FALSE;
	task_list[1].ACTIVATION = SUSPENDED;
	task_list[1].ptr_funct = task_B;
	alarm_time[1].SET_ALARM = 5000U;
	alarm_time[1].INITIAL_TIME = alarm_time[1].SET_ALARM;


	//TASK C
	task_list[2].PRIORITY = 2;
	task_list[2].SCHEDULE = FULL;
	task_list[2].AUTOSTART = FALSE;
	task_list[2].ACTIVATION = SUSPENDED;
	task_list[2].ptr_funct = task_C;
	alarm_time[2].SET_ALARM = 7000U;
	alarm_time[2].INITIAL_TIME = alarm_time[2].SET_ALARM;


	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_4);

	init_RGB();
//	gpio_init();
	PIT_init();



	while (1){
		os_init();
	}
}

