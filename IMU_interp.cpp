
#include "IMU_interp.h"

using namespace std;

void diagstat(uint16_t data){

		if ((data >> 15) & 1 == 1) cout<<"Z-axis acceleromenter self-test failure.\n";
		else cout<<"Z-axis accelerometer self-test pass.\n";
		

		if ((data >> 14) & 1 == 1) cout<<"Y-axis acceleromenter self-test failure.\n";
		else cout<<"Y-axis accelerometer self-test pass.\n";
		

		if ((data >> 13) & 1 == 1) cout<<"X-axis acceleromenter self-test failure.\n";
		else cout<<"X-axis accelerometer self-test pass.\n";

		
		if ((data >> 12) & 1 == 1)cout<<"Z-axis gyroscope self-test failure.\n";
		else cout<<"Z-axis gyroscope self-test pass.\n";
		

		if ((data >> 11) & 1 == 1) cout<<"Y-axis gyroscope self-test failure.\n";
		else cout<<"Y-axis gyroscope self-test pass.\n";
		

		if ((data >> 10) & 1 == 1) cout<<"X-axis gyroscope self-test failure.\n";
		else cout<<"X-axis gyroscope self-test pass.\n";
		

		if ((data >> 9) & 1 == 1) cout<<"Alarm 2 status active.\n";
		else cout<<"Alarm 2 status inactive.\n";
		

		if ((data >> 8 )& 1 == 1) cout<<"Alarm 1 status active.\n";
		else cout<<"Alarm 1 status inactive.\n";
		

		if ((data >> 6 )& 1 == 1)cout<<"Flash test, checksum, failed.\n";
		else cout<<"Flash test, checksum, passed.\n";

		
		if ((data >> 5) & 1 == 1)cout<<"Self-test diagnostic error fail.\n";
		else cout<<"Self-test diagnostic error pass.\n";
		

		if ((data >> 4) & 1 == 1) cout<<"Sensor outside range bounds.\n";
		else cout<<"Sensor wihtin range bounds.\n";
		

		if ((data >> 3) & 1 == 1) cout<<"SPI communication failure.\n";
		else cout<<"No SPI communication failure.\n";
		

		if ((data >> 2 )& 1 == 1) cout<<"Flash update failure.\n";
		else cout<<"No flash update failure.\n";
		

		if ((data >> 1 )& 1 == 1) cout<<"Power supply above 5.25 volts.\n";
		else if (data & 1 == 1) cout<<"Power supply below 4.75 Volts.\n";
		else cout<<"Power supply fine.\n";
		return;
}


int errorbits(uint16_t data){
	if (data >> 15 & 1 == 1) return 1; //This data has not yet been updated since the last time it was read.
	else if (data >> 14 & 1 == 1) return 2; //There is an error.  Check DIAG_STAT to see what it is\n
	return 0;
}


//Little helper method for fixing the two's complement form of IMU output
int16_t negCheckAndPad(uint16_t input, int bits){
	assert(bits >= 0);
	if ( (input >> (15-bits)) & 1 == 1){
		int16_t output = (int16_t) input;
		for (int i = 16 - bits; i < 16; i++) output &= 1<<i;
		return output;
	}
	else return (int16_t) input;
}



int genInterp(Register reg, uint16_t data, double *result){
	int err = errorbits(data);
	if (err != 0) return err;
	switch (reg){
	case SUPPLY_OUT:
		*result = (double) negCheckAndPad(data, 2) * 2.42/1000.0; //Volts
		return 0;
	case XACCL_OUT:
	case YACCL_OUT:
	case ZACCL_OUT:
		*result = (double) negCheckAndPad(data, 2) *10.0/1000.0*9.81;  //m/s^2
		return 0;
	case XMAGN_OUT:
	case YMAGN_OUT:
	case ZMAGN_OUT:
		*result = (double) negCheckAndPad(data, 2) *0.5/1000.0;  //gauss
		return 0;
	case TEMP_OUT:
		*result = (double) 25.0+ negCheckAndPad(data, 4)*0.14;  //degc
		return 0;
	case AUX_ADC:
		*result = (double) negCheckAndPad(data, 4) * 0.81/1000.0;  //Volts
		return 0;
	default:
		return 3; //Undefined register
					
	}
}


int gyroInterp(uint16_t data, Range range, double *result){
	int err = errorbits(data);
	if (err != 0) return err;
	else if (range==pm300)
		*result= (double) negCheckAndPad(data, 2)*0.05;  
		//deg per sec
	
	else if (range==pm150)
		*result= (double) negCheckAndPad(data, 2)*0.025;  
		//deg per sec
	
	else if(range==pm75)
		*result= (double) negCheckAndPad(data, 2)*0.0125; 
		//deg per sec
		
	else return 3; //Unidentified range value
	return 0;
					
}