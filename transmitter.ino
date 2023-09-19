#include "DHT.h"
#define DHTPIN 2
int sensor = A0;
const int ldrPin = A2;
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
 
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  float s = digitalRead(sensor);
  float a = analogRead(ldrPin);
  Serial.println(h);
   Serial.println(t);
}
  
