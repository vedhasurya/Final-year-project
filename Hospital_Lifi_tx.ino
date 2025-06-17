#include<SoftwareSerial.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include "DHT.h"

#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

#define DHTPIN 7
#define DHTTYPE DHT11
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;

uint32_t tsLastReport = 0;
String data;
float Hr,SpO2,t;

int16_t ax, ay, az;
int16_t gx, gy, gz;
SoftwareSerial mySerial(2,3);
DHT dht(DHTPIN, DHTTYPE);
void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    dht.begin();
    Wire.begin(); 
    mpu.initialize();
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    
  pox.setOnBeatDetectedCallback(onBeatDetected);
  mpu.setXAccelOffset(0); //Set your accelerometer offset for axis X
  mpu.setYAccelOffset(0); //Set your accelerometer offset for axis Y
  mpu.setZAccelOffset(0); //Set your accelerometer offset for axis Z
  mpu.setXGyroOffset(0);  //Set your gyro offset for axis X
  mpu.setYGyroOffset(0);  //Set your gyro offset for axis Y
  mpu.setZGyroOffset(0);

}

void loop()
{
  
    pox.update();
     mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        t = dht.readTemperature(true);
        Hr=pox.getHeartRate();
        SpO2=pox.getSpO2();
        Serial.println("%");
        data=String(Hr)+","+String(SpO2)+","+String(t)+","+String(ax);
        Serial.println(data);
        mySerial.println(data);
        tsLastReport = millis();
        
  }
}
