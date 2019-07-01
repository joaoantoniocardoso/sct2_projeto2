/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: João Antônio Cardoso
 *
 *  Description: Código para testar a placa do Raul
 *
 *  References: http://www.ti.com/product/TMS320F28335/technicaldocuments
 *
 */

#include "DSP28x_Project.h"
#include "my_adc.h"
#include "my_scia.h"
#include "my_epwm.h"
#include "my_debugpins.h"

#define MY_DEBUG_

void serial_debug(void);

void main(void)
{

    DINT;   // Disable Global interrupt

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // É necessário para as funções que utilizam macros dos .asm, como o InitAdc.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
    InitFlash();    // call InitFlash in RAM (SARAM - L0)

    InitSysCtrl();

    InitPieCtrl();
    InitPieVectTable();
    my_epwm_init();
    my_adc_init();

#ifdef MY_DEBUG_
    my_scia_init();
#endif

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

#define VO_MAX  3.30f
#define VO_MIN  0.00f
#define VO1     1.00f
#define VO2     1.50f
#define WAIT_S  0.50f

    Uint32 dt[2] = {EPwm1Regs.TBPRD*(VO1/(VO_MAX -VO_MIN)),
                    EPwm1Regs.TBPRD*(VO2/(VO_MAX -VO_MIN)) };
    Uint32 wait_us = WAIT_S*1000000;

    Uint32 i = 0;

    init_dbgpin1();
    set_dbgpin1();

    for(;;){
        epwm1_set_dt(dt[i]);
        tgl_dbgpin1();          // CHECK PIN 60

        DELAY_US(wait_us);
        if(i++) i = 0;
    }

}

