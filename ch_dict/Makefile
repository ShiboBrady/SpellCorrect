#all: 
#	g++ -o demo -O3 -DLOGGER_LEVEL=LL_WARN -Wall -g -I../../include/MakeDictCh/ MakeDictCh.cpp MakeDictCh_Main.cpp 
#clean:
#	rm -f *.o *.a demo

BIN = MakeDictCh

INSTALL_PATH = ../bin

TARGET = $(INSTALL_PATH)/$(BIN)

RM = rm -rf

CC = g++

CFLAGES = -O3 -DLOGGER_LEVEL=LL_WARN -Wall -g

INCLUDES = -I../include/MakeDictCh/

SRC = $(wildcard ./*.cpp)

OBJ = $(SRC:.cpp=.o)

.PHONY : all clean

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ -o $@

%.o:%.cpp
	$(CC) $(CFLAGES) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(TARGET)
