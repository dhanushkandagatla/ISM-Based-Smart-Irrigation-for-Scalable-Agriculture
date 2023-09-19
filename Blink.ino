#include <VirtualWire.h>
const int receive_pin = 50;
//char temperatureChar[10];
//char humidityChar[10];
struct package
{
  int node=0;
  float voltage=0;
  float temperature = 0.0;
  float humidity = 0.0;
  int soil = 0;
  int ldr = 0;
};
typedef struct package Package;
Package data;
void setup()
{
    Serial.begin(9600);
    vw_set_rx_pin(receive_pin);
    vw_setup(500);   
    vw_rx_start();      
}
void loop()
{    
    uint8_t buf[sizeof(data)];
    uint8_t buflen = sizeof(data);
if (vw_have_message())  // Is there a packet for us? 
  {
   
    vw_get_message(buf, &buflen);
    memcpy(&data,&buf,buflen);
    Serial.println(data.temperature);
    Serial.println(data.humidity);
    Serial.println(data.soil);
    Serial.println(data.ldr);
    Serial.println(data.node);
    Serial.println(data.voltage);
    
  }
}
