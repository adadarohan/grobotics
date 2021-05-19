int red = 5;
int green = 4;
int blue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 1023);
  Serial.println("set");
  delay(5000);
}
