//Grobotics NodeMCU code

#include <ESP8266WiFi.h>;
#include <ThingSpeak.h>;
#include "DHT.h"  

//DHT2 is for the lower chamber
      
#define DHTTYPE DHT11   
#define dht_dpin 2
#define dht_dpin2 13

DHT dht(dht_dpin, DHTTYPE); 
DHT dht2(dht_dpin2, DHTTYPE); 

// WiFi Setup

const char* ssid = "y2how2"; //Your Network SSID
const char* pass = "nonadubak"; //Your Network Password

WiFiClient client;
unsigned long myChannelNumber = 1148581; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "XJSKW6QO5AR3KCLX"; //Your Write API Key

//Variabes
float plantdata[] = {22, 29.5 , 255 , 0 , 255, 90};  //  Temperature,Top Humidity, R, G, B, Bottom Humidity
float state[] = {0,0,0,0,0,0} ; //Temperature, Top Humidity, R, G, B, Bottom State

//Pins

//int spray = 8;
int water = D6;
int fan = D0;
int red = D1;
int green = D2;
int blue = D3;
int heat = D5;

void setup() {
  Serial.begin(115200);
  dht.begin();
  dht2.begin();
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heat, OUTPUT);
  pinMode(water, OUTPUT);
  //pinMode(spray, OUTPUT);

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
  
  //Safety delay
  delay(50);
}
 
void loop() {
  setLight(plantdata[2],plantdata[3],plantdata[4]);
  setTemp(plantdata[0]);
  cycle(plantdata[5]);
  
  //Upload to thingspeak
  for(int y = 1; y < 7; y++){
      ThingSpeak.setField(y, state[y-1]);
  }

  int r = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(r == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(r));
  }
  delay(30000);
}

void setLight( float r, float g , float b){
  analogWrite(red, (r/255) * 1023 );
  analogWrite(green, (g/255) * 1023);
  analogWrite(blue, (b/255) * 1023);
  state[2] = r ;
  state[3] = g ;
  state[4] = b ;
}

/*
void setHum ( int rh) {
  int ch = dht.readHumidity();
  //if ( ch < rh) {

    //digitalWrite(spray , HIGH);
    //delay(5000);
  //}
  //else if ( ch > rh ) {
  digitalWrite(spray , LOW);
  //}
}
*/

void setTemp (float rt){
  // Get current temperature (ct)
  float ct = dht.readTemperature();
  float ch = dht.readHumidity();

  state[0] = ct;
  state[1] = ch;
  
  //Heat and fan are triggered by low
  
  if ( rt < ct ) {
      digitalWrite(fan, LOW); //Fan on
      digitalWrite(heat, HIGH); //Heat off
  }
  else {
      digitalWrite(fan, HIGH); //Fan off
      digitalWrite(heat, LOW); //Heat on
   }
  
}


void cycle (float rh) {
    float ch = dht2.readHumidity();
    if ((int)ch < (int)rh){
      digitalWrite(water, LOW);
      state[5] = 1;
    } else {
      digitalWrite(water, HIGH);
      state[5] = 0;
    }
}
