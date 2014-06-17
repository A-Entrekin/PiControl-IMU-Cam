#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "command.h"
#include <time.h>

//How long before first action
#define LONG_WAIT 15

using namespace std;

//#define CM_DBUG

int main(){
	cout << "\nRunning R.Pi Balloon Control: Press Ctr+C to abort.\n";

	time_t then = time(NULL);
	time_t now = time(NULL);
	initialize();
	while (difftime(now, then) < LONG_WAIT){
		now = time(NULL);
		burst();
	}

#ifdef CM_DBUG
	cout << "Launching camera command\n";
#else
	//10800000 = 3 hours * 60min/1hour * 60sec/1min * 1000ns/s, film duration.
	//-n = no preview
	//-f 30 = thirty frames per second
	system("raspivid -n -f 30 -t 10800000 -o flight_video.h264 &"); //May need to remove ampersand
#endif
	
	while (true) burst();
	
	
	return 0;
}
