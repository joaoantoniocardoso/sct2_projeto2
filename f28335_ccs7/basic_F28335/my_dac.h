/**
 * my_dac.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description:
 *
 *  Ref: http://www.ti.com/lit/an/spraa88a/spraa88a.pdf
 *
 */

#ifndef MY_DAC_H_
#define MY_DAC_H_

#include "DSP28x_Project.h"

void my_dac_init(void);
void HRPWM1_Config(int32 period);

#endif /* MY_DAC_H_ */
