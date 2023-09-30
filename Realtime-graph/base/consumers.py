import json
import asyncio
import serial
from channels.generic.websocket import AsyncWebsocketConsumer

arduino = serial.Serial('/dev/ttyUSB0', 9600)

try:
    while True:
        # Read data from the serial port
        data = arduino.readline().decode().strip()
        print(data)

except KeyboardInterrupt:
    arduino.close()



# class SensorConsumer(AsyncWebsocketConsumer):
#     def __init__(self, *args, **kwargs):
#         print("i m here")
#         super().__init__(*args, **kwargs)
#         self.serial = None
#
#     async def connect(self):
#         print("Connecting...")
#         await self.accept()
#
#         # Making connection to the arduino for getting data
#         self.serial = serial.Serial('/dev/ttyUSB0', 9600)
#         print(self.serial)
#
#         # Connection making to read data from the arduino
#         asyncio.create_task(self.send_sensor_data())
#
#     async def disconnect(self, close_code):
#         self.serial.close()
#         # disconnection the serial connection
#
#     async def send_sensor_data(self):
#         while True:
#             try:
#                 data = self.serial.readline().decode().strip()
#                 sensor_data = json.loads(data)
#                 print(sensor_data)
#
#                 # Sending data to the web socket
#                 await self.send(text_data=json.dumps(sensor_data))
#             except json.JSONDecodeError:
#                 pass
#             except asyncio.CancelledError:
#                 break
