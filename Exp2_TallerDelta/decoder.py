# Taller de visualización de datos en Python a través
# comunicación serial con arduino
from datetime import datetime
import serial
import matplotlib.pyplot as plt
from drawnow import drawnow

# Inicializa el serial
ArduinoData = serial.Serial('COM4', baudrate=9600, bytesize=8,
                            parity='N', stopbits=1, timeout=1.5)

# verfica que la instancancia serial esté cerrada
ArduinoData.close()

# Abrir la instancia serial
ArduinoData.open()

# Flush: wait until all data is written
ArduinoData.flush()

# crea e inicializa la variable a almacenar la distancia
distance = 0

# Se graba el instante de tiempo actual
past_time = datetime.now()

# crea e inicializa la variable a almacenar el tiempo transcurrido
seconds = 0

# Crea la lista vacía para almacenar el tiempo y la distancia
time_data = []
dist_data = []

# Crear la canvas para la figura
plt.ion()     # tell matplotlib you want interactive mode to plot data
fig = plt.figure()


def dist_figure() -> None:
    # Función para "imprimir" los últimos 100 datas de distancia
    ax1 = plt.subplot()
    plt.plot(time_data[-100:], dist_data[-100:])
    ax1.set(xlabel='time (s)', ylabel='distance (cm)',
            title='VL53LOX measurements')


while True:
    # Lee el primer byte de la información transmitidad por
    #  en el serial
    recep = ArduinoData.read(1)

    match recep:
        case b'\xAA':
            if ArduinoData.read(1) == b'\xDD':
                distance = int.from_bytes(ArduinoData.read(2), 'big')
                # int.from_bytes(bytes, byteorder, *, signed=False)
                # bytes – A byte object
                # byteorder – Determines the order of representation of the integer value.
                # byteorder can have values as either “little” where most significant bit
                # is stored at the end and least at the beginning, or big, where MSB is
                # stored at start and LSB at the end.

                tiempo_actual = datetime.now()
                deltat = (tiempo_actual - past_time).total_seconds()
                past_time = tiempo_actual
                seconds += deltat
                time_data.append(seconds)
                dist_data.append(distance)
                drawnow(dist_figure)
