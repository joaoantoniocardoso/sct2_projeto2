/*
 * my_dac.c
 *
 *  Created on: Apr 5, 2018
 *      Author: joaoantoniocardoso
 */

#include "my_dac.h"

void my_dac_init(void)
{

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

//====================================================================
// ePWM and HRPWM register initialization
//====================================================================
   HRPWM1_Config(10);       // ePWM1 target, 15 MHz PWM (SYSCLK=150MHz) or 10 MHz PWM (SYSCLK=100MHz)
   InitEPwm1Gpio();

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;

}

/**
 * Some useful Period vs Frequency values
 * SYSCLKOUT =     150MHz         100 MHz
 * -----------------------------------------
 * Period          Frequency      Frequency
 * 1000            150 kHz        100 KHz
 * 800             187 kHz        125 KHz
 * 600             250 kHz        167 KHz
 * 500             300 kHz        200 KHz
 * 250             600 kHz        400 KHz
 * 200             750 kHz        500 KHz
 * 100             1.5 MHz        1.0 MHz
 * 50              3.0 MHz        2.0 MHz
 * 25              6.0 MHz        4.0 MHz
 * 20              7.5 MHz        5.0 MHz
 * 12              12.5 MHz       8.33 MHz
 * 10              15.0 MHz       10.0 MHz
 * 9               16.7 MHz       11.1 MHz
 * 8               18.8 MHz       12.5 MHz
 * 7               21.4 MHz       14.3 MHz
 * 6               25.0 MHz       16.7 MHz
 * 5               30.0 MHz       20.0 MHz
 */
void HRPWM1_Config(int32 period)
{
// ePWM1 register configuration with HRPWM
// ePWM1A toggle low/high with MEP control on Rising edge

    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;           // set Immediate load
    EPwm1Regs.TBPRD = 1500;                             // PWM frequency = 1 / period
    EPwm1Regs.CMPA.half.CMPA = 0;                       // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
    EPwm1Regs.TBPHS.all = 0;                            // Set Phase register to zero
    EPwm1Regs.TBCTR = 0;                                // clear TB counte

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;             // EPWM1 is the Master
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;                // PWM toggle low/high
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;

    EALLOW;
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_REP;              //MEP control on Rising edge
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}
