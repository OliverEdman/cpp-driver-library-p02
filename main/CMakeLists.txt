idf_component_register(
    SRCS
        "source/main.cpp"
        "source/driver/adc/esp32s3.cpp"
        "source/driver/factory/esp32s3.cpp"
        "source/driver/gpio/esp32s3.cpp"
        "source/driver/serial/esp32s3.cpp"
        "source/driver/tempsensor/tmp36.cpp"
        "source/driver/timer/esp32s3.cpp"
        # Lägg till eeprom och watchdog här för VG sen
    INCLUDE_DIRS
        "include")
