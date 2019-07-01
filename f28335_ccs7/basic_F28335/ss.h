/*
 * ss.h
 *
 *  Created on: Jun 25, 2019
 *      Author: joaoantoniocardoso
 */

#ifndef _SS_H_
#define _SS_H_

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// CONSTANTS FOR SYSTEM //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static volatile const float A[3][3] = {
    {    0     ,     559.441  ,     0     },
    { -21.0084 ,     -100.928 ,  21.0084  },
    {    0     ,        0     ,  -666.667 }
};
static volatile const float B[3][1] = {
    {    0     },
    {    0     },
    { 666.667  }
};
static volatile const float C[1][3] = {{1,  0,  0}};
static volatile const float D[1][1] = {{0}};

////////////////////////////////////////////////////////////////////////////////
////////////////////////// CONSTANTS FOR CONTROLLER ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static volatile const float K[1][3] = {{4.0794, 11.5518,    -0.00496883}};
static volatile const float Ki = 375.8984344641513;
static volatile const float Fse = 3200;
static volatile const float Tse = 0.0003125;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// CONSTANTS FOR OBSERVER ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static volatile const float Ahat_o[2][2] = {
    { 152.583  ,     21.0084  },
    { -7986.92 ,     -666.667 }
};
static volatile const float Bhat_o[2][1] = {
    { 209.777  },
    { -5898.46 }
};
static volatile const float Chat_o[3][2] = {
    {    0     ,        0     },
    {    1     ,        0     },
    {    0     ,        1     }
};
static volatile const float Dhat_o[3][1] = {
    {    1     },
    {-0.453151 },
    { 14.2766  }
};
static volatile const float Fhat_o[2][1] = {
    {    0     },
    { 666.667  }
};
static volatile const float Ke[2][1] = {
    {-0.453151 },
    { 14.2766  }
};
static volatile const float Fsn = 6400;
static volatile const float Tsn = 0.00015625;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// VARIABLES ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static volatile float r[1][1];
static volatile float u[1][1] = {{0}};
static volatile float y[1][1] = {{0}};
static volatile float x[3][1] = {
    {    0     },
    {    0     },
    {    0     }
};
static volatile float xdot[3][1] = {
    {    0     },
    {    0     },
    {    0     }
};
static volatile float xtil[3][1] = {
    {    0     },
    {    0     },
    {    0     }
};
static volatile float ntil[2][1] = {
    {    0     },
    {    0     }
};
static volatile float ntildot[2][1] = {
    {    0     },
    {    0     }
};
static volatile float e[1][1] = {{0}};
static volatile float edot[1][1] = {{0}};

// Temporary variables for controller
static volatile float eKi[1][1] = {0};          // eKi = e * Ki
static volatile float Kx[1][1] = {0};           // Kx = K * x


#endif /*_SS_H_*/
