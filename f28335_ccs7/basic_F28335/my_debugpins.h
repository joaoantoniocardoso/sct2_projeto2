/*
 * my_debugpins.h
 *
 *  Created on: Sep 10, 2017
 *      Author: joaoantoniocardoso
 */

#include "DSP28x_Project.h"

#ifndef MY_DEBUGPINS_H_
#define MY_DEBUGPINS_H_

#define init_dbgpin1() EALLOW; GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1; EDIS
#define set_dbgpin1() GpioDataRegs.GPBSET.bit.GPIO60 = 1
#define clr_dbgpin1() GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1
#define tgl_dbgpin1() GpioDataRegs.GPBTOGGLE.bit.GPIO60 = 1

#define init_dbgpin2() EALLOW; GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1; EDIS
#define set_dbgpin2() GpioDataRegs.GPBSET.bit.GPIO61 = 1
#define clr_dbgpin2() GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1
#define tgl_dbgpin2() GpioDataRegs.GPBTOGGLE.bit.GPIO61 = 1

#endif /* MY_DEBUGPINS_H_ */
