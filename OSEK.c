 /*
 * OSEK.c
 *
 *  Created on: 3 feb 2023
 *      Author: Tahirí
 *
 */

#include "OSEK.h"
#include "LED_RGB.h"

extern Task_struct_t task_list[3];
uint8_t destino;
uint32_t *contexto_temp;

void os_init()
{
	uint8_t task_ID;

		for(task_ID = 0; task_ID<TOTAL_TASKS; task_ID++ )
		{
			if(task_list[task_ID].AUTOSTART)
			{
				activate_task(task_ID);
			}
		}
		//recupera contexto
		asm ("LDR R0,=destino");
		asm ("STR R1,[R0]");
		scheduler();
}
/*
 *  The specified task is transferred from the suspended ACTIVATION
 *  into the ready ACTIVATION
 */
void activate_task(uint8_t task_ID)
{
    task_list[task_ID].ACTIVATION = READY;    // 3:wait    2:running    1:ready    0:suspend
    // if interrupción, recupera contexto completo
    // else, recupera contexto del stack usando el sp desde c
    //recupera contexto
	asm ("LDR R0,= destino");
	asm ("STR R1,[R0]");
    scheduler(); //barrido de tareas
}


/*
 * After termination of the calling task an other task is
 * activated sequentially
 */
void chained_task(uint8_t task_ID)
{
	for(uint8_t i= 0; i <TOTAL_TASKS; i++)
		{
			if(task_list[i].ACTIVATION == RUNNING)
			{
				task_list[i].ACTIVATION = SUSPENDED;
			}
		}
	activate_task(task_ID);
}


/*
 * The calling task is transferred from the running ACTIVATION into
 * the suspended ACTIVATION
 */
void terminate_task(void)
{
	for(uint8_t i= 0; i <TOTAL_TASKS; i++)
	{
		if(task_list[i].ACTIVATION == RUNNING)
		{
			task_list[i].ACTIVATION = SUSPENDED;
			//recupera contexto
			asm ("LDR R0,= destino");
			asm ("STR R1,[R0]");
			scheduler();
		}
	}
}

/*
 * Using this service the task explicitly yields control to a
 * higher-priority ready task (if any exists)
 */


void scheduler()
{
	for(int8_t i = TOTAL_PRIORITY; i>=0 ; i--)
	{
		for(int8_t j = 0; j<TOTAL_TASKS ; j++)
		{
			if((task_list[j].ACTIVATION == READY)&&(task_list[j].PRIORITY == i))
			{
				task_list[j].ACTIVATION = RUNNING;
				contexto_temp = &task_list[j].CONTEXTO;
				//restaurar contexto
				asm ("LDR R0,=contexto_temp");
				asm ("LDR R1,[R0]");
				task_list[j].ptr_funct();
				break;
			}
		}
	}
}


void task_A (void)
{
	set_color(RED);
	delay(2000000);
	activate_task(task_B_ID);

	set_color(RED);
	delay(2000000);
}

void task_B (void)
{
	//led azul
	set_color(BLUE);
	delay(2000000);
	chained_task (task_C_ID);
}

void task_C (void)
{
	//led verde
	set_color(GREEN);
	delay(2000000);
	terminate_task();
}
