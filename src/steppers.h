#include <Stepper.h>

const int stepsPerRevolution = 200;

// in1, in2, in3, in4

Stepper VerticalStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper HorizontalStepper(stepsPerRevolution, 8, 9, 10, 11);

void stepper_innit()
{
    VerticalStepper.setSpeed(60);
    HorizontalStepper.setSpeed(60);
}
