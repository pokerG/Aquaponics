#define relay 3
void setup(){
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop(){
  static int a;
  if(Serial.available()){
    a = Serial.read()-48;
  }
  Serial.println(a);
  if(a){
    digitalWrite(relay,HIGH);
  }else{
    digitalWrite(relay,LOW);
  }
}
