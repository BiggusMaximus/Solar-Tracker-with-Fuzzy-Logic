#include <Arduino.h>
#include "steppers.h"
#include "ldr.h"

void show_info(String message)
{
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
  show_info("show_ldr");
}