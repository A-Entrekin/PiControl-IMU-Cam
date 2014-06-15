#ifndef SERIALMESSAGE_H_
#define SERIALMESSAGE_H_

#include "bcm2835.h"
#include <sys/time.h>

struct serial_t {
	char* message;
	int length;
	struct timeval time;
};


void send(struct serial_t mess);


#endif /*SERIALMESSAGE_H_*/
