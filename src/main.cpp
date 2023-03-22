#include <Arduino.h>
#include "ldr.h"
#include "steppers.h"
#include "bluetooth.h"

String content = "";
unsigned long lastTime = 0;

void show_info(String message)
{
  /*
    Showing Serial.print for debugging
  */
  if (message == "show_ldr")
  {
    content = 
        "Top : " + String(top) +
        " | Bottom : " + String(bottom) +
        " | Left : " + String(left) +
        " | Right : " + String(right);
  }
  else if(message == "show_limit_switch"){
    content = 
      "Limit Vertical CCW : " + String(digitalRead(switchV_CCW)) + 
      " | Limit Vertical CW : " + String(digitalRead(switchV_CW)) + 
      " | Limit Horizontal CCW : " + String(digitalRead(switchH_CCW)) + 
      " | Limit Horizontal CW : " + String(digitalRead(switchH_CW));
  }
  else if(message == "show_all"){
    content = 
        "Top : " + String(top) +
        " | Bottom : " + String(bottom) +
        " | Left : " + String(left) +
        " | Right : " + String(right) +
        " | Limit Vertical CCW : " + String(digitalRead(switchV_CCW)) + 
        " | Limit Vertical CW : " + String(digitalRead(switchV_CW)) + 
        " | Limit Horizontal CCW : " + String(digitalRead(switchH_CCW)) + 
        " | Limit Horizontal CW : " + String(digitalRead(switchH_CW));
  }
  Serial.println(content);
}

void setup()
{
  Serial.begin(115200);
  ldr_innit();
  stepper_innit();
  start_bluetooth();
  // calibration_ldr();
}

void loop()
{
  show_ldr(false);
  //show_info("show_limit_switch");
  Tracking2_vertical();
  Tracking2_horizontal();

  if ((millis() - lastTime) > 500){
      show_info("show_all");
      bluetooth.println(content);
      lastTime = millis();
  }
  
}
