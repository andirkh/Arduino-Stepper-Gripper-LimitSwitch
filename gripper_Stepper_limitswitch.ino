/* Code Gripper Stepper Limit Switch TA
*  25 Desember 2016
*/

#include <Servo.h>

Servo thisServo;

int pos = 0;        //variabel posisi servo
int Pulse = 0;     //variabel pulse stepper

//variabel limit switch
int limitSwitchPin1 = 12;  
int limitSwitchPin2 = 11;
int limitBelakangValue = 0;
int limitDepanValue = 0;

//variabel arah stepper
boolean maju = false; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pin servo 
  thisServo.attach(10);
  
  //pin stepper
  pinMode(8, OUTPUT);             //pin 8 (Dir Pin) to CW+
  pinMode(9, OUTPUT);             //pin 9 (Step pin) to CLK +
                                  //CLK- CW- connect to GND arduino
                                  //didn't  & don't connect EN+ EN-
  digitalWrite(8,HIGH);
  digitalWrite(9, LOW);
  
  //limit switch
  pinMode(limitSwitchPin1, INPUT);
  pinMode(limitSwitchPin2, INPUT);
  
  //inisialisasi awal servo buka 80
  thisServo.write(80);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  limitBelakangValue = digitalRead(limitSwitchPin1);  
  limitDepanValue = digitalRead(limitSwitchPin2);
  
  stepper();
  
  if (limitBelakangValue == HIGH) {         // check if the input is HIGH (button released)
    maju = true;
    Pulse = 0;
  } else if (limitDepanValue == HIGH ){
    maju = false;
    Pulse = 0;
  }
  
  if (maju == true) {
     stepperMaju();
     if (Pulse == 1){
       servoBuka();
     }
  } else if (maju == false) {
     stepperMundur();
     if (Pulse == 1){
       servoTutup();
     }
  }

  if (Pulse == 770) {
     if (digitalRead(8) == LOW){
        maju = false;
        //stepperMundur(); 
        //servoTutup();
        
     } else {
        maju = true;
        //stepperMaju(); 
        //servoBuka();
     }
     Pulse = 0;
  }
  
   Serial.println(Pulse);
}

/*
* ------------------------------------
*   Various Function Here :
* ------------------------------------
*/

void stepper(){
  digitalWrite(9, HIGH);
  delayMicroseconds(50);
  digitalWrite(9, LOW);
  delayMicroseconds(50);
  Pulse = Pulse + 1;
}

void servoBuka() {
  //maksudnya dari posisi tutup ke buka
  for (pos = 118; pos >= 80; pos -= 1){
     thisServo.write(pos);
     delay(5);
  }
}

void servoTutup() {
  //maksudnya dari posisi buka ke tutup
  for (pos = 80; pos <= 118; pos += 1){
     thisServo.write(pos);
     delay(5);
   }
}

void stepperMaju(){
  digitalWrite(8,LOW);
}

void stepperMundur(){
  digitalWrite(8,HIGH);
}
