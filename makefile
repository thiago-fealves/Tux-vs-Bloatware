TARGET = main

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -I$(INC_DIR) -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include/
LDLIBS := $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
