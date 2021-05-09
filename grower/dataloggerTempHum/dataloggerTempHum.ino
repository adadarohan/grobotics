/*
Code to communicate nodemcu with thingspeak. Combined with serial comm with ardiuno is serialN
Copyright Rohan Kapur 2020
*/

#include <ESP8266WiFi.h>;
#include <ThingSpeak.h>;

const char* ssid = "y2how2"; //Your Network SSID
const char* pass = "nonadubak"; //Your Network Password

WiFiClient client;
unsigned long myChannelNumber = 789133; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "F2DAVCTPLKR6BWWP"; //Your Write API Key

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
  ThingSpeak.begin(client);

}



void loop(){

  int temp = random(0, 100);
  int hum = random(0, 100);

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(30000);
  

}
