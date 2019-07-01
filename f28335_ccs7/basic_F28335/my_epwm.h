/**
 * my_epwm.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_EPWM_H_
#define MY_EPWM_H_

#include "DSP28x_Project.h"

void my_epwm_init(void);

void MyInitEPwmGpio(void);
void InitEPwm1(void);
void InitEPwm2(void);
void InitEPwm3(void);
void InitEPwm4(void);
void InitEPwm5(void);
void InitEPwm6(void);


// #define epwm1_set_dt(dt)  EPwm1Regs.CMPA.half.CMPA = (Uint32) ((dt)*EPwm1Regs.TBPRD)
#define epwm1_set_dt(dt) EPwm1Regs.CMPA.half.CMPA = dt
#define epwm2_set_dt(dt) EPwm2Regs.CMPA.half.CMPA = dt
#define epwm3_set_dt(dt) EPwm3Regs.CMPA.half.CMPA = dt
#define epwm4_set_dt(dt) EPwm4Regs.CMPA.half.CMPA = dt
#define epwm5_set_dt(dt) EPwm5Regs.CMPA.half.CMPA = dt
#define epwm6_set_dt(dt) EPwm6Regs.CMPA.half.CMPA = dt
#define epwm1_set_ph(ph) EPwm1Regs.TBPHS.half.TBPHS = ph
#define epwm2_set_ph(ph) EPwm2Regs.TBPHS.half.TBPHS = ph
#define epwm3_set_ph(ph) EPwm3Regs.TBPHS.half.TBPHS = ph
#define epwm4_set_ph(ph) EPwm4Regs.TBPHS.half.TBPHS = ph
#define epwm5_set_ph(ph) EPwm5Regs.TBPHS.half.TBPHS = ph
#define epwm6_set_ph(ph) EPwm6Regs.TBPHS.half.TBPHS = ph

#endif /* MY_EPWM_H_ */
