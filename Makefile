CXX		  := g++
CXX_FLAGS := -O3 -Wall -Wextra -std=c++11 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include

EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

clean:
	-rm $(BIN)/*
