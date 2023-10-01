from django.urls import path
from .consumers import SensorConsumer

ws_urlpatterns=[
    path('ws/graph/', SensorConsumer.as_asgi()),
]