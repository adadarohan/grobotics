/*
Code for Serial communication and thingspeak nodemcu. Only thingspeak code is groboticswifi
*/

//Libraries
#include <ESP8266WiFi.h>;
#include <ThingSpeak.h>;
#include <SoftwareSerial.h>

const char* ssid = "y2how2"; //Your Network SSID
const char* pass = "nonadubak"; //Your Network Password

//Thingspeak Details
WiFiClient client;
unsigned long myChannelNumber = 1148581; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "XJSKW6QO5AR3KCLX"; //Your Write API Key

// Software serial for comm with arduino 
SoftwareSerial s(D6,D5);
//Number of variables we're uploading
int plantvars = 6 ;
//Data recieved
int data[6];

void setup() {
  //Initialize serial comm
  
  s.begin(9600);
  Serial.begin(9600);

  // Connect to WiFi network
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  //Wait until connection is established
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);
  
}
 
void loop() {
  
  //Wait for bytes from arduino
  while ( s.available() < plantvars ) {}

  //Add bytes to data array
  for(int n = 0; n < plantvars; n++){
    data[n] = s.parseInt(); // Then: Get them.
  }

  //Write to thingspeak
  for(int n = 0; n < plantvars; n++){
    ThingSpeak.setField( (n + 1) , data[n]);
  }
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  //Handle Errors
  if(x == 200){
    Serial.println("Channel update successful.");
  } 
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

}
