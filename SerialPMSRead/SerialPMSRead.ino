#include "PMS.h"

PMS pms(Serial);
PMS::DATA data;

void setup()
{
  Serial.begin(9600);
  pms.passiveMode();    // Switch to passive mode
}
void loop()
{
  
  pms.wakeUp();
  
  Serial.println();
  Serial.println("wake up, wait 10 seconds for stable reading...");
  delay(10000);
  
  pms.requestRead();

  if (pms.readUntil(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);
    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);
    
  }
  else
  {
    Serial.println("No data");
  }
  
  Serial.println("sleep for 15 seconds");
  
  pms.sleep();
  delay(15000);
}
