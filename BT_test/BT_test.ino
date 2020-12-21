#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX

int ledPin = 13;

char BTin; // Stores response of the HC-06 Bluetooth device

void setup() {
  pinMode(13, OUTPUT);
  
  // Open serial communications:
  Serial.begin(9600);
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
}

void loop() {
  // Read device output if available.
  if (mySerial.available()) {
   BTin = mySerial.read(); // No repeats
   Serial.println(BTin);
  }

  if (BTin == 'h') {
    digitalWrite(ledPin, HIGH);
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
