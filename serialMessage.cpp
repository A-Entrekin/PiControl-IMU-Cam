#include "serialMessage.h"


void send(struct serial_t mess){
	char timeStamp[sizeof(long) + 7];
	timeStamp[0] = '<';
	timeStamp[1] = 't';
	timeStamp[2] = '>';
	char* ptr + 3 = timeStamp;
	(*long) ptr = mess.time;
	ptr += sizeof(long);
	ptr[0] = '<';
	ptr[1] = '/';
	ptr[2] = 't';
	ptr[3] = '>';
	ptr = timeStamp;
	//TODO: Fix output port
	bcm2835_spi_transfern(ptr, sizeof(long) + 7);
	bcm2835_spi_transfern(mess.message, mess.length);
	free(mess.message);
}