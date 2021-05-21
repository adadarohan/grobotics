#include <ESP8266WiFi.h>;       
 
const char* ssid = "y2how2"; //Your Network SSID
const char* pass = "nonadubak"; //Your Network Password

WiFiClient client;

void setup(){
  
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi network
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}



void loop(){}
