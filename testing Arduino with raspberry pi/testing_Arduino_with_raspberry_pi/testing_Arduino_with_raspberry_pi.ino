void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  Serial.println("Arduino is ready!");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read the command sent by Python
    command.trim(); // Remove any trailing newline or whitespace
    
    if (command == "LED_ON") {
      Serial.println("Turning LED ON");
      // Add code to turn on an LED if connected to a pin
    } else if (command == "LED_OFF") {
      Serial.println("Turning LED OFF");
      // Add code to turn off the LED
    } else {
      Serial.println("Unknown command");
    }
  }
}
