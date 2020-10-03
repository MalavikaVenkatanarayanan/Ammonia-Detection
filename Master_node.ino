#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial// Comment this out to disable prints and save space
char auth[] = " ";

/* WiFi credentials */
WiFiClient client;
WiFiServer server(80);
char ssid[] = "Laptop_Malavika";
char pass[] = "Malavika";

WidgetBridge  master_bridge1(V1);
WidgetBridge  master_bridge2(V2);
WidgetBridge  master_bridge3(V3);
WidgetBridge  master_bridge4(V4);

BLYNK_CONNECTED()
{
  master_bridge1.setAuthToken("");
  master_bridge2.setAuthToken("");
  master_bridge3.setAuthToken("");
  master_bridge4.setAuthToken("");
}

void checkSensor(int sensor, int pin)
{
  // Enable push notifications in Blynk app 
  if(digitalRead(pin)==HIGH)
    Blynk.notify("Alert!!! Smoke detected in Sensor_",sensor);
}

BLYNK_WRITE(V5)
{
  bridge1.virtualWrite(V10,param.asInt());
  bridge1.digitalWrite(10,param.asInt());
}

BLYNK_WRITE(V6)
{
  bridge2.virtualWrite(V10,param.asInt());
  bridge2.digitalWrite(10,param.asInt());
}

BLYNK_WRITE(V7)
{
  bridge3.virtualWrite(V10,param.asInt());
  bridge3.digitalWrite(10,param.asInt());
}

BLYNK_WRITE(V8)
{
  bridge4.virtualWrite(V10,param.asInt());
  bridge4.digitalWrite(10,param.asInt());
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  WiFiClient client = server.available();
  checkSensor(1,9);  // Mention pin numbers used to write 
  checkSensor(2,10); // in bridge of each sensor
  checkSensor(3,11);
  checkSensor(4,12);
 }
