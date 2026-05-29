### P02 – Driver Library for ESP32-S3
![Status](https://img.shields.io/badge/status-work--in--progress-orange)
![Platform](https://img.shields.io/badge/Platform-ESP32--S3-orange.svg)
![Framework](https://img.shields.io/badge/Framework-ESP--IDF-red.svg)



### 🎯 Project Purpose
A driver library for the ESP32-S3, created as a group project within the Embedded Systems program at Yrgo.

The project is designed to keep hardware-specific code separate from the system logic. By using interfaces and stubs, the library can run on both real hardware and in a simulated environment.


### 📁 Project Structure

```bash

├── 📂 include
│   ├── 📂 driver
│   │   ├── 📂 adc            # interface.h, esp32s3.h, stub.h
│   │   ├── 📂 factory        # interface.h, esp32s3.h, stub.h
│   │   ├── 📂 gpio           # interface.h, esp32s3.h, stub.h
│   │   ├── 📂 serial         # interface.h, esp32s3.h, stub.h
│   │   ├── 📂 tempsensor     # interface.h, tmp36.h, stub.h
│   │   └── 📂 timer          # interface.h, esp32s3.h, stub.h
│   └── 📂 system
│       └── 📂 logic          # logic.h
└── 📂 source
    ├── 📂 driver
    │   ├── 📂 adc            # esp32s3.cpp
    │   ├── 📂 factory        # esp32s3.cpp
    │   ├── 📂 gpio           # esp32s3.cpp
    │   ├── 📂 serial         # esp32s3.cpp
    │   ├── 📂 tempsensor     # tmp36.cpp
    │   └── 📂 timer          # esp32s3.cpp
    └── 📄 main.cpp           # main.cpp


```
### 🔌 Hardware Configuration 

To run the library in hardware mode on the ESP32-S3, the following pinout and peripheral configurations are used. The TMP36 sensor must be connected to an ADC1-compatible pin.

**TMP36 Vout (ADC)**  `GPIO 1` (ADC1_CH0 / A0) Analog input for temperature conversion 
**Status LED** `GPIO 6` (D3) Target LED for manual and timer driven blinking 
**Serial (UART)** `9600 Baud` Communication speed for the command interface 

### 🚀 Compilation
Use the standard ESP-IDF CLI toolchain to compile and flash the project onto the target hardware:

    idf.py set-target esp32s3
    idf.py build
    idf.py -p <PORT> flash monitor

### 🕹️ Command Interface

The system is controlled via the Serial (UART) interface using simple text commands. All Commands is handled inside `system::logic::Logic`

* `on` Turns the Status LED on (disables blinking).
* `off` Turns the Status LED off (disables blinking).
* `blink on` Activates timer controlled blinking mode.
* `blink off` Deactivates blinking mode (turns LED off).
* `period <ms>` Sets the blinking interval in milliseconds (e.g., `period 1000`).
* `temp` Reads and prints current temperature from TMP36 in °C.
* `status` Prints current state: blink mode (on/off), period (ms), and temp (°C).

### 🏗️ Architecture & Design Patterns

* **Abstract Factory (`driver::factory::Interface`):** Used to instantiate drivers without the system logic.
* **Dependency Injection:** The `system::logic::Logic` class receives a reference to the factory in its constructor. Furthermore, the `Tmp36` driver receives a reference to the `adc::Interface` upon creation:
  ```cpp
  // Example of the factory injection
  virtual std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept = 0;
  ```

### 🤝 Git Workflow & Code Review

To keep our project organized and the `main` branch stable, everyone must follow these steps:

* **Sync First** Always start your session with `git pull` to ensure you have the latest code from the team.

* **Branching** Never work directly in `main`. Create a descriptive branch for your task:  
    `git checkout -b feature/adc-driver`
    
* **Small & Frequent Commits** Work in small steps. It is better to have many small commits than one giant one.

* **Descriptive Messages** Every commit message must explain **what** you changed:  
     ✅ `git commit -m "Implement GPIO toggle function for Status LED"`  
     ❌ `git commit -m "fix"` or `git commit -m "code"`
    
* **Push & PR** Push your branch to GitHub and open a **Pull Request (PR)**. Describe shortly what you have implemented.

* **Review** At least one teammate must review your code. They look for bugs, logic, and structure.

* **Approve & Merge** Once you receive an **Approve**, the code can be merged into `main`. The branch can then be deleted.
