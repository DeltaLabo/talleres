import serial
import matplotlib.pyplot as plt
from drawnow import drawnow
from datetime import datetime

ser = serial.Serial('COM11', baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=1.5)
ser.close()
ser.open()
ser.flush()
distance = 0
past_time = datetime.now()
seconds = 0

time_data = []
dist_data = []

plt.ion()
fig = plt.figure()

def dist_figure():
    ax1 = plt.subplot()
    plt.plot(time_data[-100:],dist_data[-100:])
    ax1.set(xlabel='time (s)', ylabel='distance (cm)',
       title='VL53LOX measurements')


while(True):
    recep = ser.read(1)
    match recep:
        case b'\xAA':
            if ser.read(1) == b'\xDD':
                distance = int.from_bytes(ser.read(2), 'big')
                tiempo_actual = datetime.now()
                deltat = (tiempo_actual - past_time).total_seconds()
                past_time = tiempo_actual
                seconds += deltat
                time_data.append(seconds)
                dist_data.append(distance)
                drawnow(dist_figure)