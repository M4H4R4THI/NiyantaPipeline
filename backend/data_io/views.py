from django.shortcuts import render

def index(request):
    return render(request, 'data_io/index.html')