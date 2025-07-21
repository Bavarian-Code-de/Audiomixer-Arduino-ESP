Repository is not yet completely functional!!

---

# Audiomixer-Arduino-ESP 🎛️

**ESP32 firmware for sending audio control commands to a Windows desktop app via serial**

---

## 📌 Purpose

Firmware running on an ESP32 that reads Slider potentiometer input and sends simplified volume commands over the serial port to a Windows desktop app (from another repo) — the desktop app then adjusts system audio volume accordingly.

---

## 🧱 Technology Stack

* **Platform**: ESP32 with Arduino Core (via Arduino IDE or PlatformIO)
* **Communication**: Serial USB to Windows host
* **Interaction**: Desktop app reads serial input and applies volume changes - directly to windows or specified apps

---

## ⚙️ Features

* Send volume level (0–100) via serial
* OLEDS - displays icons, text or Volume percentage
* supports quick connect of Oled Screens - for magnetic attachment during runtime
* LED light display for each slider - color can be set through desktop app 

---

## 🏛️ Architecture

```
[Slider Potentiometer on ESP32]
         ↓
   ESP32 Firmware
         ↓ Serial USB
   [Windows Desktop App] → adjusts system volume
```

---

## 🔧 Requirements

* Any ESP32-compatible or Arduino board
* Arduino IDE (≥ 1.8.x) or PlatformIO
* USB serial connection to Windows PC
* Desktop app from paired repo running and listening on COM port

---

## 🚀 Installation & Build

1. Clone the repo:

   ```bash
   git clone https://github.com/Bavarian-Code-de/Audiomixer-Arduino-ESP.git
   ```
2. Open the project in Arduino IDE or PlatformIO
3. Adjust input pins (e.g., potentiometer or encoder)
4. Set `SERIAL_BAUD` to match the desktop app (default 115200)
5. Upload to ESP32

---

## 🧩 Usage

1. Start the desktop app on Windows
2. Connect ESP32 via USB → it opens COM port at 115200 baud
3. Move Slider → ESP32 sends information via Serial
4. Desktop app reacts by adjusting system volume

---

## 🔄 Extensions

* Expand serial protocol (EQ, presets)
* Add lillygo T3 touch-controlled presets
* maybe motorized Sliders
* Optional remote control via Wi‑Fi or BLE

---

## 🛠️ Contributing

* Report bugs or request features → open an Issue
* Send pull requests to `development` branch
* Contributions of protocol spec examples or desktop-side code welcome

---

## 📄 License

MIT License — see `LICENSE`

---

## 📫 Contact

* Repo: Bavarian‑Code‑de/Audiomixer-Arduino-ESP
* For support or collaboration → open an Issue

---

