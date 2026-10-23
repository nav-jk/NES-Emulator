GXX = g++ -std=c++17 -Wall -I.
SRC = src
TEST = test
BUILD = build

.PHONY : all clean run

all:
	mkdir -p $(BUILD)
	$(GXX) $(SRC)/*.cpp $(TEST)/*.cpp -o $(BUILD)/main

clean:
	rm -rf $(BUILD)

run: all
	./$(BUILD)/main
