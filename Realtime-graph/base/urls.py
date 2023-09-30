from django.urls import path
from .views import index, read_sensor_data

urlpatterns = [
    path('', index, name='index'),
    path('read_arduino_data/', read_sensor_data, name='read_arduino_data'),
]
