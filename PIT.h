/*
 * PIT.h
 *
 *  Created on: 13 abr 2023
 *      Author: Laura Garcia
 */

#include "fsl_pit.h"
#include "bits.h"

#ifndef PIT_H_
#define PIT_H_

// initialize the pit
void PIT_init(void);
// stops the PIT
void PIT_stop(void);
// starts the PIT
void PIT_start(void);
void PIT0_IRQHandler(void);
void PIT_callback_init(pit_chnl_t channel, void (*handler)(uint32_t flags));

boolean_t get_pit0_flag(void);
void set_pit0_flag(boolean_t value);


#endif /* PIT_H_ */
