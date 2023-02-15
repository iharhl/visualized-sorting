BUILD_DIR := ./build
SRC_DIRS := ./src

CC := g++
OPTIONS := -std=c++20
COMPILE := $(CC) $(OPTIONS)
LINK := -I src/include -L src/lib -lSDL2main -lSDL2

all: $(BUILD_DIR)/Main

$(BUILD_DIR)/Main: $(BUILD_DIR)/Main.o $(BUILD_DIR)/Visualizer.o
	$(COMPILE) -o $(BUILD_DIR)/main $(BUILD_DIR)/Main.o $(BUILD_DIR)/Visualizer.o $(LINK)

$(BUILD_DIR)/Main.o: main.cpp visualizer.h
	$(COMPILE) -c main.cpp -o $(BUILD_DIR)/main.o $(LINK)

$(BUILD_DIR)/Visualizer.o: visualizer.h types.h
	$(COMPILE) -c visualizer.cpp -o $(BUILD_DIR)/visualizer.o $(LINK)