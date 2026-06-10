### P02 / P02+ – Driver Library for ESP32-S3
![Status](https://img.shields.io/badge/status-work--in--progress-orange)
![Platform](https://img.shields.io/badge/Platform-ESP32--S3-orange.svg)
![Framework](https://img.shields.io/badge/Framework-ESP--IDF-red.svg)



### 🎯 Project Purpose
A driver library for the ESP32-S3, created as a group project within the Embedded Systems program at Yrgo.

The project is designed to keep hardware-specific code separate from the system logic. By using interfaces, factories and stubs, the library can run on both real hardware and in a simulated environment.

P02 contains the original driver library with Serial control, GPIO, Timer, ADC and TMP36 temperature reading.

P02+ extends the project with WiFi and MQTT support. MQTT can be used to send commands to the system and publish system status.



### 📁 Project Structure

```bash
├── 📂 main
│   ├── 📂 include
│   │   ├── 📂 driver
│   │   │   ├── 📂 adc            # interface.h, esp32s3.h, stub.h
│   │   │   ├── 📂 factory        # interface.h, esp32s3.h, stub.h
│   │   │   ├── 📂 gpio           # interface.h, esp32s3.h, stub.h
│   │   │   ├── 📂 mqtt           # interface.h, esp32s3.h, stub.h
│   │   │   ├── 📂 serial         # interface.h, esp32s3.h, stub.h
│   │   │   ├── 📂 tempsensor     # interface.h, tmp36.h, stub.h
│   │   │   ├── 📂 timer          # interface.h, esp32s3.h, stub.h
│   │   │   └── 📂 wifi           # interface.h, esp32s3.h, stub.h
│   │   └── 📂 system
│   │       └── 📂 logic          # logic.h
│   ├── 📂 source
│   │   ├── 📂 driver
│   │   │   ├── 📂 adc            # esp32s3.cpp
│   │   │   ├── 📂 factory        # esp32s3.cpp
│   │   │   ├── 📂 gpio           # esp32s3.cpp
│   │   │   ├── 📂 mqtt           # esp32s3.cpp
│   │   │   ├── 📂 serial         # esp32s3.cpp
│   │   │   ├── 📂 tempsensor     # tmp36.cpp
│   │   │   ├── 📂 timer          # esp32s3.cpp
│   │   │   └── 📂 wifi           # esp32s3.cpp
│   │   ├── 📂 system
│   │   │   └── 📂 logic          # logic.cpp
│   │   └── 📄 main.cpp
│   ├── 📄 CMakeLists.txt
│   └── 📄 Kconfig.projbuild
└── 📄 README.md
```



### 🔌 Hardware Configuration

To run the library in hardware mode on the ESP32-S3, the following pinout and peripheral configurations are used. The TMP36 sensor must be connected to an ADC1-compatible pin.

* **TMP36 Vout (ADC)** `GPIO 1` (ADC1_CH0 / A0) Analog input for temperature conversion
* **Status LED** `GPIO 6` (D3) Target LED for manual and timer driven blinking
* **Serial (UART)** `115200 Baud` Communication speed for the command interface



### 🚀 Compilation

Use the standard ESP-IDF CLI toolchain to compile and flash the project onto the target hardware:

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p <PORT> flash monitor
```



### ⚙️ P02 / P02+ Configuration

The project can be built in two modes:

* **P02 mode:** Original Serial controlled system.
* **P02+ mode:** Serial control plus WiFi and MQTT integration.

The mode is selected through ESP-IDF menuconfig:

```bash
idf.py menuconfig
```

Open:

```text
P02 network configuration
```

Available settings:

* `Enable MQTT integration` Enables or disables P02+ MQTT/WiFi support.
* `WiFi SSID` WiFi network name.
* `WiFi password` WiFi network password.
* `MQTT broker URI` MQTT broker address, for example `mqtt://192.168.1.50:1883`.
* `MQTT client ID` Unique client ID for the ESP32-S3.

Do not hardcode private WiFi credentials in source files. WiFi and MQTT values should be configured through `menuconfig` / `sdkconfig`.



### 🕹️ Serial Command Interface

The system is controlled via the Serial (UART) interface using simple text commands. All commands are handled inside `app::logic::Logic`.

* `on` Turns the Status LED on and disables blinking.
* `off` Turns the Status LED off and disables blinking.
* `blink on` Activates timer controlled blinking mode.
* `blink off` Deactivates blinking mode and turns the LED off.
* `period <ms>` Sets the blinking interval in milliseconds, for example `period 1000`.
* `temp` Reads and prints the current temperature from TMP36 in °C.
* `status` Prints current state: blink mode, period and temperature.



### 📡 MQTT Interface

When P02+ mode is enabled, the system connects to WiFi and then starts the MQTT client.

The MQTT driver is separated from the system logic and is accessed through `driver::mqtt::Interface`.

MQTT topics:

* `p02/command` Incoming commands to the ESP32-S3.
* `p02/status` System status published from the ESP32-S3.

The payload sent to `p02/command` uses the same commands as Serial:

```text
on
off
blink on
blink off
period 1000
temp
status
```

Example using Mosquitto:

```bash
mosquitto_sub -h <BROKER_IP> -t p02/status
```

```bash
mosquitto_pub -h <BROKER_IP> -t p02/command -m "blink on"
mosquitto_pub -h <BROKER_IP> -t p02/command -m "period 1000"
mosquitto_pub -h <BROKER_IP> -t p02/command -m "status"
```



### 🏗️ Architecture & Design Patterns

* **Interfaces:** System logic depends on abstract driver interfaces, not concrete ESP-IDF drivers.
* **Abstract Factory (`driver::factory::Interface`):** Used to create drivers without the system logic knowing the concrete implementation.
* **Dependency Injection:** `app::logic::Logic` receives a factory reference in its constructor.
* **Smart pointers:** The system logic owns its drivers through `std::unique_ptr`.
* **Stub drivers:** Stub implementations make it possible to simulate drivers without real hardware.
* **Separated hardware layer:** ESP-IDF specific code is kept inside the real driver implementations.

Example of TMP36 dependency injection:

```cpp
virtual std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin,
                                                          adc::Interface& adc) noexcept = 0;
```

The TMP36 driver receives an ADC reference instead of creating its own ADC internally.



### 🧪 Testing / Verification

Basic hardware verification:

1. Flash the ESP32-S3.
2. Open the serial monitor.
3. Send `on` and verify that the LED turns on.
4. Send `off` and verify that the LED turns off.
5. Send `blink on` and verify that the LED blinks.
6. Send `period 1000` and verify that the blink period changes.
7. Send `temp` and verify that a temperature value is printed.
8. Send `status` and verify that blink mode, period and temperature are printed.

MQTT verification:

1. Start or connect to an MQTT broker.
2. Configure WiFi and broker URI using `idf.py menuconfig`.
3. Flash the ESP32-S3.
4. Subscribe to `p02/status`.
5. Publish commands to `p02/command`.
6. Verify that LED behavior and status output match the commands.



### 🤝 Git Workflow & Code Review

To keep our project organized and the `main` branch stable, everyone must follow these steps:

* **Sync First** Always start your session with `git pull` to ensure you have the latest code from the team.

* **Branching** Never work directly in `main`. Create a descriptive branch for your task:

```bash
git checkout -b feature/mqtt-integration
```

* **Small & Frequent Commits** Work in small steps. It is better to have many small commits than one giant one.

* **Descriptive Messages** Every commit message must explain what you changed.

* **Push & PR** Push your branch to GitHub and open a Pull Request. Describe shortly what you have implemented.

* **Review** At least one teammate must review your code. They look for bugs, logic and structure.

* **Approve & Merge** Once you receive an approve, the code can be merged into `main`. The branch can then be deleted.
