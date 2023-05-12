/*
 * PIT.c
 *
 *  Created on: 13 abr 2023
 *      Author: Laura Garcia
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "PIT.h"
#include "OSEK.h"
#include "bits.h"


#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
extern Alarm_struct_t alarm_time[3];

volatile boolean_t g_pit0_flag = FALSE;

boolean_t get_pit0_flag(void){
	return g_pit0_flag;
}


void set_pit0_flag(boolean_t value){
	g_pit0_flag = value;
}


void PIT0_IRQHandler(void)
{
	uint32_t irq_status = FALSE;
	set_pit0_flag(TRUE);

	irq_status = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	for(uint8_t task_ID = 0; task_ID<TOTAL_TASKS; task_ID++ )
	{

		alarm_time[task_ID].SET_ALARM--;

		if(alarm_time[task_ID].SET_ALARM == 0)
		{
			activate_task(task_ID);

			if(alarm_time[task_ID].RELOAD == FALSE){
				alarm_time[task_ID].SET_ALARM = alarm_time[task_ID].INITIAL_TIME;
			}
		}
	}

	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	__DSB();
}


void PIT_stop(void){
	PIT_StopTimer(PIT, kPIT_Chnl_0);
}


void PIT_start(void){
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}


void PIT_init(void){
	pit_config_t pitConfig;

	CLOCK_SetSimSafeDivs();
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT, &pitConfig);


	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000U, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT0_IRQn);
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}

