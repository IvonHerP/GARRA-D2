//IVON HERNANDEZ 231111

#include <Servo.h> 

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int JOY1X= A0;
const int JOY1Y= A1;
const int JOY2X= A5;
const int JOY2Y= A4;

const int BTNA= A2;
const int BTNR= A3;

const int SWICH= 3; 

const int LEDMANUAL =7;
const int LEDAUTO= 8;


const int NPOSICIONES = 5; 
int autom[5][4] = {
  {0, 0, 0, 0},   
  {30, 60, 120, 150}, 
  {60, 90, 90, 60},  
  {90, 120, 60, 30}, 
  {120, 180, 0, 0}   
};
int posactual = 0; 

unsigned long Tiempoavance = 0;
unsigned long Tiempoatras = 0;
const long AR = 200; 


// Función 1: Mapea el valor de la lectura de un joystick (0-1023) a grados de servo (0-180)
int mapearJoystickAServo(int valorJoystick) {
  return map(valorJoystick, 0, 1023, 0, 180);
}

// Función 2: Muestra la posición actual de los servomotores en el Serial Monitor
void mostrarPosiciones(int p1, int p2, int p3, int p4) {
  Serial.print("S1: "); Serial.print(p1);
  Serial.print(" | S2: "); Serial.print(p2);
  Serial.print(" | S3: "); Serial.print(p3);
  Serial.print(" | S4: "); Serial.println(p4);
}

void setup() {
  Serial.begin(9600);

  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(6);
  myservo4.attach(5);

  pinMode(BTNA, INPUT_PULLUP);
  pinMode(BTNR, INPUT_PULLUP);
  pinMode(SWICH, INPUT_PULLUP);

  pinMode(LEDMANUAL, OUTPUT);
  pinMode(LEDAUTO, OUTPUT);

  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
}


void loop() {

  if (digitalRead(SWICH) == LOW) {
    digitalWrite(LEDMANUAL, HIGH);   // Enciende LED de Modo Manual
    digitalWrite(LEDAUTO, LOW); // Apaga LED de Modo Automático
    modoManual();
  } else {
    digitalWrite(LEDMANUAL, LOW);    // Apaga LED de Modo Manual
    digitalWrite(LEDAUTO, HIGH); // Enciende LED de Modo Automático
    modoAutomatico();
  }
}


void modoManual() {
  // Lee los valores de los joysticks y los mapea a grados de servo (0-180).
  int pos1 = mapearJoystickAServo(analogRead(JOY1X));
  int pos2 = mapearJoystickAServo(analogRead(JOY1Y));
  int pos3 = mapearJoystickAServo(analogRead(JOY2X));
  int pos4 = mapearJoystickAServo(analogRead(JOY2Y));

  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);

  // Muestra las posiciones en el Serial Monitor.
  Serial.print("MODO: MANUAL | ");
  mostrarPosiciones(pos1, pos2, pos3, pos4);

  delay(50); 
}

void modoAutomatico() {

  if (digitalRead(BTNA) == LOW && (millis() - Tiempoavance) > AR) {
    posactual = (posactual + 1) % NPOSICIONES; 
    Tiempoavance = millis();
  }

  if (digitalRead(BTNR) == LOW && (millis() - Tiempoatras) > AR) {
    posactual = (posactual - 1 + NPOSICIONES) % NPOSICIONES;
    Tiempoatras = millis(); 
  }
  myservo1.write(autom[posactual][0]);
  myservo2.write(autom[posactual][1]);
  myservo3.write(autom[posactual][2]);
  myservo4.write(autom[posactual][3]);

  Serial.print("MODO: AUTOMATICO | POSICION: "); Serial.print(posactual + 1); Serial.print(" | ");
  mostrarPosiciones(
    autom[posactual][0],
    autom[posactual][1],
    autom[posactual][2],
    autom[posactual][3]
  );
  delay(50);
}