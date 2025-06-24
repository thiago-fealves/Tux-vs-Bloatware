TARGET = main
TEST_TARGET = test_runner

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = build/tests

CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I$(INC_DIR)

# Tenta usar pkg-config pra multiplataforma
ALLEGRO_FLAGS := $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)
ALLEGRO_MAIN_LIBS := $(shell pkg-config --libs allegro_main-5)
ALLEGRO_COMMON_LIBS := $(shell pkg-config --libs allegro-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)

# Libpqxx via pkg-config, se possível
PQXX_FLAGS := $(shell pkg-config --cflags --libs libpqxx)
PQXX_CFLAGS := $(shell pkg-config --cflags libpqxx)
PQXX_LDFLAGS := $(shell pkg-config --libs libpqxx)

# fallback pro macOS com Homebrew
ifeq ($(PQXX_FLAGS),)
  PQXX_INCLUDE_DIR := $(shell brew --prefix libpqxx)/include
  PQXX_LIB_DIR := $(shell brew --prefix libpqxx)/lib
  PQ_INCLUDE_DIR := $(shell brew --prefix libpq)/include
  PQ_LIB_DIR := $(shell brew --prefix libpq)/lib

  CXXFLAGS += -I$(PQXX_INCLUDE_DIR) -I$(PQ_INCLUDE_DIR)
  LDLIBS = $(ALLEGRO_COMMON_LIBS) $(ALLEGRO_MAIN_LIBS) -L$(PQXX_LIB_DIR) -L$(PQ_LIB_DIR) -lpqxx -lpq
else
  CXXFLAGS += $(PQXX_CFLAGS)
  LDLIBS = $(ALLEGRO_COMMON_LIBS) $(ALLEGRO_MAIN_LIBS) $(PQXX_LDFLAGS)
endif

# Allegro flags
CXXFLAGS += $(ALLEGRO_FLAGS)

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

# Test runner SEM allegro_main e SEM libpq
$(TEST_TARGET): $(TEST_PRJ_OBJ) $(TEST_OBJ_FILES)
	$(CXX) $(TEST_PRJ_OBJ) $(TEST_OBJ_FILES) $(ALLEGRO_COMMON_LIBS) -o $@

# Build Rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
