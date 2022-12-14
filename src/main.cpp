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

  Serial.println("start to zero degree");
  delay(3000);
  VstepperNol();
  Serial.println("Finish to zero, start rotate 90");
  delay(2000);
  VerticalStepper.step(90);
  Serial.println("start rotate -90");
  delay(1000);
  VerticalStepper.step(-120);
  Serial.println("Finish to rotate -90");
}

void loop()
{
  read_value_ldr();
  // show_info("show_ldr");
}