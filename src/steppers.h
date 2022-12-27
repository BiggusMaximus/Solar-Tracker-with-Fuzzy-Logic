#include <Stepper.h>
#define stepsPerRevolution 360
int MAX_VER, MAX_HOR = 0;
int move = 0;
// in1, in2, in3, in4
Stepper VerticalStepper = Stepper(stepsPerRevolution, 11, 10, 9, 8);
Stepper HorizontalStepper = Stepper(stepsPerRevolution, 6, 5, 4, 3);
int pwmH = 12;
int pwmV = 7;
void stepper_innit()
{
  VerticalStepper.setSpeed(10);
  HorizontalStepper.setSpeed(10);
  //pinMode(pwmH, OUTPUT);
  //pinMode(pwmV, OUTPUT);
}

void Tracking(float THRESHOLD, int STEP_SIZE)
{

  if (diff_vertical > THRESHOLD)
  {
    // If LDR Right > LDR Left
    Serial.println("Ver CW");
    VerticalStepper.step(STEP_SIZE);
    MAX_VER = MAX_VER + 20;
  }
  else if (diff_vertical < -THRESHOLD)
  {
    // If LDR Right < LDR Left
    Serial.println("Ver CCW");
    VerticalStepper.step(-STEP_SIZE);
    MAX_VER = MAX_VER - 20;
  }
  else
  {
    Serial.println("Ver off");
    VerticalStepper.step(0);
  }
  
  Serial.println("MAX VER : " + String(MAX_VER));
  if (MAX_VER > 20){
    // if over 20, 40 > 20, step -20
    VerticalStepper.step(-MAX_VER);
    MAX_VER = 0;
  }else if (-20 > MAX_VER){
    // if over 20, -20 > -40, step +20
    VerticalStepper.step(-MAX_VER);
    MAX_VER = 0;
  }

  // For Horizontalss

  if (diff_horizontal > THRESHOLD)
  {
    Serial.println("Hor CW");
    // If LDR Right > LDR Left
    HorizontalStepper.step(STEP_SIZE);
    MAX_HOR = MAX_HOR + 20;
  }
  else if (diff_horizontal < -THRESHOLD)
  {
    Serial.println("Hor CCW");
    // If LDR Right < LDR Left
    HorizontalStepper.step(-STEP_SIZE);
    MAX_HOR = MAX_HOR - 20;
  }
  else
  {
    Serial.println("Hor Off");
    HorizontalStepper.step(0);
  }
  Serial.println("MAX_HOR : " + String(MAX_HOR));

  if (MAX_HOR > 20){
    // if over 20, 40 > 20, step -20
    HorizontalStepper.step(-MAX_HOR);
    MAX_HOR = 0;

  }else if (-20 > MAX_HOR){
    // if over 20, -20 > -40, step +20
    HorizontalStepper.step(-MAX_HOR);
    MAX_HOR = 0;
  }
}

void Tracking2(){
  if (top > bottom ){
    // if bottom is brighter than top
    digitalWrite(pwmH, HIGH);
    Serial.println("CCW");
    VerticalStepper.step(1);
    if((top < 50 + (top + bottom)/2) and (top > 50 - (top + bottom)/2)){
      digitalWrite(pwmH, LOW);
      Serial.println("CCW THRESH");
      VerticalStepper.step(0);
    }
  }else{
        digitalWrite(pwmH, HIGH);
        Serial.println("CW");
        VerticalStepper.step(-1);
    if((bottom < 50 + (top + bottom)/2) and (bottom > 50 - (top + bottom)/2)){
      Serial.println("CW THRESH");
      digitalWrite(pwmH, LOW);
      VerticalStepper.step(0);
    }
  }
}