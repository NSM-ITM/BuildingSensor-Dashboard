// INSTANCE IDENTITY
String instancePrefix = "Station_";
String instanceNo = "02"; 

// NTP - unused - switched to Firebase timestamp
//#include <NTPClient.h>
//#include <WiFiUdp.h>
//#define NTP_OFFSET   60 * 60      // In seconds
//#define NTP_INTERVAL 60 * 1000    // In miliseconds
//#define NTP_ADDRESS  "th.pool.ntp.org"

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
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

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
  //Firebase.set("register", 1);
  //Firebase.set("humidity", 0);
  //Firebase.set("temperature", 0);
  //Firebase.set("timestamp", 0);

  //timeClient.begin();

  instancePath = instancePrefix + instanceNo;
}


void loop() {
  //timeClient.update();
  Serial.println("Reading...");
  //unsigned long epochTime =  timeClient.getEpochTime();
  
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

  delay(sendingInterval);
}
