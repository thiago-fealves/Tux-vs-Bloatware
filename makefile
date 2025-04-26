TARGET = meu_programa

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

CXX = g++
CXXFLAGS = -Wall -g -std=c++17 # Adicionando flags de warning, depuração e C++17

LDFLAGS =

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR) 
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR) 
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*



