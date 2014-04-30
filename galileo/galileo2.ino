#include <comAPI.h>

#define LightS 0	//Light Sensor pin
#define	MoisS 1	//moisture sensor pin 
#define WaterS1 2 //Water level sensor 1 pin 
#define PhS 3
#define WaterS2 4	//Water level sensor 2 pin
#define relayNum 7 //the number of relay
int relay[7] =  {
  4,5,6,7,8,9,10};

void setup(){
  Serial.begin(9600);
  for (int i = 0;i < relayNum;i++){
    pinMode(relay[i],OUTPUT);
  }
}
void loop(){
  SerialPrint();
  SerialRead();
}

void SerialPrint(){
  struct DAT ls,ms,ws1,phs,ws2;
  ls.id = ID_SRL0;
  int a = analogRead(LightS)*100;
  ls.hdat = a >> 8;
  ls.ldat = a & 0x00ff;

  ms.id = ID_SHU0;
  a = analogRead(MoisS)*100;
  ms.hdat = a >> 8;
  ms.ldat = a & 0x00ff;

  ws1.id = ID_SWL0;
  a = analogRead(WaterS1)*100;
  ws1.hdat = a >> 8;
  ws1.ldat = a & 0x00ff;

  phs.id = ID_SPH1;
  a = analogRead(PhS)*100;
  phs.hdat = a >> 8;
  phs.ldat = a & 0x00ff;

  ws2.id = ID_SWL1;
  a = analogRead(WaterS2)*100;
  ws2.hdat = a >> 8;
  ws2.ldat = a & 0x00ff;

  Serial.print(ls.id,HEX);
  Serial.print(ls.hdat,HEX);
  Serial.print(ls.ldat,HEX);
  Serial.println();

  Serial.print(ms.id,HEX);
  Serial.print(ms.hdat,HEX);
  Serial.print(ms.ldat,HEX);
  Serial.println();

  Serial.print(ws1.id,HEX);
  Serial.print(ws1.hdat,HEX);
  Serial.print(ws1.ldat,HEX);
  Serial.println();

  Serial.print(phs.id,HEX);
  Serial.print(phs.hdat,HEX);
  Serial.print(phs.ldat,HEX);
  Serial.println();

  Serial.print(ws2.id,HEX);
  Serial.print(ws2.hdat,HEX);
  Serial.print(ws2.ldat,HEX);
  Serial.println();
}

void SerialRead(){
  if(Serial.available()){ 
    struct CMD cd;
    cd.id = Serial.read(); 
    delay(2);
    cd.ctr = Serial.read();
    switch(cd.id){
    case ID_PACI:
    case ID_PALK:
    case ID_LFLU: 
    case ID_PSUP:
    case ID_PREC:
    case ID_POXY:
    case ID_PFLW:
      if (cd.ctr == ON){
        digitalWrite(cd.id,HIGH);
      }
      if (cd.ctr == OFF){
        digitalWrite(cd.id,LOW);
      }
      break;
    case ID_LRED:
    case ID_LBLE:
    case ID_FFSH:
      break;
      // default:
      //return err
    }
  }

}

