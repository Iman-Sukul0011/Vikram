# Vikram
VIKRAM 1.0 is a first-generation CanSat prototype by Parikramaka, built using ESP32, BMP280, and MPU6050 to collect atmospheric data. The mission validates the hydrostatic equation through real flight measurements using onboard SD card logging.
# VIKRAM 1.0: Controlled & Stable Descent CanSat 🚀

**Project Lead:** Iman Sukul (Founder, Parikramaka - NIT Rourkela)

VIKRAM 1.0 is a specialized atmospheric descent probe designed to collect real-time telemetry and study atmospheric boundary layers. This project integrates IMU stability tracking, barometric altimetry, and a local Wi-Fi ground station for live data streaming.

---

## 📡 Features
- **Real-time Telemetry:** Streams Accel, Gyro, Temp, and Altitude data via a hosted Web Server.
- **On-board Logging:** High-frequency data logging to a MicroSD card in CSV format.
- **Local Ground Station:** Provides a mobile-friendly web dashboard for field monitoring without needing internet.
- **Modular Design:** Built using ESP32, MPU6050, and BMP280.

---

## 🛠 Hardware Architecture

| Component | Function | Interface |
|-----------|----------|-----------|
| **ESP32** | Main MCU & Wi-Fi Access Point | - |
| **MPU6050** | 6-Axis IMU (Accel + Gyro) | I2C (0x68) |
| **BMP280** | Pressure, Temp & Altitude | I2C (0x76) |
| **MicroSD Module** | Non-volatile Data Logging | SPI |
| **Li-Po Battery** | 3.7V - 7.4V Power Supply | - |



## 💻 Software Stack
The firmware is written in C++ (Arduino Framework) and utilizes:
- **Asynchronous Data Handling:** Reads sensors and logs data at 1Hz (adjustable).
- **Embedded Web Server:** Serves a dynamic HTML dashboard to connected clients.
- **CSV Data Structure:** `Timestamp(ms), Accel_X, Accel_Y, Accel_Z, Gyro_X, Gyro_Y, Gyro_Z, Temp, Pressure, Altitude`

---

## 🚀 Getting Started

### Prerequisites
Install the following libraries in your Arduino IDE:
- `Adafruit MPU6050`
- `Adafruit BMP280`
- `Adafruit Unified Sensor`
