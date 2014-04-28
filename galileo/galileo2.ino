#include <comAPI.h>

#define LightS 0	//Light Sensor pin
#define	MoisS 1	//moisture sensor pin 
#define WaterS1 2 //Water level sensor 1 pin 
#define PhS 3
#define WaterS2 4	//Water level sensor 2 pin
#define relayNum 7 //the number of relay
int relay[7] =  {2,3,4,5,6,7,8};

void setup(){
	Serial.begin(9600);
	for int i = 0;i < relayNum;i++{
		pinMode(relay[i],OUTPUT);
	}
}