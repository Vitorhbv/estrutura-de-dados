CC = gcc
CFLAGS = -Wall -Iinclude -Ithird_party
LDFLAGS = -g -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/tp3.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@ -lrt

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)
