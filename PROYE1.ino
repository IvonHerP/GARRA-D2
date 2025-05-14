
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int Joy1x=A0;
int Joy1y=A1; 
int Joy2x=A5;
int Joy2y=A4;

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