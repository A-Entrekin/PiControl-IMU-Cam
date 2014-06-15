#ifndef PICAM_H_
#define PICAM_H_
#include "serialMessage.h"
#include <stdlib.h>
#include <string>
#include <sstream>

FILE* camLong(struct timeval *time);

FILE* camShort(struct timeval *time);

struct serial_t tagFile(FILE* file, std::string tag, long time);

#endif PICAM_H