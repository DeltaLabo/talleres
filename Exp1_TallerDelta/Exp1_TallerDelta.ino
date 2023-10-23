//se definen las variables a utilizar.
int azero = 0;
float v = 0;
float RT = 0;
float T = 0;
int seco = 0;
int minu = 0;
int hour = 0;
char time_stamp [50];

//se definen las constantes a utilizar.
#define RR 10240
#define BETA 4100
#define T0 298.15
#define R0 10000
#define zero 273.15

void setup() {
  //Se inicia la comunicación serial a 9600 bits por segundo (9600 baud).
  Serial.begin(9600);
}

void loop() {
  //Se lee el pin A0 del arduino mega.
  azero = analogRead(A0);

  //Se convierte la lectura A0 a voltaje.
  v = (azero/1023.0) * 5;

  //Se convierte la lectura A0 a resistencia.
  RT = (5/v) - 1;
  RT = RR/RT;

  //Se convierte la lectura A0 a temperatura.
  T = BETA + T0 * log(RT/R0);
  T = (BETA * T0) / T;
  T = T - zero;

  //Función para poder imprimir el tiempo transcurrido en formato (00h:00m:00s).
  sprintf(time_stamp, "%02d: %02d: %02d, ", hour, minu, seco);

    //Se realiza un condicional, para determinar cuando se alcanza la temperatura crítica.
    if (T >= 28){ //Se detecta una temperatura mayor a 30 grados.
      //Se imprime el mensaje de advertencia junto a la temperatura medida.
      Serial.print("Temperatura crítica alcanzada = "); 
      Serial.println(T);
    
    }
    else { //No se detecta la temperatura crítica.
      //Se imprime la medición de temperatura junto al tiempo en que esta se realizó.
      Serial.print(time_stamp);
      Serial.println(T);
    }

  delay(1000); //Esperar un segundo entre mediciones.
  seco++; //Aumenta el contador de segundos.

    if (seco >= 60){ //Si el contador de segundos llega a 60, pasa a aumentar los minutos.
      seco = 0;
      minu++; 
    }
    if (minu >= 60){ //Si el contador de minutos llega a 60, pasa a aumentar las horas.
      minu = 0;
      hour++; 
    }
}
