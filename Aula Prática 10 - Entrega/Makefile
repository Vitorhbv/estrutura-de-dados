CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude -pg
LDFLAGS = -g -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/pa10.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

mem: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE) 

callgrind: $(EXECUTABLE)
	valgrind --tool=callgrind ./$(EXECUTABLE) 

cachegrind: $(EXECUTABLE)
	valgrind --tool=cachegrind ./$(EXECUTABLE)

gprof: $(EXECUTABLE)
	./$(EXECUTABLE)
	gprof -b ./$(EXECUTABLE) gmon.out

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)
