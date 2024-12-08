// كود السيرفو سرعته عجبتنا
#include <Servo.h>

// Create a servo object
Servo myServo;

// Define the servo pin
const int servoPin = 9;

void setup() {
  // Attach the servo to the pin
  myServo.attach(servoPin);
  
  // Move the servo to the initial position
  myServo.write(90); // Move to 90 degrees (middle position)
}

void loop() {
  // Example: Sweep servo from 0 to 180 degrees and back
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);   // Set the servo angle
    delay(15);              // Wait for the servo to reach the position
  }
  
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}