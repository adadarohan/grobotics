
#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  //Data
  int data[] = {random( 20 , 40 ) , random( 20 , 90 ) , random( 0 , 255 ) , random( 0 , 255 ) , random( 0 , 255 ) , random( 0 , 2 ) };
  
  // send data to nodemcu
  for(int n = 0; n < 5 ; n++){
      espSerial.println(data[n]);
  }
  
  //Print the last one instead of println
  espSerial.print(data[5]);

  Serial.println("written");
  delay(30000);
  
}
