// this constant won't change. pin number of the ultrasonic sensor signal:
const int pingPin = 7;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // variables for duration of the ping,
  // result in and centimeters:
  long duration, cm;

  /* The PING is triggered by a HIGH pulse of 2 or more microseconds.
   * Give a short LOW pulse beforehand to ensure a clean HIGH pulse:*/
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  /* The same pin is used to read the signal from the PING))): 
   * a HIGH pulse whose duration is the time (in microseconds) 
   * from the sending of the ping to the reception of its echo 
   * off of an object. */
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
  delay(100);


}

long microsecondsToCentimeters(long microseconds) {
  /* The speed of sound is 340 m/s or 29 microseconds per centimeter.
   * The ping travels out and back, so to find the distance of the
   * half of the distance travelled. */
  return microseconds / 29 / 2;
}
