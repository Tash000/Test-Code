#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

// Safer servo control parameters
#define SERVOMIN  150 // Minimum pulse length
#define SERVOMAX  600 // Maximum pulse length

#define JAW_LEFT  1
#define JAW_RIGHT 2

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
  
  if (serialInput.startsWith("JAW")) {
    if (serialInput.length() >= 5) {
      char side = serialInput.charAt(3);
      int angle = serialInput.substring(4).toInt();
      
      if (side == 'L') {
        moveServo(JAW_LEFT, angle);
      } 
      else if (side == 'R') {
        moveServo(JAW_RIGHT, angle);
      } 
      else {
        Serial.println("Error: Use JAWL or JAWR");
      }
    } 
    else {
      Serial.println("Error: Invalid command format");
    }
  }
  else if (serialInput == "OFF" || serialInput == "RELEASE") {
    releaseServo(JAW_LEFT);
    releaseServo(JAW_RIGHT);
    Serial.println("All servos released - no holding torque");
  }
  else {
    Serial.println("Commands: JAWL<angle>, JAWR<angle>, OFF");
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
  moveServo(JAW_LEFT, 90);
  moveServo(JAW_RIGHT, 90);
  
  Serial.println("\n=== JAW Servo Controller Ready ===");
  Serial.println("Commands:");
  Serial.println("  JAWL90   - Move left to 90°");
  Serial.println("  JAWR45   - Move right to 45°");
  Serial.println("  OFF      - Release servos (no power)");
  Serial.println("Note: Range limited to 10-170° for safety");
  Serial.println("==================================\n");
}

void loop() {
  if (Serial.available() > 0) {
    processCommand();
  }
}

