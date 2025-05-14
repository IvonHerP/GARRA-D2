
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int Joy1x=A0;
int Joy1y=A1; 
int Joy2x=A5;
int Joy2y=A4;


const int Btn1=A2;
const int Btn2=A3;
int swich=3;

int ledm=7;
int leda=8;

int autom[5][4]={
  {0, 45, 90, 130},
  {30, 60, 120, 150},
  {60, 90, 90, 60},
  {90, 120, 60, 30},
  {120, 180, 0, 0}
};

void setup() {
  
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(6);
  myservo4.attach(5);

  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);
  pinMode(swich, INPUT_PULLUP);

  pinMode(ledm, OUTPUT);
  pinMode(leda, OUTPUT);
}

void loop() {
   bool isManual = digitalRead(modeSwitch);

  if (isManual) {
    digitalWrite(ledManual, HIGH);
    digitalWrite(ledAuto, LOW);
    modoManual();
  } else {
    digitalWrite(ledManual, LOW);
    digitalWrite(ledAuto, HIGH);
    modoAutomatico();
  }
}
void modoManual() {
  myservo1.write(map(analogRead(Joy1x),0,1023,0,180));
  myservo2.write(map(analogRead(Joy1y),0,1023,0,180));
  myservo3.write(map(analogRead(Joy2x),0,1023,0,180));
  myservo4.write(map(analogRead(Joy2y),0,1023,0,180));
  delay(15);
    myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);

  mostrarPosiciones(pos1, pos2, pos3, pos4);
  delay(15);
}
