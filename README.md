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
