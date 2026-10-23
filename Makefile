GXX = g++ -std=c++17
SRC = src
BUILD = build

.PHONY : all clean run

all:
	mkdir -p $(BUILD)
	$(GXX) $(SRC)/main.cpp -o $(BUILD)/main

clean:
	rm -rf $(BUILD)

run: all
	./$(BUILD)/main