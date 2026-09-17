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

// Control parameters
#define SW_PIN 2

int Ref = 50;

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

  unsigned long pulseWidthUs = pulseIn(ECHO_PIN, HIGH);
  float distance_mm = pulseWidthUs * 0.000001 * 340 /2 * 1000;
  Serial.println("Distance: " + String(distance_mm) + " [mm]");

  if (Serial.available() > 0) {
    Ref = Serial.readString().toInt();
    Serial.println("data received: " + String(Ref));
  }

  if(digitalRead(SW_PIN) == HIGH){  // お掃除
    if(distance_mm > 50){
      digitalWrite(AIN1_PIN, HIGH);
      digitalWrite(AIN2_PIN, LOW);
      digitalWrite(BIN1_PIN, HIGH);
      digitalWrite(BIN2_PIN, LOW);
      analogWrite(PWMA_PIN, Ref);
      analogWrite(PWMB_PIN, Ref);

      delay(100);
    }
    else{
      digitalWrite(AIN1_PIN, HIGH);
      digitalWrite(AIN2_PIN, LOW);
      digitalWrite(BIN1_PIN, LOW);
      digitalWrite(BIN2_PIN, HIGH);
      analogWrite(PWMA_PIN, Ref);
      analogWrite(PWMB_PIN, Ref);

      delay(500);
    }
  }
  else{
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, LOW);
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, LOW);
    analogWrite(PWMA_PIN, 0);
    analogWrite(PWMB_PIN, 0);

    delay(100);
  }

}