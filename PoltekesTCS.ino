#include "Lib/Config/config.h"
#include "Servo.h"

#define Out 10
#define Red digitalWrite(TCS1_S2,LOW);\
  digitalWrite(TCS1_S3,LOW);

#define Green digitalWrite(TCS1_S2,HIGH);\
  digitalWrite(TCS1_S3,HIGH);


#define Blue digitalWrite(TCS1_S2,LOW);\
  digitalWrite(TCS1_S3,HIGH);

Servo centerServo, leftServo, rightServo;


void setup() {
  // put your setup code here, to run once:

  pinMode(TCS1_S2, OUTPUT);
  pinMode(TCS1_S3, OUTPUT);
  pinMode(Out, INPUT_PULLUP);
  Serial.begin(9600);

  centerServo.attach(CenterServoPin);
  leftServo.attach(LeftServoPin);
  rightServo.attach(RightServoPin);

  centerServo.write(90);
  leftServo.write(90);
  rightServo.write(90);
}


unsigned long readSensor()
{
  unsigned long freqRed, freqGreen, freqBlue;
  Red;
  freqRed = pulseIn(Out, LOW);
  #ifdef DEBUG
  Serial.print("R: " + String(freqRed));
  #endif
  delay(100);
  Green;
  freqGreen = pulseIn(Out, LOW);
  #ifdef DEBUG
  Serial.print(", Green: " + String(freqGreen));
  #endif
  delay(100);
  Blue;
  freqBlue = pulseIn(Out, LOW);
  #ifdef DEBUG
  Serial.println(", Blue: " + String(freqBlue));
  #endif
  delay(100);

  return (freqRed << 16 | freqGreen << 8 | freqBlue);

}

bool inScope(unsigned long input, unsigned long std, float tolerance)
{
  unsigned long temp;
  unsigned long RGBVal;
  float lo, hi;

  for (uint8_t i = 0; i < 3; i++)
  {
    temp = (input >> (i * 8)) & 0xFF;
    RGBVal = (std >> (i * 8)) & 0xFF;

    lo = (float)RGBVal - ((float)RGBVal * tolerance);
    hi = ((float)RGBVal * tolerance) + (float)RGBVal;

    #ifdef DEBUG
    Serial.println("Datum: "+String(i)+" RGBVAL: "+String(RGBVal)+" Temp: "+String(temp)+ " lo: "+String((uint8_t)lo) + " hi: "+String((uint8_t)hi));
    #endif
    if (temp < (uint8_t)lo || temp > (uint8_t)hi)
      return false;

  }
  return true;

}

void loop() {
  // put your main code here, to run repeatedly:
   unsigned long rgb = readSensor();

  Serial.println("rgb: "+String(rgb,HEX));
  
  // l: 7 H: 13 val 10
  //  Serial.println("\nVal: "+String(inScope(0x070100, 0x0A0200, 0.3)));
  //  delay(1500);


}
