from django.urls import re_path

from backend.data_io.consumers import SensorConsumer

websocket_urlpatterns = [
    re_path(r'ws/sensors/', SensorConsumer.as_asgi()),
]
