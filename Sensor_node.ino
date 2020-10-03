#include <MQ135.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#define RZERO 206.85


#define BLYNK_PRINT Serial// Comment this out to disable prints and save space
int mq135=36;
MQ135 gasSensor = MQ135(mq135);
char auth[] = " ";
float data = 0;
int RL=47000;
 int Ro;
int m=-0.243;
int b=0.323;
/* WiFi credentials */
WiFiClient client;
WiFiServer server(80);
 
char ssid[] = "Laptop_Malavika";
char pass[] = "Malavika";
WidgetBridge  bridge1(V1);


BLYNK_CONNECTED()
{
  bridge1.setAuthToken("");
}

void sendsensor()
{
  // smoke sensor is connected with the analog pin A0
  data= gasSensor.getPPM();
  float VRL; //Voltage drop across the MQ sensor
  float Rs; //Sensor resistance at gas concentration 
  float ratio; //Define variable for ratio
   
  VRL = data*(5.0/1023.0); //Measure the voltage drop and convert to 0-5V
  Rs = ((5.0*RL)/VRL)-RL; //Use formula to get Rs value
  ratio = Rs/Ro;  // find ratio Rs/Ro
 
  float ppm = pow(10, ((log10(ratio)-b)/m)); //use formula to calculate ppm

  Blynk.virtualWrite(V1,ppm); // Displaying data in Gauge
}

BLYNK_WRITE(V10)
{
  Blynk.virtualWrite(V2 ,param.asInt()); // Update power LED
}
 
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
 
void loop()
{
  Blynk.run();
  WiFiClient client = server.available();
  if( digitalRead(10)==HIGH)
    getSendData();
}
 

void getSendData()

{
  sendsensor();
  if (data >=50 ) // Indicating Alert to master node
  {
    bridge1.digitalWrite(9,HIGH); // Change pin for each sensor
    Blynk.notify("leakage Detected!!!");
  }
  else
  {
    bridge1.digitalWrite(9,LOW);
  }
   
   
}
