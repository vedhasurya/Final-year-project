#define BLYNK_TEMPLATE_ID "TMPL3BFqjOtTW"
#define BLYNK_TEMPLATE_NAME "LIFI"
#define BLYNK_AUTH_TOKEN "zET0piORCCrWLyAP2pF6055dkadKM9Y8"

#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

WiFiClient client;
char auth[] = "zET0piORCCrWLyAP2pF6055dkadKM9Y8";
char ssid[] = "iotdata";
char pass[] = "12345678";

#include<SoftwareSerial.h>
SoftwareSerial mySerial(14, 27);
int temp,Hr,ax,SpO2;
String dat;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("wifi connecting.....");
  Blynk.begin(auth,ssid,pass);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("wifi connected");
  delay(300);
  lcd.clear();
  lcd.print("LIFI RECEIVER");
  delay(1000);
 }

void loop() {
  Blynk.run();
  if(mySerial.available()>0){
  dat = mySerial.readStringUntil('\n');
  Serial.print("dat = ");
  Hr=dat.substring(0,dat.indexOf(',')).toInt();
  dat.remove(0,dat.indexOf(',')+1);
  SpO2=dat.substring(0,dat.indexOf(',')).toInt();
  dat.remove(0,dat.indexOf(',')+1);
  temp=dat.substring(0,dat.indexOf(',')).toInt();
  dat.remove(0,dat.indexOf(',')+1);
  ax=dat.substring(0,dat.indexOf(',')).toInt();
  dat.remove(0,dat.indexOf(',')+1);
  }
  
  Serial.print("Hr= ");
  Serial.println(Hr);
  Serial.print("SpO2 =");
  Serial.println(SpO2);
  Serial.print("temp= ");
  Serial.println(temp);
  Serial.print("ax= ");
  Serial.println(ax);
  Serial.print("dat =");
  Serial.println(dat);
  
  
  Blynk.virtualWrite(V0,Hr);
  Blynk.virtualWrite(V1,SpO2);
  Blynk.virtualWrite(V2,temp);
  Blynk.virtualWrite(V3,ax);

  if(Hr>120){
    Blynk.logEvent("Hr","HIGH HEART RATE ALERT");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HIGH HEART");
    lcd.setCursor(0,1);
    lcd.print("ALERT");
    delay(500);
    }
  else if(temp>100){
    Blynk.logEvent("temp","HIGH TEMPERATRUE ALERT");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HIGH TEMPERATURE");
    lcd.setCursor(0,1);
    lcd.print("ALERT");
    delay(500);
    }
    else{
      dis();
      }
      Blynk.virtualWrite(V0,Hr);
      Blynk.virtualWrite(V2,temp);
      Blynk.virtualWrite(V3,ax);
      Blynk.virtualWrite(V1,SpO2);

}

void dis(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HR = ");
  lcd.print(Hr);
  lcd.setCursor(0,1);
  lcd.print("SpO2 = ");
  lcd.print(SpO2);
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Ax = ");
  lcd.print(ax);
  delay(500);
  }
