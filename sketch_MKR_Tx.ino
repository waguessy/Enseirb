#include <SPI.h>  // bibl comm série (ici moniteur série de l'ordi)
#include <LoRa.h> // bibl comm Lora de MKR Tx à MKR Rx
#include <Adafruit_GPS.h> // Bibli GPS

//broches utilisés pour la communiction LoRa
#define SS_PIN    10  // broche de selection
#define RST_PIN   9   // broche de réinitialisation
#define DI0_PIN   2   //broche d'interuption

const int temperaturePin = A0; // Broche analogique utilisée pour le capteur LM35

void setup() {
  //Serial.begin(9600); // initialistation de la communication série à 9600 bauds
  while (!Serial);   // attend que la communication série soit prête avant de porusuivre

  if (!LoRa.begin(868E6)) // initialisation de la cumunication LoRa
  {
    //Serial.println("Starting LoRa failed!"); // affichage si communication echoue
    while (1);
  }
}

void loop() {
  int sensorValue = analogRead(temperaturePin); // Lecture de la valeur analogique de température
  float voltage = sensorValue * (3.3 / 1023.0); // Conversion de la valeur lue en tension (0-5V)
  float temperatureC = voltage / 0.01; // Conversion de la tension en degrés Celsius (10 mV/°C)
  
 //afichage sur le moniteur série de la température + message
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  Serial.println("Hello world affiche ! ");
  // Envoie un message + température
  LoRa.beginPacket();
  LoRa.println("Hello, world envoie!");
  LoRa.print("Temperature: ");
  LoRa.print(temperatureC);
  LoRa.print(" °C");
  LoRa.endPacket();
  delay(2000);
}