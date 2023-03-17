void motorControl(uint8_t R,uint8_t L) {
 if(R <= 0) {
  R = abs(R);
   analogWrite(IN1,0); analogWrite(IN2,R);
 }
 else {
   analogWrite(IN1,R); analogWrite(IN2,0);
 }
 if(L <= 0) {
  L = abs(L);
   analogWrite(IN3,0); analogWrite(IN4,R);
 }
 else {
   analogWrite(IN3,R); analogWrite(IN4,0);
 }
}
void Servo() {
   digitalWrite(S1,HIGH); delayMicroseconds(delay_S1); digitalWrite(S1,LOW);
   digitalWrite(S2,HIGH); delayMicroseconds(delay_S2); digitalWrite(S2,LOW);
   digitalWrite(S3,HIGH); delayMicroseconds(delay_S2); digitalWrite(S3,LOW);
   digitalWrite(S4,HIGH); delayMicroseconds(delay_S2); digitalWrite(S4,LOW);
   ControlActive = 1;
}
void buzzer(uint8_t r) {
    for(int i = 0 ; i <= r ; i++) {
      digitalWrite(Buzzer,HIGH);
      delay(45);
      digitalWrite(Buzzer,LOW);
    }
}
void FaceControl(char snap) {
   if(snap == 'N') { //Normal 
 /* display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(40,30);             
  display.println("Oled Ready !");
  display.display();*/
   }
   if(snap == 'W') { // Warn
 /* display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(40,30);             
  display.println("Oled Ready !");
  display.display();*/
   }
   if(snap == 'R') { // Repair
 /* display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(40,30);             
  display.println("Oled Ready !");
  display.display();*/
   }
   if(snap == 'L') { //Low Battery
 /* display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(40,30);             
  display.println("Oled Ready !");
  display.display();*/
   }
   if(snap == 'L') {
   }
}
void Gyro(void)   
{ 
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); 
  
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);     //Hızlanma
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation     X: ");   //Döndürme
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println(""); 
}