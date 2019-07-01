/*
 * my_controller.c
 *
 *  Created on: Jun 25, 2019
 *      Author: joaoantoniocardoso
 */

#include "my_controller.h"

/**
 * @brief CONTROL LOOP
 */
void controller_loop(void)
{
    // Initialize (static) indexes (i,j,h) for array2d macros
    ARRAY2D_INDEX_INIT();

    // INPUT
    y[0][0] = (AdcMirror.ADCRESULT0);
#ifdef OVERSAMPLING
    y[0][0] += (AdcMirror.ADCRESULT1);
    y[0][0] += (AdcMirror.ADCRESULT2);
    y[0][0] += (AdcMirror.ADCRESULT3);
//        c[3] += 60.0;
    if(y[0][0] < 0) y[0][0] = 0;
    y[0][0] = y[0][0] * 0.25 * adc_ratio;
#endif

    /* ~~~~~~~~~~~~~~~~~~~ start of Reference ~~~~~~~~~~~~~~~~~~~~ */
    if(++reference_clock_counter >= reference_clock_trigger){
        reference_clock_counter = 0;

        r[0][0] = dt[reference_clock];
        tgl_dbgpin1();          // CHECK PIN 60
        if(reference_clock++) reference_clock = 0;

    }
    /* ~~~~~~~~~~~~~~~~~~~~ end of Reference ~~~~~~~~~~~~~~~~~~~~~ */


    /* ~~~~~~~~~~~~~~~~~~~ start of Observer ~~~~~~~~~~~~~~~~~~~~~ */
    if(++observer_clock_counter >= observer_clock_trigger){
        observer_clock_counter = 0;

        // ntildot = Ahat_o*ntil + Bhat_o*y + Fhat_o*u
        MUL(Fhat_o, u, ntildot);            // ntildot = Fhat_o * u
        MULSUM(Bhat_o, y, ntildot);         // ntildot += Bhat_o * y
        MULSUM(Ahat_o, ntil, ntildot);      // ntildot += Ahat_o * ntil

        // Discrete Integrator ntil/ntildot
        INT(ntildot, Tsn, ntil);            // ntil += ntildot*Tsn

        // TRANSFORMATION
        // xtil = Chat_o*ntil + Dhat_o*y
        MUL(Chat_o, ntil, xtil);            // xtil = Chat_o*ntil
        MULSUM(Dhat_o, y, xtil);            // xtil += Dhat_o*y
    }
    /* ~~~~~~~~~~~~~~~~~~~~ end of Observer ~~~~~~~~~~~~~~~~~~~~~~ */


    /* ~~~~~~~~~~~~~~~~~~ start of Controller ~~~~~~~~~~~~~~~~~~~~ */
    if(++controller_clock_counter >= controller_clock_trigger){
        controller_clock_counter = 0;

        SUB(r, y, edot);                    // edot = r - y

        // Discrete Integrator e/edot
        INT(edot, Tse, e);                  // e += edot * Tse

        // u = e*Ki - K*x
        GAIN(e, Ki, eKi);                   // eKi = e*Ki
        MUL(K, xtil, Kx);                   // Kx = K*xtil
        if(use_controller){
            SUB(eKi, Kx, u);                // u = eKi - Kx
        }else{
            COPY(r, u);                     // u = r
        }

    }
    /* ~~~~~~~~~~~~~~~~~~~ end of Controller ~~~~~~~~~~~~~~~~~~~~~ */

    // OUTPUT
    epwm1_set_dt(u[0][0] * dac_ratio);

}


