TARGET = main
TEST_TARGET = test_runner

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = build/tests

# C++ Compiler
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I$(INC_DIR)

# Allegro (pkg-config)
ALLEGRO_FLAGS := $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)
ALLEGRO_LIBS := $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)

# PostgreSQL (Homebrew)
PQXX_INCLUDE_DIR := $(shell brew --prefix libpqxx)/include
PQXX_LIB_DIR := $(shell brew --prefix libpqxx)/lib
PQ_INCLUDE_DIR := $(shell brew --prefix libpq)/include
PQ_LIB_DIR := $(shell brew --prefix libpq)/lib


# OpenCV (opencv4)
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS := $(shell pkg-config --libs opencv4)

CXXFLAGS += $(ALLEGRO_FLAGS) -I$(PQXX_INCLUDE_DIR) -I$(PQ_INCLUDE_DIR) $(OPENCV_CFLAGS)
LDLIBS = $(ALLEGRO_LIBS) -L$(PQXX_LIB_DIR) -L$(PQ_LIB_DIR) -lpqxx -lpq $(OPENCV_LIBS)

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
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Convenience Targets
all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
