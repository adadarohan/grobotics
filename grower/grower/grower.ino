//Grobotics Arduino code
//#include <SoftwareSerial.h>

#include "DHT.h"        
#define DHTTYPE DHT11   

#define dht_dpin 2
#define dht_dpin2 13

DHT dht(dht_dpin, DHTTYPE); 
DHT dht2(dht_dpin2, DHTTYPE); 

//DHT2 is for the lower chamber

//Variabes
int plantdata[] = {50, 29.5 , 255 , 0 , 255, 90};  // Top Humidity, Temperature, R, G, B, Bottom Humidity
//Pins

/*
int spray = 8;
*/

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

  /*
  pinMode(spray, OUTPUT);

  */
  //Safety delay
  delay(50);
}
 
void loop() {
  setLight(plantdata[2],plantdata[3],plantdata[4]);
  setTemp(plantdata[1]);
  cycle(plantdata[5]);
  delay(2000);
}

void setLight( float r, float g , float b){
  analogWrite(red, (r/255) * 1023 );
  analogWrite(green, (g/255) * 1023);
  analogWrite(blue, (b/255) * 1023);
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
  //Serial.println(ct);

  //Heat and fan are triggered by low
  
  if ( rt < ct ) {
      digitalWrite(fan, LOW); //Fan on
      digitalWrite(heat, HIGH); //Heat off
      Serial.println("Fan on, Heat off");
  }
  else {
      digitalWrite(fan, HIGH); //Fan off
      digitalWrite(heat, LOW); //Heat on
      Serial.println("Fan off, Heat on");
   }
  
}


void cycle (float rh) {
    float ch = dht2.readHumidity();
    if ((int)ch < (int)rh){
      Serial.println("Water on");
      digitalWrite(water, LOW);
      delay(10000);
      digitalWrite(water, HIGH);
    } else {
      Serial.println("Water off");
      digitalWrite(water, HIGH);
    }
}
