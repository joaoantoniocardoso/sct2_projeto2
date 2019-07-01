/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: João Antônio Cardoso
 *
 *  Description: Firmware para o Projeto 1 de Sistemas de Controle 2
 *
 *  Instructions:
 *      1) Conectar a interrupção do pino GPIO60 como trigger no canal
 *      Ext. Trig. do osciloscópio
 *      2) Conectar a saída da planta no canal 1 do osciloscópio
 *      3) Conectar a saída epwm1 na entrada da planta e no canal 2 do
 *      osciloscópio
 *
 *  References: http://www.ti.com/product/TMS320F28335/technicaldocuments
 *
 */

#include "DSP28x_Project.h"
#include "my_adc.h"
#include "my_scia.h"
#include "my_epwm.h"
#include "my_debugpins.h"
#include "my_controller.h"

#define MY_DEBUG_

//void serial_debug(void);

void init(void){

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
}

void main(void)
{
    init();

    init_dbgpin1();
    set_dbgpin1();
    init_dbgpin2();

    for(;;);

}

