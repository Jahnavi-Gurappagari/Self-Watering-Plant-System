#define BLYNK_TEMPLATE_ID "TMPL3JjGcnV0H"
#define BLYNK_TEMPLATE_NAME "Smart Plant"
#define BLYNK_AUTH_TOKEN "1pvf9zzYsnQTHQfAP8dGl0zXJu8QcvIe"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WIFI credentials.
// Set password to "" for open networks.
char ssid[] = "your wifi name";
char pass[] = "your password";

BlynkTimer timer;

String myString; // complete message from Arduino, which consists of sensors data

// This function sends sensor data to Virtual Pins and checks for soil moisture level
void sensorvalue1()
{
  if (myString.length() > 0) {
    // Parse the comma-separated string into individual values
    String values[4]; // Assuming there are two values (Soil Moisture, Distance)
    int i = 0;
    char* t = strtok((char*)myString.c_str(), ",");
    while (t != NULL && i < 4) {
      values[i++] = String(t);
      t = strtok(NULL, ",");
    }

    // Extract values from the array
    int soilMoistureValue = values[0].toInt();
    float percentage = values[1].toFloat();
    float humidityValue = values[2].toFloat();
    float tempValue = values[3].toFloat();
    // Print values for debugging
    Serial.print("Soil Moisture : ");
    Serial.println(soilMoistureValue);
    Serial.print("Percentage : ");
    Serial.println(percentage);
    Serial.print("Humidity : ");
    Serial.println(humidityValue); 
    Serial.print("Temperature : ");
    Serial.println(tempValue);
    Serial.println("--------------------------");

    // Check for critical soil moisture level
    if (percentage < 30) {
       Blynk.logEvent("water_level_critical", "Water level is decreased, please fill the tank...");
     }

    // Send values to Blynk virtual pins
    Blynk.virtualWrite(V5, soilMoistureValue); 
    Blynk.virtualWrite(V6, percentage); 
    Blynk.virtualWrite(V7, humidityValue);
    Blynk.virtualWrite(V8, tempValue);

    // Clear accumulated data after sending
    myString = "";
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sensorvalue1);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  // Check for incoming data from the sensor
  if (Serial.available() > 0) {
    myString = Serial.readStringUntil('\n');
    delay(1);
  }
}
