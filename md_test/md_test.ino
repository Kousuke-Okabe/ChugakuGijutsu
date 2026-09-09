#define AIN1 4
#define AIN2 2
#define PWMA 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  analogWrite(PWMA, 128);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    // Process incoming data
    int data = Serial.read();
    Serial.println("data received: " + String(data));

    analogWrite(PWMA, data);
  }
}
