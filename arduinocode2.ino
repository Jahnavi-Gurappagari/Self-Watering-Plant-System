#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

// DHT Sensor
#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int water; // Variable to store soil moisture level
float water1;
int trig = 8;
int echo = 9;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  pinMode(3, OUTPUT); // Output pin for relay board, this will send signal to the relay
  pinMode(6, INPUT); // Input pin coming from soil sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
  mySerial.begin(9600); // Initialize SoftwareSerial communication at 9600 bits per second
  dht.begin(); // Initialize the DHT sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(500);
}

void loop() {
  // Soil moisture sensor reading
  water = digitalRead(6);  // Reading the signal from the soil sensor
  water1 = analogRead(6);
  
  Serial.print("Moisture Level: ");
  Serial.println(water1);
  //mySerial.println(water1); // Send soil moisture data to NodeMCU
  
  // Controlling the relay based on the soil moisture level
  if (water == HIGH) {
    digitalWrite(3, LOW); // Low signal to cut the relay
  } else {
    digitalWrite(3, HIGH); // High signal to continue providing signal and water supply
  }

  // Ultrasonic sensor reading
  long duration;
  long distance;
  int percentage;

  digitalWrite(trig, HIGH);
  delayMicroseconds(11);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  percentage = map(distance, 10, 1, 0, 100);

  if (percentage < 0) {
    percentage = 0;
  } else if (percentage > 100) {
    percentage = 100;
  }

  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.println(" %");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //mySerial.print("Distance: ");
  //mySerial.print(distance);
  //mySerial.println(" cm"); // Send ultrasonic sensor data to NodeMCU

  // DHT11 sensor reading
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  // Prepare and send data to NodeMCU
  String cdata = String("") + water1 + "," + percentage + "," + h + "," + t;
  mySerial.println(cdata);
  Serial.println(cdata);

  delay(2000);
}
