TARGET := test

INC_DIR := ../main/include
SRC_DIR := ../main/source

TST_INC := include/
TST_SRC := source/
YRGO_TEST_DIR := ../yrgo-test
YRGO_LIB := $(YRGO_TEST_DIR)/libyrgo_test.a

CXX_COMPILER := g++

# Define TESTSUITE to use your mocked ESP32 implementation.
CXX_FLAGS := -Wall -Werror -std=c++17 -I$(INC_DIR) -I$(TST_INC) -I$(YRGO_TEST_DIR)/include -static-libstdc++ -static-libgcc -DTESTSUITE

TEST_FILES := $(TST_SRC)/test.cpp \
              $(TST_SRC)/test/gpio.cpp \
              $(TST_SRC)/test/pin_manager.cpp \

SOURCE_FILES := $(SRC_DIR)/driver/adc/esp32s3.cpp \
                $(SRC_DIR)/driver/factory/esp32s3.cpp \
                $(SRC_DIR)/driver/gpio/esp32s3.cpp \
                $(SRC_DIR)/driver/mqtt/esp32s3.cpp \
                $(SRC_DIR)/driver/serial/esp32s3.cpp \
                $(SRC_DIR)/driver/tempsensor/tmp36.cpp \
                $(SRC_DIR)/driver/timer/esp32s3.cpp \
                $(SRC_DIR)/driver/wifi/esp32s3.cpp \
                $(SRC_DIR)/system/logic/logic.cpp \
                $(SRC_DIR)/system/pin_manager/esp32s3.cpp \

ALL_FILES := $(TEST_FILES) $(SOURCE_FILES)

default: build run

$(YRGO_LIB):
	@$(MAKE) -C $(YRGO_TEST_DIR) lib

build: $(YRGO_LIB)
	@$(CXX_COMPILER) $(ALL_FILES) -o $(TARGET) $(CXX_FLAGS) -L$(YRGO_TEST_DIR) -lyrgo_test

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
