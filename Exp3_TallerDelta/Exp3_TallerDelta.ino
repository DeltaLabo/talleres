// Incluir librería para el servomotor.
#include <Servo.h>

// Se definen los pines para el sensor ultrasónico y el servomotor en el arduino. 
#define trigPin 5
#define echoPin 6
#define servoPin 8

// Se definen las variables para las mediciones del sensor y la obtención del ángulo al que se encuentra el servo. 
float duration;
float distance;
int angle;

// Se crea el objeto servomotor.
Servo servoMotor;

void setup() {
  // Se definen las entradas y salidas del sensor ultrasónico.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Se inicia el servomotor.
  servoMotor.attach(servoPin);
  Serial.begin(9600);
}

void loop() {

  // Rota de 30 a 150 grados, esto puede cambiarse hasta un máximo de 0 y 180 grados respectivamente. 
  for (angle = 30; angle <= 150; angle++) { // Hace un loop, aumentando el ángulo en 1 cada vez. 
    // Mueve el servo a dicho ángulo.
    servoMotor.write(angle);
    delay(10);
    // Se calcula la distancia medida por el sensor ultrasónico y se envía por serial.
    calculateDistance(angle);
    displayData();
  }
  // Rota de 150 a 30 grados, esto puede cambiarse hasta un máximo de 180 y 0 grados respectivamente. 
  for (angle = 150; angle >= 30; angle--) { // Hace un loop, reduciendo el ángulo en 1 cada vez. 
    servoMotor.write(angle);
    delay(10);
    calculateDistance(angle);
    displayData();
  }

}

// Función para calcular la distancia medida por el servomotor.
float calculateDistance(int angle) {

  // Se "limpia" el pin de Trigger.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Se enciende el pin de Trigger, por 10 microsegundos. 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Se lee la duración de la onda ultrasónica enviada por el sensor. 
  duration = pulseIn(echoPin, HIGH);

  // Se calcula la distancia
  distance = duration * (0.0343) / 2; // La duración se multiplica por la velocidad del sonido (cm/μs) y se divide entre 2.

  // Condicional para enviar a 0 las distancias fuera de rango del sensor. 
  if (distance >= 400 || distance <= 3) {
    distance = 0;
  }

}

// Se envian los datos por serial. 
void displayData() {
  Serial.print(angle); // Ángulo del servomotor.
  Serial.print(",");
  Serial.println(distance); // Distancia de medición (cm).
}