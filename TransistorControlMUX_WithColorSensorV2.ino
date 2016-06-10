//Use 3 transistor multiplexer to control the clock pins of the
//3 color sensors

#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcsA, tcsB, tcsC;


int CTRLA = 3;
int CTRLB = 4;
//int CTRLC = 5;

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(CTRLA, OUTPUT);
  pinMode(CTRLB, OUTPUT);
//  pinMode(CTRLC, OUTPUT);

  digitalWrite(CTRLA, LOW);
  digitalWrite(CTRLB, LOW);
//  digitalWrite(CTRLC, HIGH);
  delay(100);

  Serial.begin(9600);

  tcsA = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  tcsB = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  tcsC = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  Serial.println("Starting...");
  delay(1000);

  delay(50);

  Serial.println("Triggering Color Sensor A....");
  turnOnColorSensor(tcsA);
  delay(50);
  checkStatusOfColorSensor(tcsA);

//  delay(1000);

  Serial.println("Triggering Color Sensor B....");
  turnOnColorSensor(tcsB);
  delay(50);
  checkStatusOfColorSensor(tcsB);

//  delay(1000);

  Serial.println("Triggering Color Sensor C....");
  turnOnColorSensor(tcsC);
  delay(50);
  checkStatusOfColorSensor(tcsC);

//  delay(1000);

}

// the loop function runs over and over again forever
void loop() {

  //REMEMBER: the mirroring effect of HIGH/LOW on the base vs the collector
  turnOnColorSensor(tcsA);
  delay(50);
  Serial.print("A: ");
  printColorSensorReadings(tcsA);

  turnOnColorSensor(tcsB);
  delay(50);
  Serial.print("B: ");
  printColorSensorReadings(tcsB);

  turnOnColorSensor(tcsC);
  delay(50);
  Serial.print("C: ");
  printColorSensorReadings(tcsC);
}

void printColorSensorReadings(Adafruit_TCS34725 &tcs)
{
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
//  Serial.print("\t");
//  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
}

void turnOnColorSensor(Adafruit_TCS34725 &tcs)
{
  if (&tcs == &tcsA)
  {
//    Serial.println("turning on A");
    digitalWrite(CTRLA, LOW);
    digitalWrite(CTRLB, LOW);
//    digitalWrite(CTRLC, HIGH);
  }
  else if (&tcs == &tcsB)
  {
//    Serial.println("turning on B");
    digitalWrite(CTRLA, HIGH);
    digitalWrite(CTRLB, LOW);
//    digitalWrite(CTRLC, HIGH);
  }
  else if (&tcs == &tcsC)
  {
//    Serial.println("turning on C");
    digitalWrite(CTRLA, LOW);
    digitalWrite(CTRLB, HIGH);
//    digitalWrite(CTRLC, LOW);
  }
  else
  {
    Serial.println("Invalid choice of transistor");
  }
}

void checkStatusOfColorSensor(Adafruit_TCS34725 &tcs)
{
  //code to check if color sensor is detected
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1); // halt!
  }
//  Serial.println("boo");
}

