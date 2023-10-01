

import json
import asyncio
import serial
from channels.generic.websocket import AsyncWebsocketConsumer

class SensorConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        await self.accept()

        # Making connection to the arduino for getting data 
        self.serial = serial.Serial('COM3', 9600) 

        # Connection making to read data from the arduino
        asyncio.create_task(self.send_sensor_data())

    async def disconnect(self, close_code):
        self.serial.close()
        # disconnection the serial connection

    async def send_sensor_data(self):
        while True:
            try:
                data = self.serial.readline().decode().strip()
                sensor_data = json.loads(data)

                # Sending data to the web socket
                await self.send(text_data=json.dumps(sensor_data))
            except json.JSONDecodeError:
                pass  
            except asyncio.CancelledError:
                break  
