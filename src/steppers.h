#include <Stepper.h>
#define STEP_SIZE 90
#define stepsPerRevolution 360

// in1, in2, in3, in4
Stepper VerticalStepper = Stepper(stepsPerRevolution, 6, 7, 8, 9);
Stepper HorizontalStepper = Stepper(stepsPerRevolution, 10, 11, 12, 13);

void stepper_innit()
{
    VerticalStepper.setSpeed(10);
    HorizontalStepper.setSpeed(10);
}

void Tracking(){
  // For Vertical
  if (diff_vertical > THRESHOLD){
    // If LDR Right > LDR Left
    VerticalStepper.step(STEP_SIZE);
  }
  else if (diff_vertical < -THRESHOLD){
    // If LDR Right < LDR Left
    VerticalStepper.step(-STEP_SIZE);
  }else{
    VerticalStepper.step(0);
    VerticalStepper.setSpeed(0);
  }

  // For Horizontalss

  if (diff_horizontal > THRESHOLD){
    // If LDR Right > LDR Left
    HorizontalStepper.step(STEP_SIZE);
  }
  else if (diff_horizontal < -THRESHOLD){
    // If LDR Right < LDR Left
    HorizontalStepper.step(-STEP_SIZE);
  }else{
    HorizontalStepper.step(0);
    HorizontalStepper.setSpeed(0);
  }
}