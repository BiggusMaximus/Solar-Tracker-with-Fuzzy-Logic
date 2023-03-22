#include <Stepper.h>
#define stepsPerRevolution 360

int MAX_VER, MAX_HOR = 0;
int move = 0;
// in1, in2, in3, in4
Stepper VerticalStepper = Stepper(stepsPerRevolution, 11, 10, 9, 8);
Stepper HorizontalStepper = Stepper(stepsPerRevolution, 6, 5, 4, 2);

int pwmH = 12;
int pwmV = 7;
int switchV_CCW = 2;
int switchV_CW = A1;
int switchH_CCW = A3;
int switchH_CW = A2;




//int switchH = 13;

void stepper_innit()
{
  VerticalStepper.setSpeed(10);
  HorizontalStepper.setSpeed(5);
  //pinMode(pwmH, OUTPUT);
  //pinMode(pwmV, OUTPUT);
  pinMode(switchV_CW, INPUT_PULLUP);
  pinMode(switchV_CCW, INPUT_PULLUP);
  pinMode(switchH_CW, INPUT_PULLUP);
  pinMode(switchH_CCW, INPUT_PULLUP);
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

void Tracking2_vertical(){

  if (top > bottom ){
    // if bottom is brighter than top
    //digitalWrite(pwmH, HIGH);
    if(digitalRead(switchV_CCW) == 0){
      Serial.println("Vertical CCW PB Pressed");
      VerticalStepper.step(-0);
      //delay(1800000);

    }
    else{
      Serial.println("Vertical CCW");
      VerticalStepper.step(1);
      if((top < 10 + (top + bottom)/2) and (top > 10 - (top + bottom)/2)){
        //digitalWrite(pwmH, LOW);
        Serial.println("Vertical CCW THRESH");
        VerticalStepper.step(0);
        //delay(180000);  
      }

    }

  }

  else{
        //digitalWrite(pwmH, HIGH);
    if(digitalRead(switchV_CW) == 0){
      Serial.println("Vertical CW PB Pressed");
      VerticalStepper.step(0);
      //delay(1800000);
    }else{
      Serial.println("Vertical CW");
      VerticalStepper.step(-1);
      if((bottom < 10 + (top + bottom)/2) and (bottom > 10 - (top + bottom)/2)){
        Serial.println("Vertical CW THRESH");
        //digitalWrite(pwmH, LOW);
        VerticalStepper.step(0);
        //delay(1800000);
      }
    }
  }
}

void Tracking2_horizontal(){
  
  if (left > right ){
    // if bottom is brighter than top
    //digitalWrite(pwmH, HIGH);
    if(digitalRead(switchH_CCW) == 0){
      Serial.println("                    Horizontal CCW PB Pressed");
      HorizontalStepper.step(-90);
      //delay(1800000);

    }
    else{
      Serial.println("                    Horizontal CCW");
      HorizontalStepper.step(-1);
      if((left < 50 + (left + right)/2) and (left > 50 - (left + right)/2)){
        //digitalWrite(pwmH, LOW);
        Serial.println("                    Horizontal CCW THRESH");
        HorizontalStepper.step(0);
        //delay(1800000);  
      }

    }

  }

  else{
        //digitalWrite(pwmH, HIGH);
    if(digitalRead(switchH_CW) == 0){
      Serial.println("                    Horizontal CW PB Pressed");
      HorizontalStepper.step(90);
      //delay(1800000);
    }else{
      Serial.println("Horizontal CW");
      HorizontalStepper.step(1);
      if((right < 50 + (left + right)/2) and (right > 50 - (left + right)/2)){
        Serial.println("                    Horizontal CW THRESH");
        //digitalWrite(pwmH, LOW);
        HorizontalStepper.step(0);
        //delay(1800000);
      }
    }
  }
}