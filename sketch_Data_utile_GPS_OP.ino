#include <SPI.h>  
#include <LoRa.h> 

#define SS_PIN    10  
#define RST_PIN   9   
#define DI0_PIN   2   

#define GPSSerial Serial1

#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&GPSSerial);

const int temperaturePin = A0; // Broche analogique utilisée pour le capteur LM35

void setup() {
  GPSSerial.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
  if (!LoRa.begin(868E6)) {
    while (1);
  }
}

void loop() {

  int sensorValue = analogRead(temperaturePin); // Lecture de la valeur analogique de température
  float voltage = sensorValue * (3.3 / 1023.0); // Conversion de la valeur lue en tension (0-5V)
  float temperatureC = voltage / 0.01; // Conversion de la tension en degrés Celsius (10 mV/°C)

  if (GPSSerial.available()) { 
    String data = GPSSerial.readStringUntil('\n');
    
    if (data.startsWith("$GPGGA")) {
      String parts[15];
      int partIndex = 0;
      int startIndex = 0;
      int endIndex = data.indexOf(',');
      
      while (endIndex != -1) {
        parts[partIndex++] = data.substring(startIndex, endIndex);
        startIndex = endIndex + 1;
        endIndex = data.indexOf(',', startIndex);
      }
      
      String latitude = parts[2];
      String longitude = parts[4];
      String altitude = parts[9];
      
      LoRa.beginPacket();
      LoRa.print(latitude);
      LoRa.print(",");
      LoRa.print(longitude);
      LoRa.print(",");
      LoRa.println(altitude);
      LoRa.println("temperature : ");
      LoRa.print(temperatureC);
      LoRa.endPacket();
    }
  }
}