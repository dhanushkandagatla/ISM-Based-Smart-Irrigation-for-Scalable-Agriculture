#include "DHT.h"
#include <VirtualWire.h>
#define DHTTYPE DHT11
#define DHTPIN 2
int sensor = A0;
const int ldrPin = A2;
const float v = A3;
const int transmit_pin = 12;
float s=0;
DHT dht(DHTPIN, DHTTYPE);
struct package
{
  int node;
  float voltage;
  float temperature ;
  float humidity ;
  int soil;
  int ldr;
};
typedef struct package Package;
Package data;
void setup()
{
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_ptt_inverted(true);
    vw_setup(500);     
}
void loop()
{

  //readSensor();
  data.node = 1;
  data.temperature = 30;//dht.readHumidity();
  //delay(1000);
  data.humidity = 77;dht.readTemperature();
  //delay(1000);
  int s= analogRead(sensor);
  data.soil = s/10;
  data.ldr= analogRead(ldrPin);
  s = analogRead(v);
  data.voltage = s*(5.00 / 1023.00);
  Serial.println(data.node);
  Serial.println(data.temperature);
  Serial.println(data.humidity);
  Serial.println(data.soil);
  Serial.println(data.ldr);
  Serial.println(data.voltage);
  vw_send((uint8_t *)&data, sizeof(data));
  vw_wait_tx();
  delay(2000);
}
//void readSensor()
//{
 //delay(1000);
 //int h = dht.readHumidity();
 //int t = dht.readTemperature();
 //data.temperature = h;
 //data.humidity = t;
 //int s= analogRead(sensor);
 //data.soil = s/10;
 //data.ldr= analogRead(ldrPin);
//}
