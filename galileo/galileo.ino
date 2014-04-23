
#define lightSensor 0
#define moiatureSensor 1
/*
   # 0  ~300     dry soil   
   # 300~700     humid soil   
   # 700~950     in water 
*/
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  Serial.print("L: ");
  Serial.println(analogRead(lightSensor));
  Serial.print("M: ");
  Serial.println(analogRead(moiatureSensor));
  delay(100);
  
}
