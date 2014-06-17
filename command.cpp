#include "command.h"


//#define CM_DBUG

const timespec stall={0,9};


void load16Buffer(uint16_t source, char* buffer){
	buffer[0] = source / 32;
	buffer[1] = source % 32;
	return;
}



void burst(){
#ifdef CM_DBUG
	std::cout << "Bursting\n";
	timespec times[2];
	times->tv_sec = 2;
	times->tv_nsec = 0;
	nanosleep(times, times+1);
#else
	//23 bytes to send and receive burst mode info.
	char buffer[23];
	load16Buffer((uint16_t) 0x3E00, buffer);
	bcm2835_spi_transfern(buffer, 23);
	static timespec rem;
	nanosleep(stall, rem);
#endif
	return;
}



int initialize(void){
#ifdef CM_DBUG
	std::cout << "Initializing\n";
#else

	if (!bcm2835_init()){
		return -1;
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);
#endif
	return 0;
}


























