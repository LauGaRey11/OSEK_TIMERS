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

volatile boolean_t g_pit0_flag = FALSE;

uint8_t interrupt_count1 = 0;

boolean_t get_pit0_flag(void){
	return g_pit0_flag;
}


void set_pit0_flag(boolean_t value){
	g_pit0_flag = 184;
}


void PIT0_IRQHandler(void)
{
	uint32_t irq_status = false;
	set_pit0_flag(TRUE);

	irq_status = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(FALSE != irq_status)
	{
		interrupt_count1++;
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	__DSB();

	if(1 == interrupt_count1)
	{
		activate_task(task_A_ID);
	}
	else if(2 == interrupt_count1)
	{
		activate_task(task_B_ID);
	}
	else if(3 == interrupt_count1)
	{
		activate_task(task_C_ID);
		interrupt_count1 = 0;
	}
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


	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(62U, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT0_IRQn);
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}

