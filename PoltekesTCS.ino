#include "Lib/Config/config.h"

#define Out 10
#define Red digitalWrite(TCS1_S2,LOW);\
            digitalWrite(TCS1_S3,LOW);

#define Green digitalWrite(TCS1_S2,HIGH);\
            digitalWrite(TCS1_S3,HIGH);


#define Blue digitalWrite(TCS1_S2,LOW);\
            digitalWrite(TCS1_S3,HIGH);

unsigned long freq;
void setup() {
  // put your setup code here, to run once:

  pinMode(TCS1_S2, OUTPUT);
  pinMode(TCS1_S3, OUTPUT);
  pinMode(Out,INPUT_PULLUP);
  Serial.begin(9600);
}


void readSensor()
{
  Red;
  freq = pulseIn(Out,LOW);
  Serial.print("R: "+String(freq));
  delay(100);
  Green;
  freq = pulseIn(Out,LOW);
  Serial.print(", Green: "+String(freq));
  delay(100);
  Blue;
  freq = pulseIn(Out,LOW);
  Serial.println(", Blue: "+String(freq));
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:
readSensor();

}
