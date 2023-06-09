#include <half.h>

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
  start_time = millis();
  if(millis() > start_time + 50){
    start_time = millis();
    can1.read(rxmsg);
    
    myData = kxAccel.getAccelData(); 
    Serial.println(myData.zData);
    
    write_float_data(float myData.zData, 0);
    
    message.len = 2;
    message.id = 0x2;
    can1.write(message);
    
  }

void write_float_data(float val, buf_num){
  buf_num *= 2;
  
  FLOAT16 val_16 = FLOAT16(val);
  uint8_t* val_8 = (uint8_t*)&val_16;
  
  message.buf[buf_num] = val_8[0];
  buf_num++;
  message.buf[buf_num] = val_8[1];
  }
}
