#include <iostream>
#include <sys/types.h>
#include <command.h>
#include <piCam.h>
#include <serialMessage.h>
#include <time.h>

//How long before first action
#define LONG_WAIT 

//How many seconds between repeated actions
#define REPEAT_FREQ 

//How many times to repeat the action
#define REPEAT_COUNT  

using namespace std;



int main(){
	cout << "\nRunning Timing Control: Press any key and 'enter' to abort.\n";
	
	
	pid_t childId;
	childId = fork();
	if (childId == 0){ //Is child, checks for keyboard interrupt
	char dummy;
	dummy >> cin;
	return 0;
}
	else{
		timespec time1, time2;
		time1.tv_sec = LONG_WAIT;
		time1.tv_nsec = 0;
		nanosleep(&time1, &time2);
	
		cout << "Doing important thing\n";
		
		burst();
		camLong();
		burst();
		
		time1.tv_sec = REPEAT_FREQ;
		for (int i = 0; i < REPEAT_COUNT; i++){
			nanosleep(&time1, &time2);
			cout << "Doing something else important";
			burst();
			camShort();
			burst();
		}
	}
	return 0;
}