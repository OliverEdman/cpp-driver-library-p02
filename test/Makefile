TARGET := test

INC_DIR := ../main/include
SRC_DIR := ../main/source

CXX_COMPILER := g++

CXX_FLAGS := -Wall -Werror -std=c++17 -I$(INC_DIR)

SOURCE_FILES := test.cpp \
                $(SRC_DIR)/driver/adc/esp32s3.cpp \
                $(SRC_DIR)/driver/factory/esp32s3.cpp \
                $(SRC_DIR)/driver/gpio/esp32s3.cpp \
                $(SRC_DIR)/driver/serial/esp32s3.cpp \
                $(SRC_DIR)/driver/tempsensor/tmp36.cpp \
                $(SRC_DIR)/driver/timer/esp32s3.cpp \

default: build run

build:
	@$(CXX_COMPILER) $(SOURCE_FILES) -o $(TARGET) $(CXX_FLAGS)

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
