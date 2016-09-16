/*
 * 3 Pot RGB PWM
 * APurdon
 * 2016-09-14
 * 
 * Influenced by: 
 * http://www.silvinopresa.com/how-to/arduino/rgb-led-common-annode-controlled-by-potentiometers-and-arduino/
 * Arduino Starter Kit example 4 
 */


// all RGB in this project have 3 colours, so to save code repetition, use an array
int rgbPotPins[] = { A0, A1, A2 };
int rgbPwmPins[] = { 11, 9, 10 };

// variables for reading input and writing output. Not necessary but increases readability of code
int potValue;
int pwmValue;

void setup() {
  for (int i = 0; i < sizeof(rgbPotPins[i]) ; i++)
  {
    pinMode(rgbPotPins[i], INPUT);
  }
  for (int i = 0; i < sizeof(rgbPwnPins); i++)
  {
    pinMode(rgbPwnPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++)
  {
    // small delay to let ADC settle. This could possibly be reduced
    delay(5);
    potValue = analogRead(rgbPotPins[i]);
    pwmValue = map(potValue, 0, 1023, 0, 255);
    analogWrite(rgbPwmPins[i], pwmValue);
  }
}
