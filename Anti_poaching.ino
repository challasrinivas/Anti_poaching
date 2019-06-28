
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13); 
SoftwareSerial gsm(5,6); //RX,TX

int temp = A0;
int sound = 7;
int buzzer = 6;
int water = 5;

int x=A1;  
int y=A2;
int z=A3;

float x1,y1,z1;
float a,b,c;

void setup() {

  Serial.begin(9600);
  pinMode(temp,INPUT);  
  pinMode(sound,INPUT); 
  pinMode(buzzer,OUTPUT);
  pinMode(water,OUTPUT);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WELCOME TO");
  lcd.setCursor(1,0);
  lcd.print("ANTI-POACHING");
 delay(1000);
}
void loop() {
  Checktempcondition();
  Checktiltcondition();
  CheckSoundCondition();
  SendTextsms();
  }
/* -------SOUND SENSOR   */

void  CheckSoundCondition()
{
  int s=digitalRead(sound);
  if(s==HIGH)
  {
    Serial.println("cutting trees in forest");
    delay(100);
    digitalWrite(buzzer,HIGH);
    delay(2000);
    digitalWrite(buzzer,LOW);
    SendTextsms();
  }
  else
  {
    Serial.println("sound normal condition in forest");
    delay(100);
    digitalWrite(buzzer,LOW);
  }
}
/*----   TEMPERATURE SENSOR  -----*/


void Checktempcondition()
{
  int val=analogRead(temp);
  int t= val*0.48/2;
  delay(1000);
  if( t>50)
{
  Serial.println(" FIRE OCCURED IN FOREST ");
  delay(100);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("FIRE OCCURED");
  delay(100);
  digitalWrite(water,HIGH);
  Serial.println(" WATER ACTIVATED  ");
  delay(1000);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  SendTextsms();
 }
 else
 {
  Serial.println(" FIRE IS NOT OCCURED ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("FIRE IS NOT OCCURED");
  delay(1000);
  digitalWrite(water,LOW);
  delay(1000);
   }
}
/*------ TILT SENSOR -------*/

void Checktiltcondition()
{
a=analogRead(x);    // reads the sensor output (Vout of accelerometer)3=analogRead(x,y,z);
b=analogRead(y);
c=analogRead(z);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("x: ");
lcd.print(a);
Serial.print("x: ");
Serial.print(a);
delay(3000);

lcd.print("y: ");
lcd.print(b);
Serial.print("y: ");
Serial.print(b);
delay(3000);

lcd.setCursor(1, 1);
lcd.print("z: ");
lcd.println(c);
Serial.print("z: ");
Serial.print(c);
delay(3000);

if (a >= 350 && a <= 360)
{
  lcd.clear();
  lcd.println("normal condition in forest ");
  Serial.println("normal condition in forest");
  digitalWrite(buzzer,LOW);
  delay(3000);
}
else if(b >=350 && b<=360)
{
   lcd.clear();
   lcd.println("normal condition in forest ");
   Serial.println("normal condition in forest ");
   digitalWrite(buzzer,LOW);
   delay(3000);
}
else if(c >=410 && c <= 430)
{  
  lcd.clear();
  lcd.println("normal condition in forest ");
  Serial.println("normal condition in forest ");
  digitalWrite(buzzer,LOW);
  delay(3000);
}

else
{
  lcd.clear();
  lcd.println("cutting trees in forest");
  Serial.println(" cutting trees in forest ");
  digitalWrite(buzzer,HIGH);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("BUZZER HIGH");
  Serial.println("BUZZER HIGH");
  delay(100);
  SendTextsms();
}
}
void SendTextsms()
{
  gsm.println("AT+CMGF=1"); //to send SMS in text mode
  delay(500);
  gsm.println("AT+CMGS=\"+916300069543\"\r"); //change the phone number by user
  delay(500);
  gsm.println("CUTTING TREES IN FOREST");     //content in the sms
  delay(5000);
  gsm.println((char)26);  //the stoping character
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("sending sms ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("CUTTING TREES ");
  lcd.setCursor(1,0);
  lcd.println(" IN FOREST");
  delay(1000);
  Serial.println("CUTTING TREES IN FOREST");
  delay(1000);
}
 
