
#include <ESP8266WiFi.h>
#include "LiquidCrystal.h"

#define DHT_PIN_DATA  D1

String apiWritekey = "UJIRZDH74DH6DX8U"; // THINGSPEAK WRITEAPI KEY
const char* ssid = "Hotspot"; // SSID
const char* password = "pass1234";// PASSWORD
 
const char* server = "api.thingspeak.com";
int sensorData;

WiFiClient client;
LiquidCrystal lcd(16,5,4,0,2,14);
 
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);  // to intialize LCD
  lcd.setCursor(0,0);
  lcd.print("     AIR"); 
  lcd.setCursor(0,1);
  lcd.print("QUALITY MONITOR");  

  delay(3000); 
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password); //Connect to WIFI
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to...");
  lcd.setCursor(0,1);
  lcd.print(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to WIFI...");
  Serial.println(ssid);
  Serial.println();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      WIFI");
  lcd.setCursor(0,1);
  lcd.print("   CONNECTED");
  delay(4000);
}
 
void loop() {
  
  sensorData = analogRead(A0); //Read MQ135 DATA

  Serial.print("Air Quality = ");
  Serial.print(sensorData);
  Serial.println(" PPM");
  
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print ("Air Qual:");
  lcd.print (sensorData);
  lcd.print (" PPM");
  lcd.setCursor (0,1);

  if (sensorData<=500)
   {
   lcd.print("Fresh Air");
   Serial.println("Fresh Air ");
   
  }
  else if( sensorData>=500 && sensorData<=1000 )
  {
   lcd.print("Poor Air");
   Serial.println("Poor Air");
  
  }
  else if (sensorData>=1000 )
  {
  lcd.print("Very Poor");
  Serial.println("Very Poor");
  
  }
  
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(sensorData);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.println("Uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
}
