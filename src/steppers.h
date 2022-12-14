#include <Stepper.h>

const int stepsPerRevolution = 200;

// in1, in2, in3, in4
Stepper VerticalStepper = Stepper(stepsPerRevolution, 6, 7, 8, 9);
Stepper HorizontalStepper = Stepper(stepsPerRevolution, 10, 11, 12, 13);

void stepper_innit()
{
    VerticalStepper.setSpeed(60);
    HorizontalStepper.setSpeed(60);
}

void VstepperNol()
{
  VerticalStepper.step(100);
  VerticalStepper.step(0);
}

void VstepperUp()
{
  VerticalStepper.step(200);
  VerticalStepper.step(0);
}

void VstepperDown()
{
   VerticalStepper.step(-200);
   VerticalStepper.step(0);
}