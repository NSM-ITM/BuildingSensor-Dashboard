// INSTANCE IDENTITY
String instancePrefix = "AHU";
String instanceNo = "1-5"; 


// Firebase
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// SENSOR
#include "DHT.h" 

// SETUP
#define FIREBASE_HOST "XXXXXXXXXXXXX"
#define FIREBASE_AUTH "XXXXXXXXXXXXX"
#define WIFI_SSID "XXXXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXXXX"
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 4
#define sensorInterval 15000
#define sendingInterval 300000

DHT dht(dht_dpin, DHTTYPE); 
String instancePath;

void setup() {
  
  Serial.begin(115200);

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
  //timeClient.update();
  Serial.println("Reading...");
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  //delay(5000);  // short interval for debug
  delay(sensorInterval);

  Serial.println("curent humidity: " + (String) h);
  Serial.println("curent temperature: " + (String) t);
 // Serial.println("curent timestamp: " + (String) epochTime);
  
  Serial.println("Sending...");

  StaticJsonBuffer<50> timestampBuffer;
  JsonObject& timeStampObject = timestampBuffer.createObject();
  timeStampObject[".sv"] = "timestamp";
  
  StaticJsonBuffer<200> dataBuffer;
  JsonObject& dataObject = dataBuffer.createObject();
  dataObject["temperature"] = t;
  dataObject["humidity"] = h;
  dataObject["timestamp"] = timeStampObject;
     
  Firebase.set(instancePath+"/lastUpdate", timeStampObject);
  Firebase.push(instancePath, dataObject);

  //delay(5000);  // short interval for debug
  delay(sendingInterval);
}
