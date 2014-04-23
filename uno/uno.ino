#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TWO_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
OneWire twoWire(TWO_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature tempSensor(&oneWire);
DallasTemperature tempWSensor(&twoWire);

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  tempSensor.begin();
  tempWSensor.begin();
  
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus

  tempSensor.requestTemperatures(); // Send the command to get temperatures
  tempWSensor.requestTemperatures();
  
  Serial.print("T: ");
  Serial.println(tempSensor.getTempCByIndex(0));  
  Serial.print("WT: ");
  Serial.println(tempWSensor.getTempCByIndex(0));  
}
