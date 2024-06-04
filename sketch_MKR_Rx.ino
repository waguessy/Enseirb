// bibli communication serie + LoRa
#include <SPI.h>
#include <LoRa.h>

//broches utilisés pour la communiction LoRa
#define SS_PIN    10
#define RST_PIN   9
#define DI0_PIN   2

void setup() {
  // initialistation de la communication série à 9600 bauds
  Serial.begin(9600);
  while (!Serial);

  // initialisation de la comunication LoRa
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  //  vérifie s'il y a un paquet de données disponible pour être lu
  if (LoRa.parsePacket()) {
    while (LoRa.available()) {
      // lecture du pacquet décoder de binaire a ascii puis affichage
      Serial.print((char)LoRa.read());
    }
    //sauter des ligne entre chaque paquet de donné reçu
    Serial.println();
  }
}