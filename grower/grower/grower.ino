//Arduino code
#include <SoftwareSerial.h>
#include "DHT.h"        
#define DHTTYPE DHT11   

#define dht_dpin A0


DHT dht(dht_dpin, DHTTYPE); 

//SoftwareSerial s(5,6);

//Variabes
float plantdata[] = {50, 10.0 , 0 , 200 , 150}; 
//Pins
int heat = 7;
int red = 9;
int green = 10;
int blue = 11;
int fan = 12;
//Swap with heat; 7 for testing pourposes only
int water = 6;
int spray = 8;

void setup() {
  //s.begin(9600);
  Serial.begin(9600);
  dht.begin();

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(water, OUTPUT);
  pinMode(spray, OUTPUT);
  pinMode(heat, OUTPUT);


  //Safety delay
  delay(50);
}
 
void loop() {
  setLight(plantdata[2],plantdata[3], plantdata[4]);
  setTemp(plantdata[1]);
  setHum(plantdata[0]);
  cycle();
  delay(300000);
}

void setLight( int r, int g , int b){
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
  
}

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

void setTemp (float rt){
  // Get current temperature (ct)
  float ct = dht.readTemperature();
  Serial.println(ct);

 if ( rt < ct ) {
    digitalWrite(fan, HIGH);
    digitalWrite(heat, LOW);
  }
  else {
    digitalWrite(fan, LOW);
    digitalWrite(heat, HIGH);
  }
}

void cycle () {
    digitalWrite(water, HIGH);
    delay(10000);
    digitalWrite(water, LOW);
}
