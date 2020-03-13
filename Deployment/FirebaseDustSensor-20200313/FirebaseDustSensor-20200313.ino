// INSTANCE IDENTITY
String instancePrefix = "DustStation_";
String instanceNo = "TEST"; 

// Firebase
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// PMS Module
#include "PMS.h"

// SETUP
#define FIREBASE_HOST "XXXXXXXXXXX"
#define FIREBASE_AUTH "XXXXXXXXXXX"
#define WIFI_SSID "XXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXX"
#define sensorInterval 15000
#define sendingInterval 300000

PMS pms(Serial);
PMS::DATA data;

String instancePath;

void setup() {
  
  Serial.begin(9600);
  pms.passiveMode();

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
  instancePath = instancePrefix + instanceNo;
}


void loop() {
  
  pms.wakeUp();
  
  float pm1_0 = 0;
  float pm2_5 = 0;
  float pm10 = 0;
  
  delay(sensorInterval);

  pms.requestRead();
  
  if (pms.readUntil(data)) {
    pm1_0 = data.PM_AE_UG_1_0;
    pm2_5 = data.PM_AE_UG_2_5;
    pm10 = data.PM_AE_UG_10_0;
    
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(pm1_0);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(pm2_5);
    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(pm10);
    
  } else {
    Serial.println("No PMS data");
  }
  
  Serial.println("Sending...");

  StaticJsonBuffer<50> timestampBuffer;
  JsonObject& timeStampObject = timestampBuffer.createObject();
  timeStampObject[".sv"] = "timestamp";
  
  StaticJsonBuffer<200> dataBuffer;
  JsonObject& dataObject = dataBuffer.createObject();
  
  dataObject["pm1_0"] = pm1_0;
  dataObject["pm2_5"] = pm2_5;
  dataObject["pm10"] = pm10;
  dataObject["timestamp"] = timeStampObject;
     
  Firebase.set(instancePath+"/lastUpdate", timeStampObject);
  Firebase.push(instancePath, dataObject);

  pms.sleep();
  delay(sendingInterval);
}
