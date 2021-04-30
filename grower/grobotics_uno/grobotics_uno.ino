#include <DHT.h>

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11  (AM2302)
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

int rpin = 9;
int gpin = 10;
int bpin = 11;
int datasend[] = { 90, 10}; // Humidity, Temperature
int plantdata[] = {0, 5,250, 100 , 250, 5}; //Humidity, Temperature, R, G, B, End of packet
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(rpin, OUTPUT);
pinMode(gpin,OUTPUT);
pinMode(bpin, OUTPUT);
dht.begin();

}

void loop() {
 
  if(Serial.available() > 0){ 
    for (int i = 0 ; i < 6 ; i++ ) {
      plantdata[i] = Serial.read(); 

     }
     if(plantdata[5] = 44){
      //Creating an array for the data to send
      datasend[0] = round(dht.readHumidity());
      datasend[1] = dht.readTemperature();
      
      
      for (int i = 0 ; i < 2 ; i++ ) {
        Serial.print(datasend[i]);
        Serial.print(" , ");

      }
     }
  };
 
  analogWrite(rpin,255 - plantdata[2]);
  analogWrite(gpin, 255 - plantdata[3]);
  analogWrite(bpin, 255 - plantdata[4]);
  delay(500);

  
   
}
