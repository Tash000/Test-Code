// Define the potentiometer pin
const int potPin = 34; // Use any available analog pin on the ESP32

void setup() {
  // Initialize serial communication
  Serial.begin(115200); // Set baud rate for serial communication
  delay(1000); // Small delay to ensure stable serial connection
}

void loop() {
  // Read the analog value from the potentiometer
  int potValue = analogRead(potPin);

  // Map the potentiometer value to a readable range (0-4095 for ESP32)
  float voltage = potValue * (3.3 / 4095.0); // Convert to voltage (assuming 3.3V reference)

  // Print the value in a readable format
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2); // Print voltage with 2 decimal places
  Serial.println("V");

  delay(500); // Delay for half a second before next reading
}
