CC=g++
CXXFLAGS=-c -Wall -o
INCLUDE_DIR=./include
SRC_DIR=./src
BUILD_DIR=./build
EXE=decrypt

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/decrypt.o $(BUILD_DIR)/StringAnalysis.o
	$(CC) $^ -o $(BUILD_DIR)/$(EXE)

$(BUILD_DIR)/main.o: main.o
main.o: $(SRC_DIR)/main.cpp
	$(CC) $< $(CXXFLAGS) $(BUILD_DIR)/$@ -I$(INCLUDE_DIR)

$(BUILD_DIR)/decrypt.o: decrypt.o
decrypt.o: $(SRC_DIR)/decrypt.cpp $(INCLUDE_DIR)/decrypt.hpp
	$(CC) $< $(CXXFLAGS) $(BUILD_DIR)/$@ -I$(INCLUDE_DIR)

$(BUILD_DIR)/StringAnalysis.o: StringAnalysis.o
StringAnalysis.o: $(SRC_DIR)/StringAnalysis.cpp $(INCLUDE_DIR)/StringAnalysis.hpp
	$(CC) $< $(CXXFLAGS) $(BUILD_DIR)/$@ -I$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -rf build/*

.PHONY: run
run:
	$(BUILD_DIR)/$(EXE)
