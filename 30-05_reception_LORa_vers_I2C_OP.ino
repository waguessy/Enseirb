#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define SLAVE_ADDRESS 0x08
#define LORA_SS 10    // Pin connected to LoRa module's NSS
#define LORA_RST 9    // Pin connected to LoRa module's RESET
#define LORA_DIO0 2   // Pin connected to LoRa module's DIO0

void setup() {
  Wire.begin(); // Initialize I2C as master
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
  
  // Setup LoRa transceiver module
  if (!LoRa.begin(868E6)) { // Initialize LoRa at 868 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String receivedMessage = "";

  // Check if there's a packet available to read
  if (LoRa.parsePacket()) {
    Serial.println("Packet received!");
    while (LoRa.available()) {
      // Read each character and add it to the message string
      char incoming = (char)LoRa.read();
      Serial.print(incoming); // Print the incoming character for debugging
      receivedMessage += incoming;
    }
    // Print a new line after each received packet
    Serial.println();

    // Log the received message
    Serial.println("Full received message: " + receivedMessage);

    // Send the received message over I2C
    Wire.beginTransmission(SLAVE_ADDRESS); // Start I2C transmission to slave
    Wire.write(receivedMessage.c_str());   // Send the received message
    Wire.endTransmission();                // End transmission

    Serial.println("Message sent over I2C: " + receivedMessage);
  }

  // Small delay to prevent flooding the I2C bus and to allow for stable LoRa communication
  //delay(2000); // Wait for 2 seconds before checking for the next packet
}