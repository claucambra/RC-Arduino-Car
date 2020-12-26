#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX

#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
 
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2

#define ultrasoundPin 7 // Signal pin for ultrasound sensor

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

void drive(char command) {
  analogWrite(E1, 255);
  analogWrite(E2, 255); // Run both motors full speed

  switch(command) {
    case 'w': //FORWARD
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      break;
    case 's': //BACKWARD
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      break;
    case 'a': //TURN LEFT
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, LOW);
      digitalWrite(I4, LOW);
      break;
    case 'd': //TURN RIGHT
      digitalWrite(I1, LOW);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      break;
    case 'q': //SPIN LEFT
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      break;
    case 'e': //SPIN RIGHT
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      break;
    case 'p': //STOP
      digitalWrite(I1, LOW);
      digitalWrite(I2, LOW);
      digitalWrite(I3, LOW);
      digitalWrite(I4, LOW);
      break;
  } 
}

int detectDistance() {
  long duration; //Duration of the ping out
  
  pinMode(ultrasoundPin, OUTPUT);
  digitalWrite(ultrasoundPin, LOW);
  delayMicroseconds(2); //Short low pulse to ensure clean high pulse
  digitalWrite(ultrasoundPin, HIGH);
  delayMicroseconds(5); //
  digitalWrite(ultrasoundPin, LOW);

  pinMode(ultrasoundPin, INPUT);
  duration = pulseIn(ultrasoundPin, HIGH); //Time it takes for echo of HIGH ping to return

  return duration / 29 / 2; //Returns distance in centimeters (speed of sound is 29 cm per microsecond, then half the time of ping out and then in)
}

void waitAndCheckDistance(char input) {
  char oppositeDirection;
  switch(input) {
    case 'w': //FORWARD
      oppositeDirection = 's';
      break;
    case 's': //BACKWARD
      oppositeDirection = 'w';
      break;
    case 'a': //TURN LEFT
      oppositeDirection = 'd';
      break;
    case 'd': //TURN RIGHT
      oppositeDirection = 'a';
      break;
    case 'q': //SPIN LEFT
      oppositeDirection = 'e';
      break;
    case 'e': //SPIN RIGHT
      oppositeDirection = 'q';
      break;
    case 'p': //STOP
      oppositeDirection = 'p';
      break;
  } 
  
  int currentDistance;
  int starttime = millis();
  int endtime = starttime;
  while ((endtime - starttime) <= duration && currentDistance > 5) { // do this loop for set duration
    currentDistance = detectDistance();
    endtime = millis();
  }
  while(currentDistance < 2) { //Move away if less than 2cm away from obstacle
    drive('p');
    delay(50);
    drive(oppositeDirection);
    delay(duration);
    currentDistance = detectDistance();
  }
}

void loop() {
  if (mySerial.available()) {
    BTin = mySerial.read(); // No repeats
    Serial.println(BTin);
  }
  
  if(isdigit(BTin)) { //Detect if number provided, if so change duration of actions
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
        drive('w');
        waitAndCheckDistance('w');
        break;
      case 'a':
        drive('a');
        waitAndCheckDistance('a');
        break;
      case 's':
        drive('s');
        waitAndCheckDistance('s');
        break;
      case 'd':
        drive('d');
        waitAndCheckDistance('d');
        break;
      case 'q':
        drive('q');
        waitAndCheckDistance('q');
        break;
      case 'e':
        drive('e');
        waitAndCheckDistance('e');
        break;
    } 
  }

  drive('p'); //Stop motors
  delay(10);
}
