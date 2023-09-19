#include <VirtualWire.h>
#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(15,14);
#include <String.h>
const int receive_pin = 50;
int sensornumber;
float battery;
float temp;
float hum;
int soilmois;
int light;
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
    gprsSerial.begin(9600);                 
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
    temp = data.temperature;
    hum=data.humidity;
    soilmois=data.soil;
    light=data.ldr;
    sensornumber=data.node;
    battery=data.voltage;
    Serial.println(battery);
    Serial.println(temp);
    Serial.println(hum);
    Serial.println(soilmois);
    Serial.println(light);
  

  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"internet\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=VTMAQ71UMFN7AANN&field1=" + String(sensornumber) +"&field2="+String(hum)+"&field3="+String(temp)+"&field4="+String(light)+"&field5="+String(soilmois)+"&field6="+String(battery);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }
} 

void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}
    
   
 
    
 
    
  
   
