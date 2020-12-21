#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX

#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
 
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2

char BTin; // Stores response of the HC-06 Bluetooth device
int duration = 1000; //Amount of time for each command to make motors turn
int rtChanger = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
 
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  // Open serial communications:
  Serial.begin(9600);
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
}

void loop() {
  
  analogWrite(E1, 255);
  analogWrite(E2, 255); // Run both motors full speed

  if (mySerial.available()) {
    BTin = mySerial.read(); // No repeats
    Serial.println(BTin);
  }
  
  if(isdigit(BTin)) {
    rtChanger *= 10;
    rtChanger += BTin - 48; //Offset ascii value code
  }
  else {
    if(rtChanger > 0) {
      duration = rtChanger;
    }
    rtChanger = 0;
    switch (BTin) {
      case 'w':
        Serial.println("FORWARD");
        digitalWrite(I1, HIGH);
        digitalWrite(I2, LOW);
        digitalWrite(I3, HIGH);
        digitalWrite(I4, LOW);
        delay(duration);
        break;
      case 'a':
        Serial.println("TURNING LEFT");
        digitalWrite(I1, HIGH);
        digitalWrite(I2, LOW);
        digitalWrite(I3, LOW);
        digitalWrite(I4, LOW);
        delay(duration);
        break;
      case 's':
        Serial.println("BACKWARD");
        digitalWrite(I1, LOW);
        digitalWrite(I2, HIGH);
        digitalWrite(I3, LOW);
        digitalWrite(I4, HIGH);
        delay(duration);
        break;
      case 'd':
        Serial.println("TURNING RIGHT");
        digitalWrite(I1, LOW);
        digitalWrite(I2, LOW);
        digitalWrite(I3, HIGH);
        digitalWrite(I4, LOW);
        delay(duration);
        break;
    } 
  }

  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, LOW);
  delay(10);
}
