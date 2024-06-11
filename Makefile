CC = g++
CFLAGS = -Wall -g -Werror -Wextra

INC_DIR = ./Include
SRC_DIR = ./Src
DATA_DIR = ./Output

SRC = $(shell find $(SRC_DIR) -type f -name "*.cpp" )
OBJ = ${SRC:.cpp=.o}
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(shell find $(SRC_DIR) -type f -name "*.o")
	rm -f $(shell find $(DATA_DIR) -type f -name "*.png")
	rm -f $(shell find $(DATA_DIR) -type f -name "*.dot")
	rm -f $(shell find $(DATA_DIR) -type f -name "*.txt")
	clear

clean-ObjectFile:
	rm -f $(TARGET)
	rm -f $(shell find $(SRC_DIR) -type f -name "*.o")
	clear

.PHONY: result
result:
	@echo "Compilation result:"
	@g++ $(CFLAGS) -o $(TARGET)