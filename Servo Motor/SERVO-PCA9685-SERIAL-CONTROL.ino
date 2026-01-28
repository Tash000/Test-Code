#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

// Safer servo control parameters
#define SERVOMIN  150 // Minimum pulse length
#define SERVOMAX  600 // Maximum pulse length

#define MOTOR_A  0  // Channel 0
#define MOTOR_B  1  // Channel 1

String serialInput;

int angleToPulse(int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

void moveServo(int channel, int angle) {
  // Avoid extreme positions that cause stalling
  if (angle < 10) angle = 10;
  if (angle > 170) angle = 170;
  
  int pulse = angleToPulse(angle);
  pca9685.setPWM(channel, 0, pulse);
  
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(" moved to ");
  Serial.print(angle);
  Serial.println(" degrees");
}

// Release servo to prevent overheating
void releaseServo(int channel) {
  pca9685.setPWM(channel, 0, 0);
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.println(" released (no power)");
}

void processCommand() {
  serialInput = Serial.readStringUntil('\n');
  serialInput.trim();
  serialInput.toUpperCase();
  
  if (serialInput.startsWith("MOV")) {
    if (serialInput.length() >= 5) { // Minimum: MOVA0
      char channel = serialInput.charAt(3); // Get 'A' or 'B'
      int angle = serialInput.substring(4).toInt();
      
      if (channel == 'A') {
        moveServo(MOTOR_A, angle);
      } 
      else if (channel == 'B') {
        moveServo(MOTOR_B, angle);
      } 
      else {
        Serial.println("Error: Use MOVA or MOVB");
      }
    } 
    else {
      Serial.println("Error: Invalid command format");
    }
  }
  else if (serialInput == "OFF" || serialInput == "RELEASE") {
    releaseServo(MOTOR_A);
    releaseServo(MOTOR_B);
    Serial.println("All servos released - no holding torque");
  }
  else {
    Serial.println("Commands: MOVA<angle>, MOVB<angle>, OFF");
  }
  
  Serial.flush();
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.setRxBufferSize(1024);
  
  pca9685.begin();
  pca9685.setPWMFreq(50);  // Correct frequency for servos
  
  delay(1000);
  
  // Start at safe center position
  moveServo(MOTOR_A, 90);
  moveServo(MOTOR_B, 90);
  
  Serial.println("\n=== Dual Servo Controller Ready ===");
  Serial.println("Commands:");
  Serial.println("  MOVA90   - Move channel 0 to 90°");
  Serial.println("  MOVB45   - Move channel 1 to 45°");
  Serial.println("  MOVA0    - Move channel 0 to 0°");
  Serial.println("  MOVB180  - Move channel 1 to 180°");
  Serial.println("  OFF      - Release servos (no power)");
  Serial.println("Note: Range limited to 10-170° for safety");
  Serial.println("==================================\n");
}

void loop() {
  if (Serial.available() > 0) {
    processCommand();
  }
}
