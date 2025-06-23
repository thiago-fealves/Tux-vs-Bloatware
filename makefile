TARGET = main
TEST_TARGET = test_runner

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = build/tests

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

# Objetos do projeto necessários para os testes
TEST_PRJ_OBJ = \
	$(BUILD_DIR)/game_object.o \
	$(BUILD_DIR)/movement.o \
	$(BUILD_DIR)/bootstrap.o \
	$(BUILD_DIR)/levels.o \
	$(BUILD_DIR)/shots.o \
	$(BUILD_DIR)/sound.o \
	$(BUILD_DIR)/music.o \
	$(BUILD_DIR)/pipe.o \
	$(BUILD_DIR)/polygon_obstacle.o \
	$(BUILD_DIR)/circle_obstacle.o \
	$(BUILD_DIR)/obstacles_list.o \
	$(BUILD_DIR)/collision.o \
	$(BUILD_DIR)/windows_boss.o \
	$(BUILD_DIR)/abstract_obstacle.o \
	$(BUILD_DIR)/interface.o

TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_FILES))

# Alvo principal
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CXX) $(OBJ_FILES) $(MAIN_OBJ) $(LDLIBS) -o $@

# Test runner SEM allegro_main-5 e SEM libs de banco
$(TEST_TARGET): $(TEST_PRJ_OBJ) $(TEST_OBJ_FILES)
	$(CXX) $(TEST_PRJ_OBJ) $(TEST_OBJ_FILES) $(ALLEGRO_COMMON_LIBS) -o $@

# Build Rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

all: $(TARGET)
test: $(TEST_TARGET)
	./$(TEST_TARGET)
clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean