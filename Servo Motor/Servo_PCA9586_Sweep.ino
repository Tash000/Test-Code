#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

// Servo control parameters for MG996R / SG90 / MG90S
#define SERVOMIN  150 // Minimum pulse length out of 4096
#define SERVOMAX  600 // Maximum pulse length out of 4096

void setup() {
  Serial.begin(115200);
  
  // Initialize PCA9685
  pca9685.begin();
  pca9685.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  
  // Let the PCA9685 be stable
  delay(1000);
}

void loop() {
  // Sweep servos on channels 0-3 (first 4 channels)
  for (int pos = SERVOMIN; pos <= SERVOMAX; pos++) {
    for (int channel = 0; channel < 4; channel++) {
      pca9685.setPWM(channel, 0, pos); // Sweep servo position
    }
    delay(10);  // Small delay for smooth movement
  }
  for (int pos = SERVOMAX; pos >= SERVOMIN; pos--) {
    for (int channel = 0; channel < 4; channel++) {
      pca9685.setPWM(channel, 0, pos); // Sweep servo position back
    }
    delay(10);
  }

  // Set servos on channels 4-7 to 0 degrees (next 4 channels)
  for (int channel = 4; channel < 8; channel++) {
    pca9685.setPWM(channel, 0, SERVOMIN); // Set to 0 degrees
  }

  // Set servos on channels 8-11 to 90 degrees (next 4 channels)
  for (int channel = 8; channel < 12; channel++) {
    pca9685.setPWM(channel, 0, (SERVOMIN + SERVOMAX) / 2); // Set to 90 degrees
  }

  // Set servos on channels 12-15 to 180 degrees (last 4 channels)
  for (int channel = 12; channel < 16; channel++) {
    pca9685.setPWM(channel, 0, SERVOMAX); // Set to 180 degrees
  }

  delay(1000);  // Delay before starting the next loop
}
