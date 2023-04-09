

#include <FlexCAN_T4.h>
#include <Wire.h>
#include "SparkFun_Qwiic_KX13X.h"
#include <half.h>
//CAN
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

//Accel
QwiicKX134 kxAccel;
outputData myData;

int start_time = 0;
const int ledPin = 13;
const int baudRate = 50000;
int count = 0;

CAN_message_t message;


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
  if(millis() > start_time + 50){
    start_time = millis();

    
    myData = kxAccel.getAccelData(); 
    Serial.println(myData.zData);
    
    write_float_data(myData.xData, 0);
    write_float_data(myData.yData, 1);
    write_float_data(myData.zData, 2);
    
    message.len = 6;
    message.id = 0x2;
    can1.write(message);
    
  }
}
void write_float_data(float val, int buf_ind){
  buf_ind *= 2;
  
  FLOAT16 val_16 = FLOAT16(val);
  uint8_t* val_8 = (uint8_t*)&val_16;
  
  message.buf[buf_ind] = val_8[0];
  buf_ind++;
  message.buf[buf_ind] = val_8[1];
}
