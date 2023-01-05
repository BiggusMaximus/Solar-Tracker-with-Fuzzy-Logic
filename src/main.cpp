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
  else if(message == "show_limit_switch"){
    Serial.println(
      "Limit Vertical CCW : " + String(digitalRead(switchV_CCW)) + 
      " | CW : " + String(digitalRead(switchV_CW)));
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
  show_ldr(true);
  show_info("show_limit_switch");
  Tracking2();
  
}
