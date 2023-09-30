import json
import asyncio
import serial
from channels.generic.websocket import AsyncWebsocketConsumer

class SensorConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        await self.accept()

        # Open a connection to your Arduino
        self.serial = serial.Serial('COM3', 9600)  # Adjust port and baud rate

        # Start a task to read data from the Arduino and send it to clients
        asyncio.create_task(self.send_sensor_data())

    async def disconnect(self, close_code):
        # Close the serial connection on disconnect
        self.serial.close()

    async def send_sensor_data(self):
        while True:
            try:
                # Read data from the Arduino
                data = self.serial.readline().decode().strip()
                sensor_data = json.loads(data)

                # Send the data to the WebSocket
                await self.send(text_data=json.dumps(sensor_data))
            except json.JSONDecodeError:
                pass  # Handle JSON decoding errors if necessary
            except asyncio.CancelledError:
                break  # Task was cancelled on disconnect

