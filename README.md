# NiyantaPipeline - Pipeline Security System
Project for KU Hackfest 2023

## Introduction
NiyantaPipeline is a smart system that keeps important fuel pipelines safe. It constantly watches and quickly identifies any unusual activity, making sure the fuel keeps moving smoothly and safely.

## Key Features
a) Sensor Integration: Utilizes advanced sensors like vibration and flow sensors for real-time monitoring.
b) Anomaly Detection: Detects unauthorized access, tampering, or irregularities in pipeline activity.
c) Immediate Alerts: Triggers instant alerts by doing led high.
d) Precise Location Tracking: Incorporates GPS modules to enable accurate location tracking during security events.

## How It Works

The system employs a combination of hardware and software technologies. Sensors continuously monitor the pipeline, sending data to a microcontroller. This data is processed, and in case of anomalies, immediate alerts are generated for prompt action.

## Setup
    Clone Repository: git clone <https://github.com/Team-Maharathi/NiyantaPipeline.git>
    Install Dependencies: pip install -r requirements.txt
    Database Migration: python manage.py migrate
    Run the Server: python manage.py runserver
    Access the System: Open a web browser and go to http://localhost:8000/

## Branches

    iot-side: Contains code for sensor integration and communication.
    server-side: Holds backend logic and setup.
    client-side: Includes code for the user interface.

## Challenges Faced
We encountered challenges in sourcing specific IoT equipment and optimizing internet connectivity. Overcoming these hurdles, we refined our solutions and improved the system's efficiency.

## Future Enhancements
In the future, we aim to expand the system by incorporating additional sensors to measure temperature and pressure. Developing a mobile application for real-time alerts is on the roadmap, enhancing user accessibility and responsiveness.
