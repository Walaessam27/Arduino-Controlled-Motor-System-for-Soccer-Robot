// Motor A and B connections
int enA = 9;
int in1 = 8;
int in2 = 7;
int enB = 3;
int in3 = 5;
int in4 = 4;

// Ultrasonic Sensor Pins
int trigRight = 2;
int echoRight = 12;
int trigCenter = 11;
int echoCenter = 10;
int trigLeft = 6;
int echoLeft = 13;

// Speed control
int speed = 50; // Default speed

// Distance threshold for obstacle detection
const int obstacleDistance = 15; // cm

void setup() {
  // Motor pins as output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Sensor pins as output/input
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigCenter, OUTPUT);
  pinMode(echoCenter, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);

  // Initialize motors to stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.begin(9600); // Debugging
}

// Function to measure distance using an ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Function to control motors with speed and direction
void controlMotors(int speed, bool forward) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  if (forward) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

// Functions for directional control
void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnLeft(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  // Measure distances from sensors
  long rightDistance = measureDistance(trigRight, echoRight);
  long centerDistance = measureDistance(trigCenter, echoCenter);
  long leftDistance = measureDistance(trigLeft, echoLeft);

  // Debugging output
  Serial.print("Right: ");
  Serial.print(rightDistance);
  Serial.print(" cm, Center: ");
  Serial.print(centerDistance);
  Serial.print(" cm, Left: ");
  Serial.println(leftDistance);

  // Decision logic
  if (centerDistance < obstacleDistance) {
    // Obstacle ahead
    Serial.println("Obstacle ahead! Stopping...");
    stopMotors();
    delay(500);
    // Reverse slightly and turn
    controlMotors(speed, false); // Reverse
    delay(500);
    stopMotors();
    delay(200);
    if (leftDistance > rightDistance) {
      Serial.println("Turning left...");
      turnLeft(speed);
      delay(500);
    } else {
      Serial.println("Turning right...");
      turnRight(speed);
      delay(500);
    }
    stopMotors();
  } else if (leftDistance < obstacleDistance) {
    // Obstacle on the left
    Serial.println("Obstacle on left! Turning right...");
    turnRight(speed);
    delay(500);
    stopMotors();
  } else if (rightDistance < obstacleDistance) {
    // Obstacle on the right
    Serial.println("Obstacle on right! Turning left...");
    turnLeft(speed);
    delay(500);
    stopMotors();
  } else {
    // No obstacles, move forward
    Serial.println("Path clear! Moving forward...");
    controlMotors(speed, true);
  }

  delay(100); // Small delay for stability
}