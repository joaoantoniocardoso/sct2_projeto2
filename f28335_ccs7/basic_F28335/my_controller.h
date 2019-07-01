/*
 * my_controller.h
 *
 *  Created on: Jun 25, 2019
 *      Author: joaoantoniocardoso
 */

#ifndef MY_CONTROLLER_H_
#define MY_CONTROLLER_H_

#include "ss.h"
#include "my_adc.h"
#include "my_epwm.h"
#include "array_macros.h"

// CONFIGURATIONS
#define VO1     1.0f
#define VO2     1.5f
#define REFERENCE_PERIOD  0.5f
#define OVERSAMPLING
static volatile const unsigned int use_controller = 1;        // Use control for output?

// ADC
//static volatile const float vadc = 3.0;
//static volatile const int badc = 12;
static volatile const float adc_ratio = 0.000732421875 * 1.0036764705882353;

// DAC
//static volatile const float vdac = 3.3;
//static volatile const int bdac = 12;
static volatile const float dac_ratio = 2272.7272727272728;

// CLOCKS
static volatile unsigned int reference_clock = 0;
static volatile unsigned int observer_clock_trigger = 0;
static volatile unsigned int controller_clock_trigger = 2;
static volatile unsigned int reference_clock_trigger = 1600; // = REFERENCE_PERIOD / (Tsn * 2)
static volatile unsigned int observer_clock_counter = 0;
static volatile unsigned int controller_clock_counter = 0;
static volatile unsigned int reference_clock_counter = 0;

static const float dt[2] = {VO1, VO2};

// FUNCTIONS
void controller_loop(void);

// Simplify macro
#define ROWS    ARRAY2D_ROWS
#define COLS    ARRAY2D_COLS
#define SUM     ARRAY2D_SUM_REVERSE
#define SUB     ARRAY2D_SUB_REVERSE
#define MUL     ARRAY2D_MUL_REVERSE
#define GAIN    ARRAY2D_GAIN_REVERSE
#define INT     ARRAY2D_GAINSUM_REVERSE
#define MULSUM  ARRAY2D_MULSUM_REVERSE
#define COPY    ARRAY2D_COPY_REVERSE
#define ZERO    ARRAY2D_ZERO_REVERSE

#endif /* MY_CONTROLLER_H_ */
