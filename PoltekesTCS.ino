#include "Lib/Config/config.h"
#include "Servo.h"
#include <MD_TCS230.h>
#include <FreqCount.h>

#define DEBUG_RGB
#define Out 10
#define tolerance_ 0.5
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

  delay(1000);
  centerServo.attach(CenterServoPin);
  leftServo.attach(LeftServoPin);
  rightServo.attach(RightServoPin);

  centerServo.write(85); // 40 85 125
  leftServo.write(70); // 70 35
  rightServo.write(95); //95 130
}


unsigned long readSensor()
{
  unsigned long freqRed, freqGreen, freqBlue;
  Red;
  freqRed = pulseIn(Out, digitalRead(Out) == HIGH ? LOW : HIGH);
#ifdef DEBUG_RGB
  Serial.print("R: " + String(freqRed, HEX));
#endif
  delay(100);
  Green;
  freqGreen = pulseIn(Out, digitalRead(Out) == HIGH ? LOW : HIGH);
#ifdef DEBUG_RGB
  Serial.print(", Green: " + String(freqGreen, HEX));
#endif
  delay(100);
  Blue;
  freqBlue = pulseIn(Out, digitalRead(Out) == HIGH ? LOW : HIGH);
#ifdef DEBUG_RGB
  Serial.println(", Blue: " + String(freqBlue, HEX));
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

#ifdef DEBUG_SHOW_TOLERANCE
    Serial.println("Datum: " + String(i) + " RGBVAL: " + String(RGBVal) + " Temp: " + String(temp) + " lo: " + String((uint8_t)lo) + " hi: " + String((uint8_t)hi));
#endif
    if (temp < (uint8_t)lo || temp > (uint8_t)hi)
      return false;

  }
  return true;

}



void loop() {
  // put your main code here, to run repeatedly:
  unsigned long rgb;
  rgb = readSensor();
  Serial.println("\nrgb: " + String(rgb, HEX));

  if (inScope(rgb, Blue_Color, tolerance_) || inScope(rgb, Red_Color, tolerance_) /*|| inScope(rgb, Purple_Color,tolerance_) || inScope(rgb, Brown_Color,tolerance_)*/) {
    centerServo.write(40);
    delay(500);
    centerServo.write(85);
    delay(500);
    leftServo.write(35);
    delay(500);
    leftServo.write(70);
    delay(500);
    Serial.println("Left");
  }
  else if (/*inScope(rgb, Pink_Color,tolerance_) || inScope(rgb, White_Color,tolerance_)
  ||*/ inScope(rgb, Yellow_Color, tolerance_) || inScope(rgb, Green_Color,tolerance_)) {
    centerServo.write(125);
    delay(500);
    centerServo.write(85);
    delay(500);
    rightServo.write(130);
    delay(500);
    rightServo.write(95);
    Serial.println("Right");
  }

  static unsigned char i = 0;
  // l: 7 H: 13 val 10
  //  Serial.println("\nVal: "+String(inScope(0x070100, 0x0A0200, 0.3)));
  //  delay(1500);
  //  if(i==0){
  //    rightServo.write(95);
  //    Serial.println("Center");
  //  }
  //   else{
  //   rightServo.write(130);
  //   }
  //   delay(1500);
  i++;
  i = i % 2;

}
