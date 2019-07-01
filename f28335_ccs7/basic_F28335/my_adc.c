/**
 * my_adc.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description:
 *
 *  References: http://www.ti.com/lit/ug/spru812a/spru812a.pdf
 *
 */

#include "my_adc.h"
#include "my_epwm.h"
#include "my_controller.h"
#include "ss.h"

/*
 * @brief
 */
void my_adc_init(void)
{
    // Callibration
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK=1;
    (*ADC_Cal) ();
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK=0;
    EDIS;

    // ISR functions found within this file.
    EALLOW;
    PieVectTable.ADCINT = &adc_isr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS;

    InitAdc();                              // Basic ADC setup, incl. calibration

    // Configure ADC
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       // start-stop mode
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;       // Dual-sequencer mode. SEQ1 and SEQ2 operate as two 8-state sequencers.
    AdcRegs.ADCTRL1.bit.CPS = 1;            // Core clock prescaler (ADCCLK = Fclk/2) (aparentemente obrigatório)
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0xf;       // Acquisition window size.
    //AdcRegs.ADCTRL3.bit.ADCCLKPS = 0xf;     // HSPCLK/[30*(ADCTRL1[7] + 1)]
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;      // Sequential sampling mode is selected.
    AdcRegs.ADCREFSEL.bit.REF_SEL = 0;      // Internal reference selected (default)

    // SEQ1 config:
#ifndef OVERSAMPLING
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0;   // Setup 1 conv's on SEQ1
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x2;  // Setup ADCINA2 as 1nd SEQ1 conv.
#else
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 4;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x2;
#endif

    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;   // INT_SEQ1 is set at the end of every SEQ1 sequence.
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0 ;      // Clears a pending SOC trigger for SEQ1.
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;   // Interrupt request by INT_SEQ1 is enabled.


    InitCpuTimers();                            // Basic Timers setup
//    ConfigCpuTimer(&CpuTimer0, 150, 1000);     // 1000us for 1kHz
    ConfigCpuTimer(&CpuTimer0, 150, 1E6 / Fsn);
//    ConfigCpuTimer(&CpuTimer0, 150, 100);;     // 100us for 10kHz

    //////// Enable interrupts /////////

    // enable interrupts at peripheral level:
//    CpuTimer0Regs.TCR.bit.TIE = 1;          // timer0

    // enable interrupts at PIsE level:
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;      // Enable ADCINT in PIE
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      // Enable TINT0 in the PIE: Group 1 interrupt 7

    // enable interrupts at CPU level:
    IER |= M_INT1;      // Enable CPU Interrupt 1

    // To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
    // of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
    // below settings must also be updated.
    CpuTimer0Regs.TCR.all = 0x4000;         // Use write-only instruction to set TSS bit = 0

}

__interrupt void adc_isr(void)
{
    set_dbgpin2();
    controller_loop();
    clr_dbgpin2();

    // Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;       // Reset SEQ1 to state CONV00
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;     // Clear INT SEQ1 interrupt flag bit
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt to PIE
}

__interrupt void cpu_timer0_isr(void)
{

   CpuTimer0.InterruptCount++;

   AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1 ;       // Software triggers SEQ1
   PieCtrlRegs.PIEACK.bit.ACK7 = 1;         // TINT0 ack

   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
