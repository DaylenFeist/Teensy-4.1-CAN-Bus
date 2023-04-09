#include <FlexCAN_T4.h>
// #include <kinetis_flexcan.h>
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;

CAN_message_t msg;
const int ledPin = 13;
const int baudRate = 50000;
const int delayTime = 100;

int8_t i,j;

void setup() {
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);

  Serial.begin(9600);
  can1.begin();
  can1.setBaudRate(baudRate);
  }

void loop() {
    delay(50);
    CAN_message_t msg;
    can1.read(msg);
    i = msg.buf[0];
    j = msg.buf[1];
    Serial.print(i);
    Serial.print(' ');
    Serial.println(j);
    // Serial.println(ConstructValue(i,j));
  }

int16_t ConstructValue(int8_t& i, int8_t& j)
{
  return (i << 8) | j;
}
