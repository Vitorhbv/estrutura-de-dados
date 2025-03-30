# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -I./include

# Diretórios de origem, objeto e binário
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos de origem e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nome do executável
EXECUTABLE = $(BIN_DIR)/pa8.out

# Alvo padrão
all: $(EXECUTABLE)

# Compilação do programa
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos de origem em objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove os objetos e o executável
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

# Indica que os alvos "clean" e "all" não são arquivos
.PHONY: clean all
