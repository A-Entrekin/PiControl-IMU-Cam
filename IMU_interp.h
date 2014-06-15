#ifndef IMU_INTERP_H_
#define IMU_INTERP_H_

#include <iostream>
#include <assert.h>
#include <stdint.h>
#include "register.h"


//To use with DIAG_STAT register
//Prints assorted diagnostic information
void diagstat(uint16_t data);


/* 
 * Sets 'result' to the interpreted value non-gyroscopic results
 * Returns zero if sucessful.
 */
int genInterp(Register reg, uint16_t data, double *result);

//Interprets gyroscopic data, with range being pm300, pm150 or pm75
//'result' in degrees per second
int gyroInterp(Register reg, uint16_t data, Range range, double *result);



#endif /*IMU_INTERP_H_*/
