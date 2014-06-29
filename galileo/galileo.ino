#include <comAPI.h>

#define LightS 0  //Light Sensor pin
#define MoisS 1 //moisture sensor pin 
#define WaterS1 2 //Water level sensor 1 pin 
#define PhS 3
#define WaterS2 4 //Water level sensor 2 pin
#define relayNum 9 //the number of relay
#define relayoffset 3 // offset from 0
bool relay[relayNum];

void setup(){
  Serial.begin(9600);
  for (int i = 0;i < relayNum;i++){
    relay[i] = false;
    pinMode(i + relayoffset,OUTPUT);
  }
}
void loop(){
  // SerialPrint();
  SerialRead();
  relayPrint();
}


void SerialPrint(){
  struct DAT ls,ms,ws1,phs,ws2;
  ls.id = ID_SRL0;
  int a = analogRead(LightS)*10;
  ls.dat = a;


  ms.id = ID_SHU0;
  a = analogRead(MoisS)*10;
  ms.dat = a;


  ws1.id = ID_SWL0;
  a = analogRead(WaterS1)*10;
  ws1.dat = a;


  phs.id = ID_SPH1;
  a = analogRead(PhS)*10;
  phs.dat = a;


  ws2.id = ID_SWL1;
  a = analogRead(WaterS2)*10;
  ws2.dat = a;


  Serial.print(ls.id,DEC);
  Serial.print(ls.dat,DEC);
  Serial.print(" ");

  Serial.print(ms.id,DEC);
  Serial.print(ms.dat,DEC);
  Serial.print(" ");

  Serial.print(ws1.id,DEC);
  Serial.print(ws1.dat,DEC);
  Serial.print(" ");

  Serial.print(phs.id,DEC);
  Serial.print(phs.dat,DEC);
  Serial.print(" ");

  Serial.print(ws2.id,DEC);
  Serial.print(ws2.dat,DEC);
  Serial.print(" ");

  Serial.print(0x08,DEC);
      	FILE *fp;
      	 //继电器状态
    	  fp = fopen("/home/galileo", "r");
    	  int i = 0;
 		    if(fp!= NULL){
    	   while( feof(fp) == 0){
      		  Serial.print(fgetc(fp),DEC);
      		  i++;
      		  if(i == relayNum){
        	   	break;
      		  }
    	   }
        }
    	  fclose(fp);
  Serial.println();
}

void SerialRead(){
  if(Serial.available() == 2){ 


    struct CMD cd;
    cd.id = Serial.read(); 
    delay(2);
    cd.ctr = Serial.read();
    switch(cd.id){
    case 0x00: //获取传感器信息
      if(cd.ctr == 0x00){
        SerialPrint();
      }
      break;

       //控制继电器
    case ID_FFSH:
    case ID_PACI:
    case ID_PALK:
    case ID_LFLU: 
    case ID_PSUP:
    case ID_PREC:
    case ID_POXY:
    case ID_PFLW:
    case ID_LIFR:
      if (cd.ctr == ON){
        relay[cd.id - relayoffset] = true;
      }
      if (cd.ctr == OFF){
        relay[cd.id - relayoffset] = false;
      }
      break;
    case ID_LRED:
    case ID_LBLE:
      break;
      // default:
      //return err
    }
    FILE *fp;
    fp = fopen("/home/galileo", "w"); 
    if(fp != NULL){
      for (int i = 0; i < relayNum; i ++){
        fputc(relay[i],fp);
      }
      fclose(fp);
    }
  }  
  while(Serial.available() ){
    Serial.read();
  }

}

void relayPrint(){
  FILE *fp;

  fp = fopen("/home/galileo", "r"); 
  int i = 0;
  if(fp!= NULL){
    while(feof(fp) == 0){
      relay[i] = fgetc(fp);
      i++;
      if(i == relayNum){
        break;
      }
    }
    fclose(fp);
  }
  for( i = 0; i < relayNum; i++){
    if(relay[i]){
      digitalWrite(i + relayoffset,LOW);
    }
    else{
      digitalWrite(i + relayoffset,HIGH);
    }
  }
}




