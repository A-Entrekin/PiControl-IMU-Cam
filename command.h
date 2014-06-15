#ifndef COMMAND_H_
#define COMMAND_H_
#include "register.h"
#include <time.h>
#include "bcm2835.h"
#include <cmath>
#include <stdint.h>
#include <iostream>
#include "serialMessage.h"

//int initialize(void);

//Sends command to IMU, recording simultanious IMU output to buffer
//See register.h, enum IMU_COMM
void gcommand(IMU_COMM command);

	
//Sets gyro range
//See register.h, enum Range
void rangeset(Range range);

//This function sets the number of filter taps on the imu.  ntaps should be a power of two.
void tapset(int ntaps);


//General, 16 bit command/16 bit data reader
uint16_t read_data(Register reg);

/*
 * Calibrates the offset of a given register
 * gyroscope		=>	value in deg/sec
 * accelerometer	=>	value in mg
 * magnetometer HIF	=>	value in mgauss
 * magnetometer SIF	=>	value is scale factor betweeen 0 and 2
*/

/*
 * No vote of confidence that this actually works. 
*/
void callibset(Register reg, double value);

int initialize(void);

//gets IMU burst, returns raw byte message
serial_t burst(void);

#endif /*COMMAND_H_*/
