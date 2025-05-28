
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int Joy1x=A0;
const int Joy1y=A1; 
const int Joy2x=A5;
const int Joy2y=A4;

const int BTNA=A2;
const int BTNR=A3;

const int SWICH= 3;
const int LEDMANUAL= 7;
const int LEDAUTO=8;

const int NPOSICIONES = 5;
int autom[5][4]
void setup() {
  
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(6);
  myservo4.attach(5);
}

void loop() {

  myservo1.write(map(analogRead(Joy1x),0,1023,0,180));
  myservo2.write(map(analogRead(Joy1y),0,1023,0,180));
  myservo3.write(map(analogRead(Joy2x),0,1023,0,180));
  myservo4.write(map(analogRead(Joy2y),0,1023,0,180));
  delay(15);
  
}
