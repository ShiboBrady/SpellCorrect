BIN = MakeDictEn

INSTALL_PATH = ../bin

TARGET = $(INSTALL_PATH)/$(BIN)

SRC = $(wildcard ./*.cpp)

OBJ = $(SRC:.cpp=.o)

RM = rm -rf

CC = g++

CFLAGS = -Wall -g 

.PHONY:all clean

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)
	$(RM) $(TARGET)
