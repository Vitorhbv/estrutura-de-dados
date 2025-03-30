# Compilador e flags de compilação
CC = gcc
CFLAGS = -Wall -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/tp2.out

all: $(TARGET)

# Regra para compilar os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
