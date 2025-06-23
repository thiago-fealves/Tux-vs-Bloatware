TARGET = main
TEST_TARGET = test_runner

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = build/tests

# C++ Compiler
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Allegro e libpqxx via pkg-config
PKG_FLAGS := $(shell pkg-config --cflags --libs \
	allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 \
	allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5 \
	libpqxx)

CXXFLAGS += $(shell pkg-config --cflags \
	allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 \
	allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5 \
	libpqxx)

LDLIBS = $(shell pkg-config --libs \
	allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 \
	allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5 \
	libpqxx)

# Source and Object files
SRC_FILES := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ := $(BUILD_DIR)/main.o
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_FILES))

# Targets
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CXX) $(OBJ_FILES) $(MAIN_OBJ) $(LDLIBS) -o $@

$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(TEST_OBJ_FILES) $(LDLIBS) -o $@

# Build Rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Convenience Targets
all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean