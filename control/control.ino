// Motor driver
#define AIN1_PIN 4
#define AIN2_PIN 5
#define PWMA_PIN 6
#define BIN1_PIN 7
#define BIN2_PIN 8
#define PWMB_PIN 9
#define SW_PIN 2

// Ultrasonic sensor
#define TRIG_PIN 11
#define ECHO_PIN 12

#define US_a 0.182
#define US_b -4.79

#define Kp 0.5

const unsigned long ECHO_TIMEOUT_US = 30000UL;
unsigned long distance_ref = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Motor driver pins setting
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(PWMA_PIN, OUTPUT);

  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
  pinMode(PWMB_PIN, OUTPUT);

  analogWrite(PWMA_PIN, 0);
  analogWrite(PWMB_PIN, 0);

  // Ultrasonic sensor pins setting
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  // Switch pin setting
  pinMode(SW_PIN, INPUT);
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
  // Serial.println("Pulse width: " + String(pulseWidthUs) + " [us]");
  Serial.println("Distance: " + String(distance_mm) + " [mm]");

  // Motor control
  static int velocity = 0;
  static int angular = 0;
  float vel_m1 = 0;
  float vel_m2 = 0;

  if (Serial.available() > 0) {
    distance_ref = Serial.readString().toInt();
    // Serial.println("data received: " + String(velocity));
  }

  if(digitalRead(SW_PIN) == HIGH){
    velocity = Kp*( distance_ref - distance_mm );
    angular = 0;
  }
  else{
    velocity = 20;
    angular = Kp*( distance_ref - distance_mm );
  }


  vel_m1 = velocity + angular;
  vel_m2 = velocity - angular;
  // Serial.println("vel_m1: " + String(vel_m1) + ", vel_m2: " + String(vel_m2));

  if(vel_m1 >= 0){
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
  } else {
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
  }
  analogWrite(PWMA_PIN, abs(vel_m1));

  if(vel_m2 >= 0){
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
  } else {
    digitalWrite(BIN1_PIN, HIGH);
    digitalWrite(BIN2_PIN, LOW);
  }
  analogWrite(PWMB_PIN, abs(vel_m2));

  delay(100);
}