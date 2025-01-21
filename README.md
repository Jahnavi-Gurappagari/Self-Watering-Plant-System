# Self-Watering-Plant-System

Self-Watering Plant System

This project demonstrates a self-watering plant system designed to automate irrigation for plants by monitoring soil moisture levels, water tank levels, temperature, and humidity. It uses sensors and a microcontroller to ensure plants are watered adequately while optimizing water usage. Additionally, it integrates with the Blynk platform for real-time monitoring and notifications.

What the Project Does

This system automates plant irrigation by:

  . Monitoring soil moisture levels using a soil moisture sensor.

  . Measuring water tank levels using an ultrasonic sensor.

  . Tracking environmental conditions such as temperature and humidity using a DHT11 sensor.

  . Controlling a water pump via a relay to irrigate the plant when soil moisture is low.

  . Sending real-time data to the Blynk app for remote monitoring and alerts.

  . Providing critical notifications when water levels are low in the reservoir.

Motive of the Project

The primary goal of this project is to reduce manual effort in plant care and promote efficient water usage by automating the irrigation process. It ensures that plants are watered based on their needs, helping users maintain healthy plants while conserving water and minimizing waste.

Materials Required

  1. Microcontroller: ESP8266 NodeMCU

  2. Soil Moisture Sensor: To measure soil moisture levels

  3. Ultrasonic Sensor: HC-SR04 to measure water tank levels

  4. DHT11 Sensor: For temperature and humidity readings

  5. Relay Module: To control the water pump

  6. Water Pump: Submersible pump for irrigation

  7. Power Supply: USB or battery pack

  8.Connecting Wires: For connections between components

  9. Breadboard: For prototyping connections

  10. Software:

        . Arduino IDE

        . Blynk app (for remote monitoring)

Connections and Setup

Hardware Connections

  1. Soil Moisture Sensor:

      . VCC to 3.3V on ESP8266

      . GND to GND on ESP8266

      . Signal to Analog Pin A0 on ESP8266

  2. Ultrasonic Sensor (HC-SR04):

      . VCC to 5V on ESP8266

      . GND to GND on ESP8266

      . Trig to Digital Pin D8

      . Echo to Digital Pin D9

  3. DHT11 Sensor:

      . VCC to 5V on ESP8266

      . GND to GND on ESP8266

      . Data to Digital Pin D2

  4. Relay Module:

      . Signal Pin to Digital Pin D3

      . VCC to 5V on ESP8266

      . GND to GND on ESP8266

  5. Water Pump:

      . Connected to the NO (Normally Open) and COM terminals of the relay

      . Powered by an external 12V DC supply

Software Setup

  1. Install the Arduino IDE from Arduino's official website.

  2. Install the necessary libraries:

      . ESP8266WiFi

      . BlynkSimpleEsp8266

      . DHT

  3. Configure the Blynk app:

      . Create a new project in the Blynk app.

      . Add widgets for monitoring soil moisture, temperature, humidity, and water level.

      . Note down the Blynk authentication token.

  4. Modify the code:

      . Update the ssid and pass variables with your Wi-Fi credentials.

      . Set the BLYNK_AUTH_TOKEN with your Blynk project token.

Code Overview

The code handles the following tasks:

  . Reads sensor data (soil moisture, water level, temperature, and humidity).

  . Sends data to the Blynk app for remote monitoring.

  . Controls the water pump via the relay based on soil moisture readings.

  . Triggers alerts for low water levels using the Blynk app.

Key Functions

  . sensorvalue1(): Sends sensor data to Blynk virtual pins and checks critical water levels.

  . loop(): Continuously reads sensor data and handles Blynk operations.

  . setup(): Initializes the sensors, Blynk connection, and timers.

