# Air-Quality-Monitor
An Air Quality Monitor with MQ135 and NodeMCU

Data is uploaded to ThingSpeak and also shown on a connected 16x2 LCD.

#### Connections:

###### MQ135:

AOUT (or A0)===> A0 of NodeMCU

VCC ==> Vin

GND ==> GND

###### LCD:

VSS ==> GND

VCC ==> +5V

VEE ==> GND

RS ==> D0

R/W ==> GND

E ==> D1

D0-D3 ==> No Connections

D4 ==> D2 

D5 ==> D3

D6 ==> D4

D7 ==> D5

LED+ ==> +5V

LED- ==> GND

###### Libraries Used:

https://github.com/esp8266/Arduino#installing-with-boards-manager
and LCD Library.
