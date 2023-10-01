import serial
import matplotlib.pyplot as plt


ser = serial.Serial('/dev/ttyUSB0', 9600)


time_data = []
sensor_data = []


plt.ion()
fig, ax = plt.subplots()


line, = ax.plot(time_data, sensor_data)
ax.set_title('Vibration Sensor Data')
ax.set_xlabel('Time')
ax.set_ylabel('Sensor Value')


ax.set_xlim(0, 100)

try:
    while True:
        data = ser.readline().decode().strip()
        parts = data.split(":")
        if len(parts) == 2:
            variable_name = parts[0].strip()
            variable_value = parts[1].strip()

            if variable_name == "Vibration Sensor A":
                time_data.append(len(time_data))
                sensor_data.append(variable_value)

            line.set_data(time_data, sensor_data)
            ax.relim()
            ax.autoscale_view()

            # Pause to allow the plot to update
            plt.pause(0.01)

except KeyboardInterrupt:
    ser.close()
    plt.ioff()
    plt.show()
