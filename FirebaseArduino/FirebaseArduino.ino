#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "XXXXXXXXXXXXX"
#define FIREBASE_AUTH "XXXXXXXXXXXXX"
#define WIFI_SSID "XXXXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXXXX"

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
  Firebase.set("register", 1);
  Firebase.set("randData", 0);
}


void loop() {
  
  //Firebase.setInt("pushbutton", button);
  //Firebase.setFloat("sunlight", light);
  float randData = random(0,100);
  Firebase.setFloat("randData", randData);
  Serial.println("curent data: " + (String) randData);
  
  delay(5000);
}
