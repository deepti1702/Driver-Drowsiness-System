#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 =11 , d5 = 10, d6 =9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int PS2187_sensor = A2;
int psrPin = A0;    
int psrReading;     
int analog =1023;
int heartrate =A3;
int hrtReading;
const int lm35_pin = A1;  /* LM35 O/P pin */

void setup() 
{
  pinMode(A0,INPUT); //PRESSURE
  pinMode(A1,INPUT); //temp
  pinMode(A3,INPUT); //PULSE
  pinMode(2,OUTPUT);  //BUZZOR
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
  lcd.print("DRIVER !");
 lcd.setCursor(0,1); 
 lcd.println("DROWSINESS ");
  delay(2000);   
  lcd.clear(); 
}
 
void loop()
{
  int breatheValue = 0; 
  for (int i = 0; i < 32; i++) 
  {
    breatheValue += analogRead( PS2187_sensor); 
    } 
   breatheValue >>= 5; 
  Serial.print("BREATHING V:"); 
  Serial.println(breatheValue); 
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("BREATHING V:");
  lcd.println(breatheValue);
  delay(1000);
  lcd.clear();
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print("Temperature = ");
  Serial.print(temp_val/10);
  Serial.print(" Degree Celsius\n");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("TEMPERATURE:");
  lcd.print(temp_val/10);
  delay(1000);
  lcd.clear();
 psrReading = analogRead(psrPin);  
 Serial.print("pressure :");
 Serial.println(analog-psrReading);
 lcd.setCursor(0,0); 
 lcd.print("pressure :");
 lcd.println(analog-psrReading);
 if (breatheValue> 500) { 
  Serial.println(" HIGHER  ");
   Serial.println(" HIGHER  ");
   digitalWrite(2,HIGH);
   lcd.setCursor(0,0);
   lcd.print("HIGHER:");
   delay(1000);
   lcd.clear();
  }
 hrtReading = analogRead(heartrate);  
 hrtReading =hrtReading-420;
 Serial.print("Heart rate :");
 Serial.println(hrtReading);
 lcd.setCursor(0,1); 
 lcd.print("Heart rate:");
 lcd.println(hrtReading);
 delay(1000);

if ((temp_val/10)>38)
{ 
   Serial.println(" TEMP HIGH  ");
   digitalWrite(2,HIGH);
   lcd.setCursor(0, 0);
   lcd.print("HEMP HIGH:");
   delay(1000);
   lcd.clear();
  } 
  else
  {
     digitalWrite(2,LOW);
  }
if ((analog-psrReading)>500)
{ 
   Serial.println("PRESSURE HIGH  ");
   digitalWrite(2,HIGH);
   lcd.setCursor(0, 0);
   lcd.print("PRESSURE HIGH:");
   delay(1000);
   lcd.clear();
  } 
  else
  {
     digitalWrite(2,LOW);
  }
  
}
