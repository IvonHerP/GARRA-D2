//IVON HERNANDEZ 231111

#include <Servo.h> // Necesitamos esta librería para que los servos funcionen. ¡Es como la base!

// Aquí estoy definiendo mis servomotores. Tengo cuatro, así que los nombro para no hacerme bolas.
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// Estos son los pines donde conecté los joysticks. A0, A1, A5, A4 son pines analógicos,
// que son los que saben leer los movimientos de los joysticks.
const int JOY1X = A0; // Joystick 1, eje X
const int JOY1Y = A1; // Joystick 1, eje Y
const int JOY2X = A5; // Joystick 2, eje X
const int JOY2Y = A4; // Joystick 2, eje Y

// Aquí están los botones. Uno es para avanzar y el otro para retroceder en el modo automático.
const int BTNA = A2; // Botón para "Avanzar" (seguro es A de avanzar)
const int BTNR = A3; // Botón para "Retroceder" (R de retroceder, ¿verdad?)

// Este es el switch para cambiar entre modo manual y automático.
const int SWICH = 3; // Un switch, ¿qué hará? ¡Pues cambiar de modo!

// Mis LEDs indicadores para saber en qué modo estoy.
const int LEDMANUAL = 7; // Este se prende si estoy en modo manual
const int LEDAUTO = 8; // Y este si estoy en modo automático

// Aquí defino cuántas posiciones pregrabadas tengo para el modo automático.
const int NPOSICIONES = 5; // Tengo 5 posiciones guardadas, ni una más, ni una menos.

// Esta es la matriz mágica que guarda las posiciones de los servos para el modo automático.
// Cada fila es una posición y cada columna es un servo. ¡Es como una tabla de coreografías!
int autom[5][4] = {
  {120, 0, 0, 90}, // Posición 1: Valores para servo 1, servo 2, servo 3, servo 4
  {0, 180, 95, 95}, // Posición 2
  {0, 180, 95, 95}, // Posición 3 (esta se repite, ¡qué flojera!)
  {90, 120, 0, 30}, // Posición 4
  {0, 180, 95, 95}  // Posición 5 (otra que se repite, ¿ya viste?)
};
int posactual = 0; // Esta variable me dice en qué posición automática estoy. Empieza en la primera (0).

// Estas variables son para controlar el tiempo y que los botones no se aprieten mil veces por segundo.
// Es como un "debounce" pero a mi manera.
unsigned long Tiempoavance = 0; // Guarda el último momento en que apreté el botón de avanzar
unsigned long Tiempoatras = 0;  // Guarda el último momento en que apreté el botón de retroceder
const long AR = 200; // Es como un tiempo de espera para los botones, 200 milisegundos.

// ---

## Funciones útiles (las que me ayudan un montón)

// Función 1: Mapea el valor de la lectura de un joystick (0-1023) a grados de servo (0-180)
// Los joysticks dan números de 0 a 1023, pero los servos solo entienden de 0 a 180 grados.
// Esta función traduce eso, ¡es como un intérprete!
int mapearJoystickAServo(int valorJoystick) {
  return map(valorJoystick, 0, 1023, 0, 180);
}

// Función 2: Muestra la posición actual de los servomotores en el Serial Monitor
// Para ver qué está pasando, imprimo los valores de cada servo en el monitor serial.
// Así sé si se están moviendo como yo quiero.
void mostrarPosiciones(int p1, int p2, int p3, int p4) {
  Serial.print("S1: "); Serial.print(p1); // Servo 1
  Serial.print(" | S2: "); Serial.print(p2); // Servo 2
  Serial.print(" | S3: "); Serial.print(p3); // Servo 3
  Serial.print(" | S4: "); Serial.println(p4); // Servo 4, y un salto de línea para que se vea bonito
}

// ---

## Configuración inicial (¡una sola vez al principio!)

void setup() {
  Serial.begin(9600); // Esto es para poder ver los mensajes en la computadora.

  // Aquí le digo a qué pines están conectados mis servos. ¡No los puedo conectar en cualquier lado!
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(6);
  myservo4.attach(5);

  // Defino que los botones y el switch son entradas. INPUT_PULLUP es para que no anden
  // "flotando" y den lecturas raras.
  pinMode(BTNA, INPUT_PULLUP);
  pinMode(BTNR, INPUT_PULLUP);
  pinMode(SWICH, INPUT_PULLUP);

  // Y los LEDs son salidas, porque yo los voy a prender y apagar.
  pinMode(LEDMANUAL, OUTPUT);
  pinMode(LEDAUTO, OUTPUT);

  // Estas son las posiciones iniciales de los servos cuando el programa arranca.
  // ¡Para que no empiecen locos!
  myservo1.write(180);
  myservo2.write(180);
  myservo3.write(180);
  myservo4.write(90);
}

