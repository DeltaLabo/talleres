#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  if (!sensor.begin()) {
    Serial.println("No se ha podido iniciar el sensor.");
    while(1);
  }

  Serial.println("Iniciando medición...\n");
  sensor.startRangeContinuous();
}

void loop() {
  int medicion_cm = sensor.readRange()/10;

  if (medicion_cm >= 150){
    int medicion_cm = 0;
    Serial.println(medicion_cm);
  }
  else{
    Serial.println(medicion_cm);
  }
  
  delay(100);
}


