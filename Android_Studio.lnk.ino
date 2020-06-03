#include<LiquidCrystal.h>                   //libraries for lcd

LiquidCrystal lcd(28,29,30,31,32,33);       //pins used for interfacing lcd
#include <ESP8266_Lib.h>                    //libraries for esp8266
#include <BlynkSimpleShieldEsp8266.h>       //libraries for blynk
char auth[] = "62ec27759dcc4af99cb4d8bd80af3d97";   //authentication token for blynk
char ssid[] = "pratiks";                            //username
char pass[] = "#####777";                          //password
#define EspSerial Serial                            //setting esp object
#define ESP8266_BAUD 9600                           //setting baud rate for esp8266

ESP8266 wifi(&EspSerial);                           


#include <dht.h>                                   //include libraries for temp and humidity sensor
dht DHT;                                            //obejct for DHT
#define DHT11_PIN 9                                 //pin no for dht
#define fire_Pin 3                                  //pin no for infra red sensor
int DHTT = 0;                                       //setting values for variables
int tmp = 0;                                  
int hum = 0;
int adc=0;
int mapadc=0;
int fire=0;
int buzzer=52;                                      //set pin no for buzzer
void setup() {  
  
    Serial.begin (9600);                             //begin serial communication with 9600 bauds
    lcd.begin(16,2);                                  //insitalize lcd of 16*2
    lcd.setCursor(0,0);                               //set lcd cursor to o row and o column
    lcd.print("----WELCOME----");                     //print welcome
    delay(1000);                                      //delay
      lcd.setCursor(0,0);
      lcd.print("SMART WAREHOUSE ");
      lcd.setCursor(0,1);
      lcd.print("  MONITORING");
      delay(1000);
      pinMode(buzzer,OUTPUT);
      lcd.setCursor(0,0);
      lcd.print("PLEASE WAIT WIFI");
      lcd.setCursor(0,1);
      lcd.print("  INITIALISING");
      EspSerial.begin(ESP8266_BAUD);
      delay(10);
       Blynk.begin(auth, wifi, ssid, pass);                 //initialize blynk
  }
void loop() {
  
  DHTT = DHT.read11(DHT11_PIN);
  tmp = DHT.temperature;                                        //get reading from DHT11 sensor
  hum = DHT.humidity;
  adc = analogRead(A0);                                         //get analog reading from moisture sensor
  mapadc=map(adc,0,1023,50,0);
  fire=digitalRead(fire_Pin);                                   //get reading from flame sensor
  digitalWrite(buzzer,LOW);                                     //set buzzer =LOW
  lcd.setCursor(0,0);                                            //set curosr to 0,0
  lcd.print("Temp=");
  lcd.print(tmp);
  lcd.print("  Hum=");
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("FIRE=");
  if(fire==0)
  lcd.print("No");
 else
 {  
  digitalWrite(buzzer,HIGH);                                      //if fire is detected set buzzer and display on lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ALERT!!!");
    lcd.setCursor(0,1);
    lcd.print("FIRE DETECTED  ");
    //delay(200);
   }
  //delay(200);
  
  lcd.print(" Moist=");                                          
  if(mapadc==1){
  lcd.print("OK");
  delay(200);}
  else
  {
    
  digitalWrite(buzzer,HIGH);                                          //if moisture is found then turn buzzer on and display 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MaintainMoisture");
  lcd.setCursor(0,1);
  lcd.print("of grains");
  delay(200); 
  }
   Blynk.run(); 
  Blynk.virtualWrite(V0,tmp);                                     //send reading via virtual pin to the blynk app
  Blynk.virtualWrite(V1,hum);                                       //send reading via virtual pin to the blynk app
  Blynk.virtualWrite(V2,fire);                                    //send reading via virtual pin to the blynk app
  Blynk.virtualWrite(V3,mapadc);                                         //send reading via virtual pin to the blynk app
  //delay(200);
}
