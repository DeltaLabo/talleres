// Incluir librería para el sensor
#include "Adafruit_VL53L0X.h"
// Hacer un #define para que la libreria TimerInterrupt cargue el Timer3
#define USE_TIMER_3     true
// Incluir librería para interrupciones basadas en tiempo
#include "TimerInterrupt.h"

// Definir variable para guardar la medición del sensor
int distance = 0;
// Definir variable para levantar la bandera del timer
bool timer_flag = true;
// Definir el encabezado y la cola del la trama que se enviará por serial
uint8_t header[2]={0xAA,0xDD};
uint8_t footer[2]={0xAA,0xFF};  

// Definir el intervalo del timer en milisegundos
#define TIMER_INTERVAL_MS        100

// Definir una instacia del sensor del tipo "Adafruit_VL530X" y con el nombre "sensor"
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  // Inicializar el puerto serial
  Serial.begin(9600);
  // Inicializar el sensor
  if (!sensor.begin()) {
    Serial.println("No se ha podido iniciar el sensor.");
    while(1);
  }
  // Iniciar medición continua
  sensor.startRangeContinuous();
  // Inicializar el Timer 3
  ITimer3.init();
  // Asignar una interrupción por tiempo que ejecuta la función "TimerHandler"
  if (ITimer3.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler))
  {
    Serial.print(F("Starting  ITimer3 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer3. Select another freq. or timer"));
}

void TimerHandler()
{
  // Cuando se activa la función se sube la bandera
  timer_flag = true;
}

void loop() {
  //Serial.println(medicion_cm);
  if (timer_flag)
  {
    distance = sensor.readRange()/10;
    if (distance >= 300) distance = 300;
    Serial.write(header,2);
    Serial.write( (distance>>8) & 0xFF);
    Serial.write( (distance) & 0xFF);
    Serial.write(footer,2);
    timer_flag = 0;
  }
}




