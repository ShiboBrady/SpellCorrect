BIN = server

INSTALL_PATH = ./bin

TARGET = $(INSTALL_PATH)/$(BIN)

VPATH = :src

SRC_PATH = $(foreach dir, $(subst :, ,$(VPATH)), $(wildcard $(dir)/*.cpp))

OBJ_DIR = ./obj

OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(subst :, ,$(VPATH)))
	
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .cpp,.o,$(SRC_PATH)))

MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR) $(OBJ_PATH))

INCLUDES = -I./include/ \
		   -I./echo/

LIBS = -lpthread -lecho 

LIBDIRS = -L./lib

CC = gcc

CXX = g++

CXXFLAGES += -Wall -O2 -g -std=c++0x

RM = rm -rf

.PHONY : all clean

all:submake $(TARGET)

submake:
	make -C ./echo/
	make -C ./en_dict/
	make -C ./ch_dict/

$(TARGET):$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(LIBDIRS)

$(OBJ_PATH)/%.o:%.cpp
	$(CXX) $(CXXFLAGES) $(INCLUDES) -c $^ -o $@

clean:
	$(RM) $(INSTALL_PATH)/$(BIN)
	$(RM) $(wildcard $(OBJ_DIR)/*)
	make -C ./en_dict/ clean
	make -C ./ch_dict/ clean
