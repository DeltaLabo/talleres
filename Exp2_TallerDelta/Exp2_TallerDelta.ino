#include "Adafruit_VL53L0X.h"

uint8_t header[2]={0xAA,0xDD};
uint8_t footer[2]={0xAA,0xFF};  

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  if (!sensor.begin()) {
    //Serial.println("No se ha podido iniciar el sensor.");
    while(1);
  }

  //Serial.println("Iniciando medición...\n");
  sensor.startRangeContinuous();
}

void loop() {
  int distance = sensor.readRange()/10;

  if (distance >= 300) distance = 300;
    
  //Serial.println(medicion_cm);

  Serial.write(header,2);
  Serial.write( (distance>>8) & 0xFF);
  Serial.write( (distance) & 0xFF);
  Serial.write(footer,2);
  delay(100);
}


