#ifndef REGISTER_H_
#define REGISTER_H_

//Registers
enum Register{
		FLASH_CNT			= 0x0000,	//Flash memory write count 
		SUPPLY_OUT			= 0x0200,	//Power supply measurement
		XGYRO_OUT			= 0x0400,	//X-axis gyroscope output
		YGYRO_OUT			= 0x0600,	//Y-axis gyroscope output
		ZGYRO_OUT			= 0x0800,	//Z-axis gyroscope output
		XACCL_OUT			= 0x0A00,	//X-axis accelerometer output
		YACCL_OUT			= 0x0C00,	//Y-axis accelerometer output
		ZACCL_OUT			= 0x0E00,	//Z-axis accelerometer output
		XMAGN_OUT			= 0x1000,	//X-axis magnetometer measurement
		YMAGN_OUT			= 0x1200,	//Y-axis magnetometer measurement
		ZMAGN_OUT			= 0x1400,	//Z-axis magnetometer measurement
		TEMP_OUT			= 0x1600,	//Temperature output
		AUX_ADC				= 0x1800,	//Auxiliary ADC measurement
		XGYRO_OFF			= 0x1A00,	//X-axis gyroscope bias offset factor
		YGYRO_OFF			= 0x1C00,	//Y-axis gyroscope bias offset factor
		ZGYRO_OFF			= 0x1E00,	//Z-axis gyroscope bias offset factor
		XACCL_OFF			= 0x2000,	//X-axis acceleration bias offset factor
		YACCL_OFF			= 0x2200,	//Y-axis acceleration bias offset factor
		ZACCL_OFF			= 0x2400,	//Z-axis acceleration bias offset factor
		XMAGN_HIF			= 0x2600,	//X-axis magnetometer, hard-iron factor
		YMAGN_HIF			= 0x2800,	//Y-axis magnetometer, hard-iron factor
		ZMAGN_HIF			= 0x2A00,	//Z-axis magnetometer, hard-iron factor
		XMAGN_SIF			= 0x2C00,	//X-axis magnetometer, soft-iron factor
		YMAGN_SIF			= 0x2E00,	//Y-axis magnetometer, soft-iron factor
		ZMAGN_SIF			= 0x3000,	//Z-axis magnetometer, soft-iron factor
		GPIO_CTRL			= 0x3200,	//Auxiliary digital input/output control
		MSC_CTRL			= 0x3400,	//Miscellaneous control
		SMPL_PRD			= 0x3600,	//Internal sample period (rate) control
		SENS_AVG			= 0x3800,	//Dynamic range and digital filter control
		SLP_CNT				= 0x3A00,	//Sleep mode control
		DIAG_STAT			= 0x3C00,	//System status 
		GLOB_CMD			= 0x3E00,	//System command
		ALM_MAG1			= 0x4000,	//Alarm 1 amplitude threshold
		ALM_MAG2			= 0x4200,	//Alarm 2 amplitude threshold 
		ALM_SMPL1			= 0x4400,	//Alarm 1 sample size
		ALM_SMPL2			= 0x4600,	//Alarm 2 sample size
		ALM_CTRL			= 0x4800,	//Alarm control 
		AUX_DAC				= 0x4A00,	//Auxiliary DAC data
		UPPER_BYTE			= 0x0100,	//Add to address to access upper byte
		LOWER_BYTE			= 0x0000,	//Add to address to access LOWER byte
		MSB_1				= 0x8000,	//Use to change MSB to 1
		PROD_ID				= 0x5600	//The register containing the product identification
};

enum IMU_COMM{
	fautonull			=0x0001,  //quickly corrects gyroscope to output all registers to 0 when motionless
	factoryrestore		=0x0002,  //restore default calibration settings from flash memory
	DAClatch			=0x0004,  //this moves the AUX_DAC register to the DAC input register (see table 21 in notebook)
	flashupdate			=0x0008,  //this performs a backup of the current register settings into flash memory.
	pautonull			=0x0010,  //precisely corrects gyrocope to output all registers to 0 when motionless.  Note: takes at least 30 seconds
	softreset			=0x0080   //stops device, powers off, powers on, reloads registers from flash memory
};

//Values for the gyro range
enum Range {
		pm300				= 0x0004,
		pm150				= 0x0002,
		pm75				= 0x0001
	};

#endif /*REGISTER_H_*/
