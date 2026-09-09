const int TRIG_PIN = 11;
const int ECHO_PIN = 12;
const unsigned long ECHO_TIMEOUT_US = 30000UL;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  // Send a 10 microsecond trigger pulse.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Print the echo pulse width in microseconds (0 on timeout).
  unsigned long pulseWidthUs = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  Serial.println(pulseWidthUs);

  delay(100);
}
