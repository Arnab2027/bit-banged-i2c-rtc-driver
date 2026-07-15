# Bare-Metal Bit-Banged I2C Driver for DS1307 RTC

A light-weight, register-level bare-metal C driver that emulates the I2C protocol through software bit-banging on an AVR target architecture (ATmega328P). This project was built completely from scratch to demonstrate low-level hardware control, timing synchronization, and protocol state-machine implementation without using standard hardware libraries.

## 🛠️ System Features
* **Software Bit-Banging:** Emulates Open-Drain configuration on GPIO registers (`DDRC`, `PORTC`, `PINC`) to prevent bus short-circuits.
* **Deterministic Timing:** Maintains I2C Standard Mode (100 kHz) timing margins using calibrated microsecond instruction delays.
* **Bare-Metal UART Engine:** Direct configuration of `UBRR0`, `UCSR0B`, and `UDR0` registers for serial data telemetry at 9600 bps.
* **Modular Code Structure:** Clean separation between Bus Layer (`i2c_bb`), Device Driver (`ds1307`), and Application Layer (`main`).

## ⚙️ How it Works under the Hood
1. **Open-Drain Simulation:** To safely drive the line LOW, the pin is configured as output and pulled low. To release the line HIGH, the pin is converted back to an input, allowing the hardware pull-up resistors to bring the bus line high safely.
2. **BCD Decoding:** Decodes the Binary Coded Decimal format utilized by the DS1307's internal registers into decimal values for real-time serial terminal displays.

## 🚀 How to Run the Simulation
You can simulate this project instantly in your browser without any hardware using Wokwi:
1. Open [Wokwi](https://wokwi.com).
2. Create an Arduino Uno project and wire a **DS1307 RTC** (SDA to A4, SCL to A5).
3. Copy the compiled modular source code into the editor and hit **Play**.
