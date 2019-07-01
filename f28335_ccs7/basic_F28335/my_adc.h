/**
 * my_adc.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 *  References: http://www.ti.com/lit/ug/spru812a/spru812a.pdf
 *
 */

#ifndef MY_ADC_H_
#define MY_ADC_H_

#include "DSP28x_Project.h"

extern Uint32 raw_adc0;

void my_adc_init(void);
__interrupt void adc_isr(void);
__interrupt void cpu_timer0_isr(void);

#endif /* MY_ADC_H_ */
