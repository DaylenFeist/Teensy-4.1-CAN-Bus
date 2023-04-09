#include <half.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

CAN_message_t msg;
const int ledPin = 13;
const int baudRate = 50000;
const int delayTime = 100;
int start_time = 0;


FLOAT16 accel_x;
FLOAT16 accel_y;
FLOAT16 accel_z;

void setup() {
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);

  Serial.begin(9600);
  can1.begin();
  can1.setBaudRate(baudRate);
  }

void loop() {
  if(millis() > start_time + 50){
    start_time = millis();
    CAN_message_t msg;
    can1.read(msg);

    accel_x = read_float16_from_fram(msg,0);
    accel_y = read_float16_from_fram(msg,1);
    accel_z = read_float16_from_fram(msg,2);
    Serial.println("x : " + (String)accel_x+ " | y : " + (String)accel_y + " | z : " + (String)accel_z );
    
  }
}
FLOAT16 read_float16_from_fram(CAN_message_t msg, int buf_ind)
  {
  buf_ind *= 2;
  
  uint8_t float16_arr[2];

  float16_arr[0] = msg.buf[buf_ind];
  buf_ind++;
  float16_arr[1] = msg.buf[buf_ind];
  
  
  FLOAT16 f16_val = *(FLOAT16*)float16_arr;

  return f16_val;
  }
