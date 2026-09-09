// Motor driver
#define AIN1_PIN 4
#define AIN2_PIN 5
#define PWMA_PIN 6
#define BIN1_PIN 7
#define BIN2_PIN 8
#define PWMB_PIN 9

// Ultrasonic sensor
#define TRIG_PIN 11
#define ECHO_PIN 12

#define US_a 0.182
#define US_b -4.79

const unsigned long ECHO_TIMEOUT_US = 30000UL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Motor driver pins setting
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(PWMA_PIN, OUTPUT);

  // Ultrasonic sensor pins setting
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize motor driver
  digitalWrite(AIN1_PIN, LOW);
  digitalWrite(AIN2_PIN, HIGH);
  analogWrite(PWMA_PIN, 128);

  // Initialize ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  // Sense distance using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long pulseWidthUs = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  float distance_mm = US_a * pulseWidthUs + US_b;
  Serial.println("Distance: " + String(distance_mm) + " [mm]");

  if (Serial.available() > 0) {
    // Process incoming data
    int data = Serial.read();
    // Serial.println("data received: " + String(data));

    analogWrite(PWMA_PIN, data);
  }
}