// ---

## El loop principal (¡esto se repite una y otra vez!)

void loop() {
  // Aquí es donde decido si estoy en modo manual o automático.
  // Si el switch está en LOW (es decir, lo estoy presionando o está conectado a tierra),
  // entro al modo manual. Si no, ¡al automático!
  if (digitalRead(SWICH) == LOW) {
    digitalWrite(LEDMANUAL, HIGH);  // Prendo el LED de manual
    digitalWrite(LEDAUTO, LOW);     // Apago el de automático
    modoManual();                   // Llamo a la función que maneja el modo manual
  } else {
    digitalWrite(LEDMANUAL, LOW);   // Apago el LED de manual
    digitalWrite(LEDAUTO, HIGH);    // Prendo el de automático
    modoAutomatico();               // Llamo a la función que maneja el modo automático
  }
}

// ---

## Modo Manual (¡para que yo controle todo!)

void modoManual() {
  // Leo los valores de los joysticks. Cada uno me da un número.
  int pos1 = mapearJoystickAServo(analogRead(JOY1X));
  int pos2 = mapearJoystickAServo(analogRead(JOY1Y));
  int pos3 = mapearJoystickAServo(analogRead(JOY2X));
  int pos4 = mapearJoystickAServo(analogRead(JOY2Y));

  // Y ahora le digo a cada servo que se mueva a la posición que me dio el joystick.
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);

  // Muestro en el monitor serial que estoy en modo manual y dónde están los servos.
  Serial.print("MODO: MANUAL | ");
  mostrarPosiciones(pos1, pos2, pos3, pos4);

  delay(50); // Un pequeño retraso para que no vaya tan rápido y se estabilice.
}

// ---

## Modo Automático (¡para que se mueva solo!)

void modoAutomatico() {
  // Aquí checo si apreté el botón de avanzar y si ya pasó suficiente tiempo desde la última vez.
  // Esto evita que al dejarlo presionado se salte muchas posiciones.
  if (digitalRead(BTNA) == LOW && (millis() - Tiempoavance) > AR) {
    posactual = (posactual + 1) % NPOSICIONES; // Avanzo a la siguiente posición.
    // El '%' es para que, cuando llegue al final, regrese a la primera posición (es un ciclo).
    Tiempoavance = millis(); // Guardo el tiempo actual para la próxima vez.
  }

  // Lo mismo, pero para el botón de retroceder.
  if (digitalRead(BTNR) == LOW && (millis() - Tiempoatras) > AR) {
    posactual = (posactual - 1 + NPOSICIONES) % NPOSICIONES; // Retrocedo a la posición anterior.
    // El '+ NPOSICIONES' es un truco para que si estoy en la posición 0 y retrocedo, vaya a la última.
    Tiempoatras = millis(); // Guardo el tiempo actual.
  }

  // Ahora, muevo los servos a las posiciones que tengo guardadas en mi matriz 'autom'.
  myservo1.write(autom[posactual][0]); // Servo 1 toma el valor de la posición actual en la columna 0
  myservo2.write(autom[posactual][1]); // Servo 2 toma el valor de la posición actual en la columna 1
  myservo3.write(autom[posactual][2]); // Servo 3 toma el valor de la posición actual en la columna 2
  myservo4.write(autom[posactual][3]); // Servo 4 toma el valor de la posición actual en la columna 3

  // Imprimo en el monitor serial que estoy en modo automático, en qué posición voy,
  // y las posiciones de los servos.
  Serial.print("MODO: AUTOMATICO | POSICION: "); Serial.print(posactual + 1); Serial.print(" | ");
  mostrarPosiciones(
    autom[posactual][0], // Imprimo el valor del servo 1 para esta posición
    autom[posactual][1], // Imprimo el valor del servo 2
    autom[posactual][2], // Imprimo el valor del servo 3
    autom[posactual][3]  // Imprimo el valor del servo 4
  );
  delay(50); // Otro pequeño retraso, ¡para que no se ponga loco!
}
