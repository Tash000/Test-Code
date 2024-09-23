#include <ESP32Servo.h>

// Define PWM-capable pins for servo control
const int servoPin1 = 2;  // Pin to move servo to a sweeping motion
const int servoPin2 = 4;  // Pin to move servo to 0 degrees
const int servoPin3 = 33; // Pin to move servo to 90 degrees
const int servoPin4 = 19; // Pin to move servo to 180 degrees

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

void setup() {
  Serial.begin(115200);

  // Attach servos to the respective pins
  myservo1.attach(servoPin1); // Sweeping servo
  myservo2.attach(servoPin2); // Servo for 0 degrees
  myservo3.attach(servoPin3); // Servo for 90 degrees
  myservo4.attach(servoPin4); // Servo for 180 degrees
}

void loop() {
  // Sweep the servo connected to servoPin1
  for (int pos = 0; pos <= 180; pos++) {
    myservo1.write(pos); // Sweeping from 0 to 180 degrees
    delay(15);           // Wait for 15ms to simulate servo movement
  }
  for (int pos = 180; pos >= 0; pos--) {
    myservo1.write(pos); // Sweeping back from 180 to 0 degrees
    delay(15);
  }

  // Servo connected to servoPin2 moves to 0 degrees
  myservo2.write(0);
  Serial.println("Servo at 0 degrees on Pin 4");

  // Servo connected to servoPin3 moves to 90 degrees
  myservo3.write(90);
  Serial.println("Servo at 90 degrees on Pin 18");

  // Servo connected to servoPin4 moves to 180 degrees
  myservo4.write(180);
  Serial.println("Servo at 180 degrees on Pin 19");

  delay(1000);  // Wait for 1 second before the next loop
}

