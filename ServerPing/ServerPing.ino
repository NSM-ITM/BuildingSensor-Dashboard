#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
     
const char* ssid     = "XXXXXXXXXXXXX";
const char* password = "XXXXXXXXXXXXX";     
const char* website = "http://www.google.com";

int wifiStatus;
WiFiClient client;
HTTPClient http;
 
void setup() {
    
    Serial.begin(115200);
    delay(200);
          
    // We start by connecting to a WiFi network
   
    Serial.println();
    Serial.println();
    Serial.print("Your are connecting to;");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("Your ESP is connected!");  
    Serial.println("Your IP address is: ");
    Serial.println(WiFi.localIP());  
   
}   
   
void loop() {
    wifiStatus = WiFi.status();
    Serial.println("");
    Serial.println("Working...");

    
    if(wifiStatus == WL_CONNECTED){
      Serial.println("");
      Serial.println("Making Request...");
     

      //http.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
      //http.addHeader("Content-Type", "text/plain");

      // Pastebin APIs
      http.begin("http://api.jsonbin.io/b");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("secret-key", "$2a$10$xV.W1GWEW.ZMME.cn.U5n.alCdEzLolsA5BLVKaluCsVr1Fv2cVYK");
      http.addHeader("collection-id", "5bac90a09353c37b7436098f");
      http.addHeader("private", "true");
      
      int httpCode = http.POST("{\"Sample\": \"Hello World\"}"); 
   
      if (httpCode > 0) { //Check the returning code
   
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload
   
      }
   
      http.end();   //Close connection
      
      
    } else{
      Serial.println("");
      Serial.println("WiFi not connected");

    }
    
    delay(60000);     // call once every minute

}

