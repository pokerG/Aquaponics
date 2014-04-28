#include <comAPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define TWO_WIRE_BUS 3
// Setup Wire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
OneWire twoWire(TWO_WIRE_BUS);
// Pass our Wire reference to Dallas Temperature. 
DallasTemperature tempSensor(&oneWire);
DallasTemperature tempWSensor(&twoWire);

void setup(){
	Serial.begin(9600);
	tempSensor.begin();
  	tempWSensor.begin();
}

void loop(){
	SerialPrint();
}

void SerialPrint(){
	struct DAT ts,wts;	//Temps WTemps data struct
	ts.id = ID_STP0;
	wts.id = ID_STP1;
	tempSensor.requestTemperatures(); // Send the command to get temperatures
  	tempWSensor.requestTemperatures();
	int a0 = tempSensor.getTempCByIndex(0)*100;
	int a1 = tempWSensor.getTempCByIndex(0)*100;
	ts.hdat = a0 >> 8;
	ts.ldat = a0 & 0x00ff;
	wts.hdat= a1 >> 8;
	wts.ldat = a1 & 0x00ff;
	Serial.print(ts.id);
	Serial.print(ts.hdat,HEX);
	Serial.print(ts.ldat,HEX);
	Serial.println();

	Serial.print(wts.id,HEX);
	Serial.print(wts.hdat,HEX);
	Serial.print(wts.ldat,HEX);
    Serial.println();

}
void serialEvent(){
	Serial.read();
}