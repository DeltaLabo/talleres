# Se importan todas las librerias necesarias. 
import warnings
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import serial.tools.list_ports

# Se inicia matplotlib (librería para la creación del gráfico del radar).
matplotlib.use('TkAgg')

# Función hecha para encontrar automáticamente el arduino en el port Serial respectivo.
arduinoPorts = [
    p.device
    for p in serial.tools.list_ports.comports() # Se explora todos los dispositivos Serial usados. 
    if 'Arduino' in p.description # Se buscan específicamente los serial de arduino. 
]
if len(arduinoPorts) == 1: # El arduino fue encontrado correctamente.
    print("Arduino port found")
if len(arduinoPorts) > 1: # Aviso, en caso de que se tenga más de un arduino conectado a la vez. 
    warnings.warn(
        "There are multiple Arduinos identified. Using the first identified Arduino port")
if not arduinoPorts: # No se encontró algún arduino.
    raise IOError("No Arduino port found")

arduinoData = serial.Serial(arduinoPorts[0])
arduinoData.flushInput()

# -----------------------------------------------------------------------------------------------------
# DE ACÁ EN ADELANTE EL CÓDIGO ÚNICAMENTE SE CENTRA EN LA CREACIÓN DEL GRÁFICO PARA LA REPRESENTACIÓN
# DEL RADAR. EN ESTA EXPERIENCIA NO SE CONTEMPLA QUE USTED ENTIENDA EL CÓMO CREAR ESTAS GRÁFICAS, POR
# LO QUE NO ES NECESARIO ESTUDIARLO, SIN EMBARGO SE LE ALIENTA A QUE LO HAGA.
# -----------------------------------------------------------------------------------------------------

# Se le dan las propiedades a la ventana. 
fig = plt.figure("Arduino Radar Scanner", facecolor='black')
fig.set_dpi(180) # Resolución de la figura.
fig.canvas.manager.window.wm_geometry("-340+75") # Posición de la ventana en la pantalla. 

# Se le dan las propiedades a la figura del radar. 
ax = fig.add_subplot(111, polar=True, facecolor='#288526')
ax.set_position([-0.05, -0.05, 1.1, 1.1]) # Posición del radar en la ventana.
ax.set_ylim([0.0, 100]) # Límite de distancia del radar.
ax.set_xlim([0.0, np.pi]) # Se crea el semicirculo que le da forma al radar. 
ax.set_thetagrids(np.linspace(0.0, 180.0, 7)) # El radar enseña 7 ángulos, entre 0 y 180 grados.

# Diseño del radar.
ax.tick_params(axis='both', colors='w')  # Color del texto
points, = ax.plot([], linestyle='', marker='.', markerfacecolor='#f1fff1',
markeredgecolor='w', markersize=8.0)  # Diseño de los puntos. 
line, = ax.plot([], color='#79f07b', linewidth=3.0)  # Diseño de las líneas.

# Variables.
angles = np.arange(0, 181, 1)  # Desde 0 hasta 180 grados.
theta = angles * (np.pi / 180.0)  # Se pasan los grados a radianes.
distances = np.ones((len(angles),))  # Distancias iniciales.

fig.canvas.toolbar.pack_forget()  # Se limpia la memoria de la figura.

# Diseño del la ventana.
fig.canvas.draw()  # Se abre la ventana.
axbackground = fig.canvas.copy_from_bbox(ax.bbox)  # Se le da un fondo.

fig.show()  # Se enseña la figura. 

# Procesamiento de datos.
while True:
    while arduinoData.inWaiting() == 0:  # No se reciben datos.
        pass
    arduinoString = arduinoData.readline()  # Se reciben los datos. 
    decodedBytes = arduinoString.decode('utf')  # Los datos se decodifican para su lectura. 
    data = (decodedBytes.replace('\r', '')).replace('\n', '')

    # Los datos de distancia y ángulo se guardan en una lista. 
    dataList = [float(x) for x in data.split(',')]
    angle = dataList[0]  # Se define el ángulo en la lista.
    distance = dataList[1]  # Se define la distancia en la lista. 

    # Si se obtienen distancias mayores al limite del radar se igualan a 0.
    if distance > 100:
        distance = 0

    distances[int(angle)] = distance

    points.set_data(theta, distances)  # Se colocan los puntos según la distancia medida.
    fig.canvas.restore_region(axbackground)  # Se "reinicia" la ventana.
    ax.draw_artist(points)  # Se dibujan los puntos.

    line.set_data(np.repeat((angle * (np.pi / 180.0)), 2),  # Se dibujan lineas entre 0 y 180 grados.
                  np.linspace(0.0, 100, 2))  # Se dibuja la línea que indica el límite de 100 cm.
    ax.draw_artist(line)  # Se dibujan las líneas del radar. 

    fig.canvas.blit(ax.bbox)
    fig.canvas.flush_events() 
