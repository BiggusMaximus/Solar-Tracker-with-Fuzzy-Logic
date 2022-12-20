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
  Serial.begin(115200);
  ldr_innit();
  stepper_innit();
  calibration_ldr();
}

void loop()
{
  show_ldr();
  Tracking2();
  // VerticalStepper.step(360);
  // HorizontalStepper.step(60);
  // delay(2000);
  // HorizontalStepper.step(-60);
  // delay(2000);
}