//slave 

#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define BUFFER_SIZE 32

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Initialize I2C as slave with the given address
  Wire.onReceive(receiveEvent); // Register event handler for receiving data
  Serial.begin(9600);
}

void loop() {
  // The loop is intentionally empty. The receiveEvent function handles incoming data.
}

// This function is called when data is received via I2C
void receiveEvent(int howMany) {
  char buffer[BUFFER_SIZE];
  int index = 0;

  // Read the data from the I2C buffer
  while (Wire.available()) {
    buffer[index++] = Wire.read();
    if (index >= BUFFER_SIZE) break;
  }
  buffer[index] = '\0'; // Null-terminate the string

  // Print the received message
  Serial.print("Message received: ");
  Serial.println(buffer);
}