String ph = "";

void setup(){
  Serial.begin(9600);
  while(Serial.available() == 0){
    
  }
  ph = Serial.readString();
}
void loop(){
  Serial.println(ph.toInt()+5);
}
