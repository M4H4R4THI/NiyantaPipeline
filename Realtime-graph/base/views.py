import json
import os

from django.shortcuts import render
import serial
from django.http import JsonResponse


def index(request):
    return render(request, 'base/index.html')


arduino = serial.Serial('/dev/ttyUSB0', 9600)


def read_sensor_data(request):
    try:
        sensor_data = {}  # Initialize an empty dictionary to store the data

        while True:
            # Read data from the serial port
            line = arduino.readline().decode().strip()
            print(line)

            # Split the line by ':' to separate variable name and value
            parts = line.split(":")
            if len(parts) == 2:
                variable_name = parts[0].strip()
                variable_value = parts[1].strip()

                # Add the variable and its value to the dictionary
                sensor_data[variable_name] = variable_value

                # Send the sensor data as a JSON response
                return JsonResponse(sensor_data)

    except Exception as e:
        return JsonResponse({'error': str(e)})
