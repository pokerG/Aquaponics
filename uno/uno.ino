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

int motorSpeed = 1200;  //能够设定步进速度
int countsperrev = 512; // 一圈的步数
int lookup[8] = {
  B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

struct stepper{
  int IN1;	// Blue   - 28BYJ48 pin 1
  int IN2;	// Pink   - 28BYJ48 pin 2
  int IN3;	// Yellow - 28BYJ48 pin 3
  int IN4;	// Orange - 28BYJ48 pin 4
}sp[3];

void setup(){
  Serial.begin(9600);
  tempSensor.begin();
  tempWSensor.begin();
  sp[0].IN1 = 10;
  sp[0].IN2 = 11;
  sp[0].IN3 = 12;
  sp[0].IN4 = 13;
  sp[1].IN1 = 6;
  sp[1].IN2 = 7;
  sp[1].IN3 = 8;
  sp[1].IN4 = 9;
  sp[2].IN1 = 14;
  sp[2].IN2 = 15;
  sp[2].IN3 = 16;
  sp[2].IN4 = 17;
  
  for(int i = 6;i <= 17;i++){
    pinMode(i,OUTPUT);
  }
}

void loop(){
  // SerialPrint();
}

void SerialPrint(){
  struct DAT ts,wts;	//Temps WTemps data struct
  ts.id = ID_STP0;
  wts.id = ID_STP1;
  tempSensor.requestTemperatures(); // Send the command to get temperatures
  tempWSensor.requestTemperatures();
  int a0 = tempSensor.getTempCByIndex(0)*100;
  int a1 = tempWSensor.getTempCByIndex(0)*100;
  ts.dat = a0;
  wts.dat = a1;

  Serial.print(ts.id,DEC);
  Serial.print(ts.dat,DEC);
  Serial.print(" ");

  Serial.print(wts.id,DEC);
  Serial.print(wts.dat,DEC);
  Serial.println();

}

void serialEvent(){
	if(Serial.available()){
		struct CMD cd;
  cd.id = Serial.read();
  delay(2);
  cd.ctr = Serial.read();
  if(cd.id == 0x00 && cd.ctr == 0x00){
  	SerialPrint();
  }else{
  	wise(cd);
  }
	}
  while(Serial.available() ){
    Serial.read();
  }
  
}


void wise(struct CMD cd){
  int d = cd.ctr >>7;
  int snum = cd.ctr  & 0x7F;

  if(d){
    for(int i = 0;i < snum;i++){
      clockwise(sp[cd.id - 1]);

    }
  }
  else{
    for(int i = 0;i < snum;i++){
      anticlockwise(sp[cd.id - 1]);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////
//将连接到 ULN2003 的针脚按照从1 到 4的顺序依次设置为高
// 在每次针脚设置的间隙，延迟一段"motorSpeed"的时间 (来控制速度)
//以下为定义顺反时针旋转函数
void anticlockwise(struct stepper s)
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i,s);
    delayMicroseconds(motorSpeed);
  }
}
//以下为定义顺时针旋转函数
void clockwise(struct stepper s)
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i,s);
    delayMicroseconds(motorSpeed);
  }
}
//以下为定义顺时针旋转函数
void setOutput(int out,struct stepper s)
{
  digitalWrite(s.IN1, bitRead(lookup[out], 0));
  digitalWrite(s.IN2, bitRead(lookup[out], 1));
  digitalWrite(s.IN3, bitRead(lookup[out], 2));
  digitalWrite(s.IN4, bitRead(lookup[out], 3));
}


