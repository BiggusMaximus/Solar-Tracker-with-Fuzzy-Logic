#include <Arduino.h>
#include "ldr.h"
#include "steppers.h"

void show_info(String message)
{
  /*
    Showing Serial.print for debugging 
  */
  if (message == "show_ldr")
  {
    Serial.println(
        "Top : " + String(top) +
        " | Bottom : " + String(bottom) +
        " | Left : " + String(left) +
        " | Right : " + String(right));
  }
}

void setup()
{
  Serial.begin(9600);
  ldr_innit();
  stepper_innit();
}

void loop()
{
  read_value_ldr();
  Tracking();
}