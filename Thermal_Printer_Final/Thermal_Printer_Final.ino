String sendMessage;
String receivedMessage;
#include "SoftwareSerial.h";
#include "Adafruit_Thermal.h";

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

#define RX_PIN10 10
#define TX_PIN9 9

SoftwareSerial mySerial(RX_PIN, TX_PIN);
SoftwareSerial printSerial(RX_PIN10, TX_PIN9);

Adafruit_Thermal printer(&printSerial);

void setup() {
  Serial.begin(1200);    // Initialize the Serial monitor for debugging
  mySerial.begin(1200);   // Initialize Serial1 for sending data
  printSerial.begin(19200);
  printer.begin();
}

void loop() {
mySerial.listen();
  
  while (mySerial.available() > 0) {
    char receivedChar = mySerial.read();
    if (receivedChar == '\n') {
      printSerial.listen();
      delay(1000L);
      printer.println(receivedMessage);
     // delay(500L);
      printer.feed(3);
      printer.sleep();      // Tell printer to sleep
      delay(1000L);         // Sleep for 3 seconds
      printer.wake();       // MUST wake() before printing again, even if reset
      printer.setDefault(); // Restore printer to defaults
      
      
      Serial.println(receivedMessage);  // Print the received message in the Serial monitor
      receivedMessage = "";  // Reset the received message
    } else {
      receivedMessage += receivedChar;  // Append characters to the received message
    }
  }

}
