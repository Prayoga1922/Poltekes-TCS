#include "Lib/Config/config.h"

#define Out 10
#define Red digitalWrite(TCS1_S2,LOW);\
            digitalWrite(TCS1_S3,LOW);

#define Green digitalWrite(TCS1_S2,HIGH);\
            digitalWrite(TCS1_S3,HIGH);


#define Blue digitalWrite(TCS1_S2,LOW);\
            digitalWrite(TCS1_S3,HIGH);


void setup() {
  // put your setup code here, to run once:

  pinMode(TCS1_S2, OUTPUT);
  pinMode(TCS1_S3, OUTPUT);
  pinMode(Out,INPUT_PULLUP);
  Serial.begin(9600);
}


unsigned long readSensor()
{
  unsigned long freqRed, freqGreen, freqBlue;
  Red;
  freqRed = pulseIn(Out,LOW);
  Serial.print("R: "+String(freqRed));
  delay(100);
  Green;
  freqGreen = pulseIn(Out,LOW);
  Serial.print(", Green: "+String(freqGreen));
  delay(100);
  Blue;
  freqBlue = pulseIn(Out,LOW);
  Serial.println(", Blue: "+String(freqBlue));
  delay(100);

  return (freqRed << 16 | freqGreen << 8 | freqBlue);

}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned long rgb = readSensor();

  


}
