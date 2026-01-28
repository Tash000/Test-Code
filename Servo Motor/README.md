
# Dual Servo Controller using PCA9685 (Arduino)

## Look into SERVO-PCA-SERIAL-CONTROL


A robust Arduino-based dual servo control system using the **PCA9685 16-Channel PWM Driver**.
Servos are controlled via **serial commands**, with built-in safety limits to prevent stalling, overheating, or mechanical damage.

Simple. Safe. Serial-driven. No magic smoke released.

---

## 🚀 Features

* Control **two servo motors** independently
* Uses **PCA9685** for stable, jitter-free PWM
* Serial command interface (human-friendly)
* Angle safety limits (10°–170°)
* Servo release mode to prevent overheating
* Automatic startup centering
* Clean, extensible code structure

---

## 🧠 How It Works

* Arduino communicates with the **PCA9685** over I²C
* Servo angles (0–180°) are mapped to safe PWM pulse widths
* Commands are sent via the Serial Monitor (or any serial terminal)
* Servos can be powered down when not in use

---

## 🧰 Hardware Requirements

* Arduino (Uno / Nano / Mega / ESP32*)
* PCA9685 16-Channel PWM Servo Driver
* 2× Servo motors
* External 5–6V power supply for servos (recommended)
* Jumper wires

* ESP32 works, but make sure I²C pins are correct.

---

## 📦 Software Requirements

* Arduino IDE
* Libraries:

  * `Wire`
  * `Adafruit_PWMServoDriver`

Install the Adafruit library via **Library Manager**:

```
Adafruit PWM Servo Driver Library
```

---

## 🔌 Wiring Overview

| PCA9685 | Arduino   |
| ------- | --------- |
| VCC     | 5V / 3.3V |
| GND     | GND       |
| SDA     | SDA       |
| SCL     | SCL       |

* Servo A → PCA9685 Channel **0**
* Servo B → PCA9685 Channel **1**
* Power servos using **external supply** (don’t trust USB unless you enjoy resets)

---

## 🕹️ Serial Commands

Open Serial Monitor:

* **Baud Rate:** `115200`
* **Line Ending:** Newline (`\n`)

### Commands

| Command            | Description                        |
| ------------------ | ---------------------------------- |
| `MOVA90`           | Move Servo A (Channel 0) to 90°    |
| `MOVB45`           | Move Servo B (Channel 1) to 45°    |
| `MOVA0`            | Move Servo A to minimum safe angle |
| `MOVB180`          | Move Servo B to maximum safe angle |
| `OFF` or `RELEASE` | Disable power to both servos       |

⚠️ **Note:**
Actual movement is limited to **10°–170°** internally for safety.

---

## 🔒 Safety Design Choices

* **Angle clamping:** Prevents servo stalling at extremes
* **Pulse limits:** Keeps PWM within servo-safe range
* **Release mode:** Stops holding torque to avoid overheating
* **Startup centering:** Prevents violent boot-time movement

This is code written by someone who has killed servos before—and learned.

---

## ⚙️ Configuration

You can adjust these values in the code:

```cpp
#define SERVOMIN 150
#define SERVOMAX 600
```

Fine-tune based on your servo model for maximum precision.

---

## 📈 Extending the Project

Ideas if you want to level this up:

* Add more servo channels
* Implement velocity / smooth interpolation
* Add feedback via potentiometers or encoders
* Control via Bluetooth / Wi-Fi
* Build a simple robotic arm controller

---

## 📄 License

MIT License
Use it. Modify it. Break it. Fix it. Just don’t blame the code when the servo screams.

---


