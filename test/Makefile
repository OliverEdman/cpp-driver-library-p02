TARGET := test

INC_DIR := ../main/include
SRC_DIR := ../main/source

TST_INC := include/
TST_SRC := source/

CXX_COMPILER := g++

CXX_FLAGS := -Wall -Werror -std=c++17 -I$(INC_DIR) -I$(TST_INC) -static-libstdc++ -static-libgcc

TEST_FILES := $(TST_SRC)/test.cpp \
              $(TST_SRC)/test/pin_manager.cpp \

SOURCE_FILES := $(SRC_DIR)/system/pin_manager/esp32s3.cpp \

ALL_FILES := $(TEST_FILES) $(SOURCE_FILES)

default: build run

build:
	@$(CXX_COMPILER) $(ALL_FILES) -o $(TARGET) $(CXX_FLAGS)

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
