#include <SoftwareSerial.h>//include library code
SoftwareSerial sim808(11, 10);//RX, TX
char phone_no[] = "+639205140948"; // replace with your phone no.
String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;
int Top    = A0;     //LDR orange pcb#4 resistor
int Right  = A1;     //LDR brown pcb#2 resistor
int Left   = A2;     //LDR green pcb#1 resisotr
int Bottom = A3;     //LDR blue pcb#3 resistor
int dVm = A5;     //Digital Volt Meter 0-30V
#define xlstopper  2 //microswitch_A N.O   Borwn RIGHT X-Axis limit switch
#define xrstopper  3 //microswitch_B N.O   Blue LEFT X-Axis limit switch
#define in1  4       //L298N IN1  
#define in2  5       //L298N IN2
#define in3  6       //L298N IN3
#define in4  7       //L298N IN4
#define ylstopper  8 //microswitch_C N.O   Green RIGHT Y-Axis limit switch
#define yrstopper  9 //microswitch_D N.O   Orange LEFT Y-Axis limit switch
boolean DirectionX = true;
boolean DirectionY = true;
int window = 100; // guard band
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;
float prevVoltage =13.8;
float curVoltage =0.0;

/*
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output
int x,y;*/

void setup()
{ 
  Serial.begin(115200);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(xlstopper,INPUT); 
  pinMode(xrstopper,INPUT); 
  pinMode(ylstopper,INPUT); 
  pinMode(yrstopper,INPUT); 
  pinMode(dVm,INPUT);
  sim808.begin(9600); 
  delay(100);
  sim808.print("AT+CMGF=1\r");
  delay(400);
  sendData("AT+CGNSPWR=1",1000,DEBUG);
  delay(50);
  sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
  delay(150);
}

void loop() 
{
/*  x = analogRead(X_pin);
  y = analogRead(Y_pin);
  Serial.print("X-axis: ");
  Serial.print(x);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(y);
  Serial.print("\n\n");*/
  
  int T = analogRead(Top);
  int B = analogRead(Bottom);
  int L = analogRead(Left);
  int R = analogRead(Right);
  int YDirection =  T - B;
  int XDirection =  R - L;
 /* Serial.print("X axis: ");
  Serial.print(XDirection);
  Serial.print("   Y axis: ");
  Serial.print(YDirection);
  Serial.print("     T: ");
  Serial.print(T);
  Serial.print("  B: ");
  Serial.print(B);
  Serial.print("  L: ");
  Serial.print(L);
  Serial.print("  R: ");
  Serial.print(R);
  Serial.println(" ");*/

//delay(100);
  curVoltage = readBatteryVoltage();
  if (curVoltage < (prevVoltage -1)){
    prevVoltage = (prevVoltage -1);
    sendLocation();  
  }
Serial.println(curVoltage);
        //Motor X Axis
        if (XDirection > window){
          if (digitalRead(xlstopper) == HIGH){
          digitalWrite(in1,LOW);  
          digitalWrite(in2,LOW);
   //       Serial.println("X-Axis Left limit switch reached!");
          }else{
          digitalWrite(in1,HIGH);  
          digitalWrite(in2,LOW);
      //    Serial.println("X Axis CounterClockwise");
          }  
        }else if ((XDirection < -window)){
          if (digitalRead(xrstopper) == HIGH){
          digitalWrite(in1,LOW);  
          digitalWrite(in2,LOW);
     //     Serial.println("X-Axis Right limit switch reached!");
          }else{          
          digitalWrite(in1,LOW);  
          digitalWrite(in2,HIGH);
     //     Serial.println("X Axis Clockwise");
          }  
        }else{
          digitalWrite(in1,LOW);  
          digitalWrite(in2,LOW);
      //    Serial.println("X Axis Standby");
        }
        
        //Motor Y Axis
        if (YDirection > window){
          if (digitalRead(ylstopper) == HIGH){
          digitalWrite(in3,LOW);  
          digitalWrite(in4,LOW);
      //    Serial.println("Y-Axis Left limit switch reached!");
          }else{          
          digitalWrite(in3,HIGH);  
          digitalWrite(in4,LOW);
    //     Serial.println("Y Axis CounterClockwise");
          }  
        }else if (YDirection < -window){
          if (digitalRead(yrstopper) == HIGH){
          digitalWrite(in3,LOW);  
          digitalWrite(in4,LOW);
     //     Serial.println("Y-Axis Right limit switch reached!");
          }else{ 
          digitalWrite(in3,LOW);  
          digitalWrite(in4,HIGH);
      //    Serial.println("Y Axis Clockwise");
          }  
        }else{
          digitalWrite(in3,LOW);  
          digitalWrite(in4,LOW);      
     //     Serial.println("Y Axis Standby");    
        }
}

void sendLocation(){
//--------------------- send SMS containing google map location---------
  sendTabData("AT+CGNSINF",1000,DEBUG);
  if (state !=0){
    Serial.println("State  :"+state);
    Serial.println("Time  :"+timegps);
    Serial.println("Latitude  :"+latitude);
    Serial.println("Longitude  :"+longitude);
    sim808.print("AT+CMGS=\"");
    sim808.print(phone_no);
    sim808.println("\"");
    delay(300);
    sim808.print("http://maps.google.com/maps?q=loc:");
    sim808.print(latitude);
    sim808.print(",");
    sim808.print (longitude);
    delay(200);
    sim808.println("");
 //   sim808.println("Bettery Level:"+curVoltage);
    sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    sim808.println();
    delay(20000);
    sim808.flush();
  }else{Serial.println("GPS Initializing…");}
//----------------------
}

void sendTabData(String command , const int timeout , boolean debug){
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while((time+timeout) > millis()){
    while(sim808.available()){
      char c = sim808.read();
      if (c != ',') {
        data[i] +=c;
        delay(100);
      } else {i++;}
      if (i == 5) {
        delay(100);
        goto exitL;
      }
    }
  }exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude =data[4];
  }
}

String sendData (String command , const int timeout ,boolean debug){
  String response = "";
  sim808.println(command);
  long int time = millis();
  int i = 0;
  while ( (time+timeout ) > millis()){
    while (sim808.available()){
      char c = sim808.read();
      response +=c;
    }
  }
  if (debug) {Serial.print(response);}
  return response;
}

float readBatteryVoltage(){
   // read the value at analog input--------- 0 to 30V DVM
   value = analogRead(dVm);
   vout = (value * 5.0) / 1024.0;
   vin = vout / (R2/(R1+R2)); 
   vin = vin-3.3;
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
   }
   //-----------------------------------------
   return vin;
}






















