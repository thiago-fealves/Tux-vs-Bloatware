TARGET = main
TEST_TARGET = test_runner

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = build/tests

POSTGRES_INCLUDE_DIR := /usr/include/postgresql
POSTGRES_LIB_DIR := /usr/lib/x86_64-linux-gnu

# Arquivos fonte principais (excluindo o main.cpp se existir)
SRC_FILES := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

# Objetos para o programa principal
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ := $(BUILD_DIR)/main.o

# Objetos para os testes
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_FILES))

CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I$(INC_DIR) -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include/
CXXFLAGS += -I$(POSTGRES_INCLUDE_DIR)
LDLIBS := $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)
TEST_LDLIBS := $(shell pkg-config --libs allegro-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)
LDLIBS_POSTGRES := -L$(POSTGRES_LIB_DIR) -lpqxx -lpq
LDLIBS := $(LDLIBS) $(LDLIBS_POSTGRES)
TEST_LDLIBS := $(TEST_LDLIBS) $(LDLIBS_POSTGRES)
# Target principal
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CXX) $(OBJ_FILES) $(MAIN_OBJ) $(LDLIBS) -o $@

# Target para testes (sem allegro_main)
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(TEST_OBJ_FILES) $(TEST_LDLIBS) -o $@

# Compilação do arquivo principal
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilação dos arquivos de teste
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
