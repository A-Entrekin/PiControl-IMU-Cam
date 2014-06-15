#include "command.h"



const timespec stall={0,9};


void load16Buffer(uint16_t source, char* buffer){
	buffer[0] = source / 32;
	buffer[1] = source % 32;
	return;
}

uint16_t unload16Buffer(char* buffer){
	return (uint16_t) buffer[0] * 32 + buffer[1];
}

//underlying implementation of many commands.
//Not visable in header
void IMU_IO(uint16_t command, char* buffer, bool response){
	load16Buffer(command, buffer);
	bcm2835_spi_transfern(buffer, response ? 4 : 2); //writing command/reading IMU output
	nanosleep(&stall, NULL); //stall time for next command
}

struct serial_t burst(){
	//23 bytes to send and recieve burst mode info.
	char* buffer = malloc(23 * sizeof(char));
	struct timeval time;
	if (gettimeofday(&time, NULL)) throw 2;
	load16Buffer((uint16_t) 0x3E00, buffer);
	bcm2835_spi_transfern(buffer, 23);
	struct serial_t res;
	res.message = buffer;
	res.length = 23;
	res.time = time;
	return res;
}



void gcommand(IMU_COMM command){
	char buffer[2];
	IMU_IO((uint16_t)GLOB_CMD | command, buffer, false);
	return;
}

void rangeset(Range range){
	char buffer[2];
	IMU_IO((uint16_t) SENS_AVG | UPPER_BYTE | range, buffer, false);
}

//Quick and dirty log base 2, rounded down.
//Not visable in header
int msb(int i){
	int msb = -1;
	for (int j = sizeof(int) -1; j >= 0; j--){
		if (msb>>j == 1) return j;
	}
	return -1;
}

void tapset(int ntaps){
	char buffer[2];
	IMU_IO((uint16_t) SENS_AVG | LOWER_BYTE | msb(ntaps), buffer, false);
	return;
}

uint16_t read_data(Register reg){ 
		char buffer[4];
		IMU_IO((uint16_t)reg, buffer, true);
		return unload16Buffer(buffer + 2);

}

void callibset(Register reg, double value) {
	int32_t comval=0;
	if(reg==XMAGN_SIF || reg==YMAGN_SIF || reg==ZMAGN_SIF){
		comval=value/2.0*0x3FFF;
	}else if(reg==XACCL_OFF || reg==YACCL_OFF || reg==ZACCL_OFF){
		comval=value/3.3;
	}else if(reg==XGYRO_OFF || reg==YGYRO_OFF || reg==ZGYRO_OFF){
		comval=value/0.0125;
	}else if(reg==XMAGN_HIF || reg==YMAGN_HIF || reg==ZMAGN_HIF){
		comval=value/0.5;
	}else{
		std :: cout << "invalid calibration register, please try again\n";
		comval=0;
		throw -1;
	}
	
	uint8_t* comvalPtr = (uint8_t*) &comval;
	char buffer[2];
	IMU_IO( (uint16_t) reg + UPPER_BYTE + comvalPtr[0], buffer, false);
	IMU_IO( (uint16_t) reg + LOWER_BYTE + comvalPtr[1], buffer, false);
}


int initialize(void){
	if (!bcm2835_init()){
		return -1;
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);
	return 0;
}


























