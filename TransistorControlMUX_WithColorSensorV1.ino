//Use 3 transistor multiplexer to control the clock pins of the
//3 color sensors

#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);



int CTRLA = 3;
int CTRLB = 4;
int CTRLC = 5;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  pinMode(CTRLA, OUTPUT);
  pinMode(CTRLB, OUTPUT);
  pinMode(CTRLC, OUTPUT);

  Serial.println("Triggering Color Sensor A....");
  turnOnColorSensor('A');
  delay(50);
  checkStatusOfColorSensor();

  Serial.println("Triggering Color Sensor B....");
  turnOnColorSensor('B');
  delay(50);
  checkStatusOfColorSensor();

  Serial.println("Triggering Color Sensor C....");
  turnOnColorSensor('C');
  delay(50);
  checkStatusOfColorSensor();
}

// the loop function runs over and over again forever
void loop() {

  //REMEMBER: the mirroring effect of HIGH/LOW on the base vs the collector
  turnOnColorSensor('A');
  delay(50);
  Serial.println("Expecting reading from Color Sensor A....");
  printColorSensorReadings();

  turnOnColorSensor('B');
  delay(50);
  Serial.println("Expecting reading from Color Sensor B....");
  printColorSensorReadings();

  turnOnColorSensor('C');
  delay(50);
  Serial.println("Expecting reading from Color Sensor C....");
  printColorSensorReadings();
}

void printColorSensorReadings()
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
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
}

void turnOnColorSensor(char c)
{
  if (c == 'A')
  {
    digitalWrite(CTRLA, LOW);
    digitalWrite(CTRLB, HIGH);
    digitalWrite(CTRLC, HIGH);
  }
  else if (c == 'B')
  {
    digitalWrite(CTRLA, HIGH);
    digitalWrite(CTRLB, LOW);
    digitalWrite(CTRLC, HIGH);
  }
  else if (c == 'C')
  {
    digitalWrite(CTRLA, HIGH);
    digitalWrite(CTRLB, HIGH);
    digitalWrite(CTRLC, LOW);
  }
  else
  {
    Serial.println("Invalid choice of transistor");
  }
}

void checkStatusOfColorSensor()
{
  //code to check if color sensor is detected
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1); // halt!
  }
}


