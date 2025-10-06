#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5

#define IR_L2 A0
#define IR_L1 A1
#define IR_C  A2
#define IR_R1 A4
#define IR_R2 A3

#define echo 11
#define trigger 12

#define servo A5

#define LED_LEFT 2
#define LED_RIGHT 3

#define BUZZER 4

int Set = 27;
int distance_L, distance_F, distance_R;

void setup() {
  Serial.begin(9600);

  pinMode(IR_L2, INPUT);
  pinMode(IR_L1, INPUT);
  pinMode(IR_C,  INPUT);
  pinMode(IR_R1, INPUT);
  pinMode(IR_R2, INPUT);

  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(servo, OUTPUT);

  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  analogWrite(enA, 120);
  analogWrite(enB, 120);
}

void loop() {
  distance_F = getMedianDistance();
  if (distance_F <= Set) {
    Serial.print("Obstacle detected at ");
    Serial.print(distance_F);
    Serial.println(" cm. Starting avoidance maneuver.");
    performAvoidanceManeuver();
    return;
  }

  bool sL2 = digitalRead(IR_L2);
  bool sL1 = digitalRead(IR_L1);
  bool sC  = digitalRead(IR_C);
  bool sR1 = digitalRead(IR_R1);
  bool sR2 = digitalRead(IR_R2);

  Serial.print("IR Sensors [L2, L1, C, R1, R2]: ");
  Serial.print(sL2);
  Serial.print(" ");
  Serial.print(sL1);
  Serial.print(" ");
  Serial.print(sC);
  Serial.print(" ");
  Serial.print(sR1);
  Serial.print(" ");
  Serial.println(sR2);

  if (!sL2 && !sL1 && sC && !sR1 && !sR2) {
    forword();
  }
  else if ((!sL2 && sL1 && sC && !sR1 && !sR2) || (!sL2 && sL1 && !sC && !sR1 && !sR2)) {
    turnLeftMinor();
  }
  else if ((!sL2 && !sL1 && sC && sR1 && !sR2) || (!sL2 && !sL1 && !sC && sR1 && !sR2)) {
    turnRightMinor();
  }
  else if ((sL2 && sL1 && !sC && !sR1 && !sR2) || (sL2 && !sL1 && !sC && !sR1 && !sR2)) {
    turnLeftMajor();
  }
  else if ((!sL2 && !sL1 && !sC && sR1 && sR2) || (!sL2 && !sL1 && !sC && !sR1 && sR2)) {
    turnRightMajor();
  }
  else if (!sL2 && !sL1 && !sC && !sR1 && !sR2) {
    forword();
  }
  else {
    Stop();
  }
  
  delay(10);
}

void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500;
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50);
}

long Ultrasonic_read() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long time = pulseIn(echo, HIGH);
  return time / 29 / 2;
}

long getMedianDistance() {
  const int samples = 5;
  long readings[samples];
  for (int i = 0; i < samples; i++) {
    readings[i] = Ultrasonic_read();
    delay(5);
  }

  for (int i = 0; i < samples - 1; i++) {
    for (int j = i + 1; j < samples; j++) {
      if (readings[i] > readings[j]) {
        long temp = readings[i];
        readings[i] = readings[j];
        readings[j] = temp;
      }
    }
  }
  return readings[samples / 2];
}

void buzzerOn() {
  digitalWrite(BUZZER, HIGH);
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}

void turnLeftMinor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(LED_LEFT, HIGH);
  digitalWrite(LED_RIGHT, LOW);

  buzzerOff();
}

void turnRightMinor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(LED_RIGHT, HIGH);
  digitalWrite(LED_LEFT, LOW);

  buzzerOff();
}

void turnLeftMajor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(LED_LEFT, HIGH);
  digitalWrite(LED_RIGHT, LOW);

  buzzerOn();
}

void turnRightMajor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(LED_RIGHT, HIGH);
  digitalWrite(LED_LEFT, LOW);

  buzzerOn();
}

void forword() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  buzzerOff();
}

void backword() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  buzzerOff();
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  buzzerOff();
}

void performAvoidanceManeuver() {
  Stop();
  delay(200);

  for (int angle = 70; angle <= 140; angle += 5) {
    servoPulse(servo, angle);
  }
  delay(600);

  distance_R = getMedianDistance();
  Serial.print("Scanning Right... Distance: ");
  Serial.print(distance_R);
  Serial.println(" cm");
  delay(100);

  for (int angle = 140; angle >= 0; angle -= 5) {
    servoPulse(servo, angle);
  }
  delay(600);

  distance_L = getMedianDistance();
  Serial.print("Scanning Left...  Distance: ");
  Serial.print(distance_L);
  Serial.println(" cm");
  delay(100);

  for (int angle = 0; angle <= 70; angle += 5) {
    servoPulse(servo, angle);
  }
  delay(600);

  if (distance_L > distance_R && distance_L > Set) {
    Serial.println("Decision: Left side is clearer. Executing LEFT maneuver.");
    turnLeftMajor();
    delay(500);
    forword();
    delay(600);
    turnRightMajor();
    delay(520);
    forword();
    delay(500);
    turnRightMajor();
    delay(600);
    buzzerOff();
  } else if (distance_R > Set) {
    Serial.println("Decision: Right side is clearer. Executing RIGHT maneuver.");
    turnRightMajor();
    delay(500);
    forword();
    delay(600);
    turnLeftMajor();
    delay(520);
    forword();
    delay(500);
    turnLeftMajor();
    delay(600);
    buzzerOff();
  } else {
    Serial.println("Decision: Both sides are blocked. Reversing.");
    backword();
    delay(1000);
    Stop();
    buzzerOff();
  }
}