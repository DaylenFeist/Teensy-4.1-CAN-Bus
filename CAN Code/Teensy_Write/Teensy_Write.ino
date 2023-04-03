#include <FlexCAN_T4.h>
#include <Wire.h>
#include "SparkFun_Qwiic_KX13X.h"

//CAN
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

//Accel
QwiicKX134 kxAccel;
outputData myData;

CAN_message_t msg;
const int ledPin = 13;
const int baudRate = 50000;
int count = 0;

CAN_message_t message;
CAN_message_t rxmsg;

void setup() {
  
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledPin,HIGH);
  can1.begin();
  can1.setBaudRate(baudRate);

  Wire.begin();
  kxAccel.begin();
  kxAccel.initialize(DEFAULT_SETTINGS);

}
void loop() {
    delay(50);
    can1.read(rxmsg);
    
    myData = kxAccel.getAccelData(); 
    Serial.print("X: ");
    Serial.print(myData.xData, 4);
    Serial.print("g ");
    Serial.print(" Y: ");
    Serial.print(myData.yData, 4);
    Serial.print("g ");
    Serial.print(" Z: ");
    Serial.print(myData.zData, 4);
    Serial.println("g ");
    Serial.println(rxmsg.buf[0]);
    if(rxmsg.buf[0] == 49)
    {
     rxmsg.buf[0] = 0;
     Serial.println("message Sent");
     message.buf[0] = 'a';
     message.buf[1] = count+1;
     message.len = 2;
     message.id = 0x2;
     can1.write(message);
     count++;
      
  }
  rxmsg.buf[0] += 1;
  
}
